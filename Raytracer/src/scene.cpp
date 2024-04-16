#include "scene.h"
#include "material.h"
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
    assert(objectMaterial->type == MaterialType::Diffuse);

    Color diffuse(0, 0, 0, 1.0f);
    Color specular(0, 0, 0, 1.0f);

    for (Light* light : m_lights)
    {
        Vector3 toLight = -( light->GetDirection(rayHit.hitPoint).Normalized() );
        // Ray rayToLight(rayHit.hitPoint + rayHit.hitNormal * 0.001f, toLight); // this makes wall corners show a warning and be black.
        Ray rayToLight(rayHit.hitPoint + toLight * 0.001f, toLight);
        
        HitResult _; 
        float distanceToHit;
        bool inShadow = GetClosestHit(rayToLight, _, distanceToHit, true);

        if (inShadow)
        {
            float distanceToLight = light->GetDirection(rayHit.hitPoint).Magnitude();
            if (distanceToHit <= distanceToLight)
            {
                // the object was obscured
                continue;
            }
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

Color Scene::TraceRay(Ray ray, int ttl) const
{
    if (ttl <= 0) 
    {
        return OUT_OF_BOUNCES_COLOR;
    }

    HitResult rayHit;
    float _;
    if (GetClosestHit(ray, rayHit, _))
    {
        const Material* objectMaterial = rayHit.material;
        assert(objectMaterial != nullptr);

        switch (objectMaterial->type)
        {
        case MaterialType::Diffuse:
            return HandleDiffuse(objectMaterial, ray, rayHit);

        case MaterialType::Reflective:
        {
            // ray hit a reflective surface. Compute a reflection ray and trace it again.
            Vector3 reflectedRayDirection = Vector3::Reflect(ray.direction, rayHit.hitNormal).Normalized();
            Vector3 reflectedRayOrigin = rayHit.hitPoint + (rayHit.hitNormal * 0.001f);
            Ray reflectedRay = Ray(reflectedRayOrigin, reflectedRayDirection);
            return TraceRay(reflectedRay, ttl - 1);
        }

        case MaterialType::Refractive:
        {
            // ray hit a refractive surface. Compute refracted ray and trace it again.
            Vector3 refractedRayDirection;
            bool refracted = Vector3::Refract(ray.direction, rayHit.hitNormal, objectMaterial->ior, refractedRayDirection);
            if (!refracted)
            {
                std::cout << "Ray wasn't refracted!";
                return Color(0, 0, 0, 1.0f);
            }
            Vector3 refractedRayOrigin;
            bool hitFromFront = Vector3::Dot(ray.direction, rayHit.hitNormal) < 0;
            if (hitFromFront)
            {
                refractedRayOrigin = rayHit.hitPoint + (-rayHit.hitNormal * 0.001f); // reverse normal because the next ray must go through
            }
            else 
            {
                refractedRayOrigin = rayHit.hitPoint + (rayHit.hitNormal * 0.001f); // dont reverse the normal because we want the ray to go outside.
            }
            Ray refractedRay = Ray(refractedRayOrigin, refractedRayDirection.Normalized());
            // std::cout << "incoming: " << ray << ", refracted: " << refractedRay << '\n'; 
            return TraceRay(refractedRay, ttl - 1);
        }
        default:
            std::cerr << "Unhandled switch case\n";
            abort();
            break;
        }
    }
    {
        return BACKGROUND_COLOR;
    }
}

Color Scene::TraceRay(Ray ray) const
{
    return TraceRay(ray, BOUNCES);
}

bool Scene::GetClosestHit(Ray ray, HitResult& outHitResult, float& outDistanceToHit, bool ignoreRefractiveObjects) const 
{
    HitResult closestHit;
    float closestDistance = std::numeric_limits<float>::max();
    for (SceneObject* object : m_objects) 
    {
        if (ignoreRefractiveObjects && object->GetMaterial()->type == MaterialType::Refractive) 
        {
            continue;
        }
        
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
        outDistanceToHit = closestDistance;
        return true;
    }

    return false;
}