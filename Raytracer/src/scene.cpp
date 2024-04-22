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
}

void Scene::AddObject(SceneObject* object) 
{
    m_objects.push_back(object);
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
            Color directLighting(0, 0, 0, 1.0f);

            Color indirectLighting = color * objectMaterial->color * DIFFUSE_DAMPING_CONSTANT;
            // 0.999 to avoid a case when we get a vector exactly opposite to normal
            Vector3 bounceDirection = rayHit.hitNormal + Vector3::RandomOnUnitSphere() * 0.999f; 
            bounceDirection.Normalize();
            Ray bounceRay(rayHit.hitPoint, bounceDirection);
            return TraceRay(bounceRay, directLighting + indirectLighting, ttl - 1);
        }

        case MaterialType::Reflective:
        {
            Color newColor = color * objectMaterial->color * REFLECTIVE_DAMPING_CONSTANT;
            Vector3 reflectedRayDirection = Vector3::Reflect(ray.direction, rayHit.hitNormal).Normalized() +
                Vector3::RandomOnUnitSphere() * objectMaterial->roughness;
            reflectedRayDirection.Normalize();
            Ray reflectedRay = Ray(rayHit.hitPoint, reflectedRayDirection);
            return TraceRay(reflectedRay, newColor, ttl - 1);
        }

        case MaterialType::Refractive:
        {
            Vector3 refractedRayDirection;
            bool wasRefracted = Vector3::Refract(ray.direction, rayHit.hitNormal, objectMaterial->ior, refractedRayDirection);
            // TODO : handle total internal reflection case, try air bubble (ior 1 / 1.3) to see.
            Ray refractedRay = Ray(rayHit.hitPoint, refractedRayDirection.Normalized());
            Color newColor = color * objectMaterial->color * REFRACTIVE_DAMPING_CONSTANT;
            return TraceRay(refractedRay, newColor, ttl - 1);
        }

        case MaterialType::Emissive:
        {
            Color tint = objectMaterial->color.Clamped(); // The emission color is likely to be above 1
            return (color * tint) + objectMaterial->color; // addition here makes it possible to add light to the scene
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