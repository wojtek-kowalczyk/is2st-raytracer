#include "scene.h"
#include "ray.h"
#include "sceneObject.h"
#include "vector3.h"

#include <limits>

void Scene::AddObject(SceneObject* object) 
{
    m_objects.push_back(object);
}

Color Scene::TraceRay(Ray ray) const
{
    HitResult closestHit;

    if (GetClosestHit(ray, closestHit))
    {
        return Color::FromInt(closestHit.color); // TODO : this color passing is awkward, better would be hit->object->material->color
    }

    else return Color(0, 0, 0, 1.0f);
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