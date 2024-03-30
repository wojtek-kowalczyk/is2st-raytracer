#include "scene.h"
#include "ray.h"
#include "sceneObject.h"
#include "vector3.h"

#include <limits>
#include <cassert>

void Scene::AddObject(SceneObject* object) 
{
    m_objects.push_back(object);
}

void Scene::AddLight(Light* light)
{
    m_lights.push_back(light);
}

Color Scene::TraceRay(Ray ray) const
{
    HitResult rayHit;

    if (GetClosestHit(ray, rayHit))
    {
        const Material* objectMaterial = rayHit.material;

        assert(objectMaterial != nullptr);

        Color totalLightAccumulation(0, 0, 0, 1.0f);

        for (Light* light : m_lights)
        {
			Vector3 toLight = -light->GetDirection();
			Ray rayToLight(rayHit.hitPoint + toLight * 0.001f, toLight.Normalized()); // 0.001f to avoid self-shadowing
            
            HitResult _; // needn't be closest hit, just any hit
            if (GetClosestHit(rayToLight, _) == false) 
            {
                float shade = Vector3::Dot(toLight, rayHit.hitNormal);
                if (shade < 0)
                {
                    shade = 0;
                }
			    totalLightAccumulation += light->GetColor() * shade;
			}
		}

        Color light = m_ambientLight + totalLightAccumulation;

        assert(objectMaterial->color.IsClamped());

        return objectMaterial->color * light;
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