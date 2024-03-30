#pragma once

#include "vector3.h"
#include "ray.h"
#include "sceneObject.h"
#include "color.h"

#include <vector>

// TODO : sort out ownership of objects. Should the scene own them, or should it just reference them? heap vs stack?

class Scene 
{
public:
    void AddObject(SceneObject* object);
    Color TraceRay(Ray ray) const;

private:
    bool GetClosestHit(Ray ray, HitResult& outHitResult) const;
    std::vector<SceneObject*> m_objects;
};