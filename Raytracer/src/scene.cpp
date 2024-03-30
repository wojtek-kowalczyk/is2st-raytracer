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
    HitResult closestHit;

    if (GetClosestHit(ray, closestHit))
    {
        assert(closestHit.color.IsClamped());

        Color totalLightAccumulation(0, 0, 0, 1.0f);

        for (Light* light : m_lights)
        {
			Vector3 toLight = -light->GetDirection();
			Ray rayToLight(closestHit.hitPoint + toLight * 0.001f, toLight.Normalized()); // 0.001f to avoid self-shadowing
            
            HitResult _; // needn't be closest hit, just any hit
            if (GetClosestHit(rayToLight, _) == false) 
            {
			    totalLightAccumulation += light->GetColor();
			}
		}

        Color light = m_ambientLight + totalLightAccumulation;

        return closestHit.color * light;
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