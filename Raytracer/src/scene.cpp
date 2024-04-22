#include "scene.h"
#include "color.h"
#include "material.h"
#include "ray.h"
#include "sceneObject.h"
#include "vector3.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cassert>
#include <math.h>

Scene::~Scene()
{
    for (SceneObject* object : m_objects)
    {
		delete object;
	}

    for (Light* light : m_lights)
    {
		delete light;
	}
}

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
    std::cout << "Deprecated\n";
    abort();
    ///////////////////////////////////////////////////

    assert(objectMaterial->type == MaterialType::Diffuse);

    Color ambientLight(0.1f, 0.1f, 0.1f, 0.1f);
    Color diffuse(0, 0, 0, 1.0f);
    Color specular(0, 0, 0, 1.0f);

    for (Light* light : m_lights)
    {
        Vector3 toLight = -( light->GetDirection(rayHit.hitPoint).Normalized() );
        Ray rayToLight(rayHit.hitPoint + toLight, toLight);
        
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
    Color ambient = objectMaterial->color * ambientLight;

    return ambient * objectMaterial->Ka + diffuse * objectMaterial->Kd + specular * objectMaterial->Ks;
}

Color Scene::TraceRay(Ray ray, Color color, int ttl) const
{
    static constexpr float DIFFUSE_DAMPING_CONSTANT = 0.83f;
    static constexpr float REFLECTIVE_DAMPING_CONSTANT = 0.97f;
    static constexpr float REFRACTIVE_DAMPING_CONSTANT = 0.98f;

    if (ttl <= 0)
    {
        return color;
    }

    HitResult rayHit;
    float distanceToHit;
    if (GetClosestHit(ray, rayHit, distanceToHit))
    {
        const Material* objectMaterial = rayHit.material;
        assert(objectMaterial != nullptr);

        switch (objectMaterial->type)
        {
        case MaterialType::Diffuse:
        {
            Color newColor = color * objectMaterial->color * DIFFUSE_DAMPING_CONSTANT;
            // 0.999 to avoid a case when we get a vector exactly opposite to normal
            Vector3 bounceDirection = rayHit.hitNormal + Vector3::RandomOnUnitSphere() * 0.999f; 
            bounceDirection.Normalize();
            Ray bounceRay(rayHit.hitPoint, bounceDirection);
            return TraceRay(bounceRay, newColor, ttl - 1);
        }

        case MaterialType::Reflective:
        {
            Color newColor = color * objectMaterial->color * REFLECTIVE_DAMPING_CONSTANT;
            Vector3 reflectedRayDirection = Vector3::Reflect(ray.direction, rayHit.hitNormal).Normalized() +
                Vector3::RandomOnUnitSphere() * objectMaterial->roughness;
            reflectedRayDirection.Normalize();
            Vector3 reflectedRayOrigin = rayHit.hitPoint;
            Ray reflectedRay = Ray(reflectedRayOrigin, reflectedRayDirection);
            return TraceRay(reflectedRay, newColor, ttl - 1);
        }

        case MaterialType::Refractive:
        {
            Vector3 refractedRayDirection;
            bool refracted = Vector3::Refract(ray.direction, rayHit.hitNormal, objectMaterial->ior, refractedRayDirection);
            if (!refracted)
            {
                // TODO : handle this case with reflection? TIR?
                std::cerr << "Ray wasn't refracted!";
                return Color(1, 0, 1, 1.0f);
            }
            Ray refractedRay = Ray(rayHit.hitPoint, refractedRayDirection.Normalized());
            // std::cout << "incoming: " << ray << ", refracted: " << refractedRay << '\n'; 
            Color newColor = color * objectMaterial->color * REFRACTIVE_DAMPING_CONSTANT;
            return TraceRay(refractedRay, newColor, ttl - 1);
        }
        
        default:
            std::cerr << "Unhandled switch case\n";
            abort();
            break;
        }
    }
	else
    {
        return color;
    }
}

bool Scene::GetClosestHit(Ray ray, HitResult& outHitResult, float& outDistanceToHit, bool ignoreRefractiveObjects) const 
{
    HitResult closestHit;
    float closestDistanceSquared = std::numeric_limits<float>::max();
    for (SceneObject* object : m_objects) 
    {
        if (ignoreRefractiveObjects && object->GetMaterial()->type == MaterialType::Refractive) 
        {
            continue;
        }

        HitResult currentHit;
        if (object->Hit(ray, currentHit)) 
        {
            float distanceToHitSquared = (currentHit.hitPoint - ray.origin).SquareMagnitude();

            if (distanceToHitSquared < 0.00001f) 
            {
                continue;
            }

            if (distanceToHitSquared < closestDistanceSquared) 
            {
                closestDistanceSquared = distanceToHitSquared;
                closestHit = currentHit;
            }
        }
    }

    if (closestDistanceSquared != std::numeric_limits<float>::max()) 
    {
        outHitResult = closestHit;
        if (closestDistanceSquared == 0) 
        {
            std::cerr << "[WARNING] Calling call sqrt(0). Make sure this isn't a mistake.\n";
        }
        outDistanceToHit = sqrt(closestDistanceSquared);
        return true;
    }

    outHitResult.material = nullptr; // crash the app if we try to use it without checking if there was a hit
    return false;
}