#include "scene.h"
#include "ray.h"
#include "sceneObject.h"
#include "vector3.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <cassert>
#include <math.h>

void Scene::AddObject(SceneObject* object) 
{
    m_objects.push_back(object);
}

void Scene::AddLight(Light* light)
{
    m_lights.push_back(light);
}

Color Scene::HandleDiffuse(const Material* objectMaterial, const Ray& ray, const HitResult& rayHit) const
{
    Color diffuse(0, 0, 0, 1.0f);
    Color specular(0, 0, 0, 1.0f);

    for (Light* light : m_lights)
    {
        Vector3 toLight = -light->GetDirection(rayHit.hitPoint).Normalized();
        Ray rayToLight(rayHit.hitPoint + rayHit.hitNormal * 0.001f, toLight.Normalized()); // 0.001f to avoid self-shadowing
        
        HitResult _; // needn't be closest hit, just any hit
        bool inShadow = GetClosestHit(rayToLight, _);

        if (inShadow)
        {
            continue;
        }
    
        // compute the diffuse component
        diffuse += objectMaterial->color * light->GetColor() * fmaxf(0.0f, Vector3::Dot(rayHit.hitNormal, toLight));

        // compute the specular component
        // what would be the ideal reflection direction for this light ray
        Vector3 reflected = Vector3::Reflect(-toLight, rayHit.hitNormal);
        specular += light->GetColor() * pow(fmaxf(0.0f, Vector3::Dot(reflected, -ray.direction)), objectMaterial->specularPow);
    }

    assert(objectMaterial->color.IsClamped());
    Color ambient = objectMaterial->color * m_ambientLight;

    return ambient * objectMaterial->Ka + diffuse * objectMaterial->Kd + specular * objectMaterial->Ks;
}

Color Scene::TraceRay(Ray ray) const
{
    HitResult rayHit;

    if (GetClosestHit(ray, rayHit))
    {
        const Material* objectMaterial = rayHit.material;

        assert(objectMaterial != nullptr);

        switch (objectMaterial->type)
        {
        case MaterialType::Diffuse:
            return HandleDiffuse(objectMaterial, ray, rayHit);

        case MaterialType::Reflective:
        case MaterialType::Transmissive:
        default:
            std::cerr << "Unhandled switch case\n";
            abort();
        }

    }
    else
    {
        return Color(0, 0, 0, 1.0f);
    }
}

bool Scene::GetClosestHit(Ray ray, HitResult& outHitResult) const 
{
    HitResult closestHit;
    float closestDistance = std::numeric_limits<float>::max();
    for (SceneObject* object : m_objects) 
    {
        HitResult currentHit;
        if (object->Hit(ray, currentHit)) 
        {
            float distanceToHit = (currentHit.hitPoint - ray.origin).Magnitude();
            if (distanceToHit < closestDistance) 
            {
                closestDistance = distanceToHit;
                closestHit = currentHit;
            }
        }
    }

    if (closestDistance != std::numeric_limits<float>::max()) 
    {
        outHitResult = closestHit;
        return true;
    }

    return false;
}