#pragma once

#include "vector3.h"
#include "ray.h"
#include "sceneObject.h"
#include "color.h"

#include <vector>

class Scene 
{
public:
    ~Scene();
    void AddObject(SceneObject* object);
    Color TraceRay(Ray ray, Color color, int ttl) const;

private:
    bool GetClosestHit(Ray ray, HitResult& outHitResult, float& outDistanceToHit, bool ignoreRefractiveObjects = false) const;

private:
    static constexpr Color BACKGROUND_COLOR = Color( 1.0f, 1.0f, 1.0f, 1.0f );
    static constexpr Color OUT_OF_BOUNCES_COLOR = Color(1.0f, 0.0f, 1.0f, 1.0f);

    std::vector<SceneObject*> m_objects;
};