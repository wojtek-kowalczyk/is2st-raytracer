#pragma once

#include "vector3.h"
#include "ray.h"
#include "sceneObject.h"
#include "light.h"
#include "color.h"

#include <vector>

// TODO : sort out ownership of objects. Should the scene own them, or should it just reference them? heap vs stack?

class Scene 
{
public:
    void AddObject(SceneObject* object);
    void AddLight(Light* light);
    Color TraceRay(Ray ray, Color color, int ttl) const;

private:
    static constexpr Color BACKGROUND_COLOR = Color( 1.0f, 1.0f, 1.0f, 1.0f );
    static constexpr Color OUT_OF_BOUNCES_COLOR = Color(1.0f, 0.0f, 1.0f, 1.0f);

    bool GetClosestHit(Ray ray, HitResult& outHitResult, float& outDistanceToHit, bool ignoreRefractiveObjects = false) const;
    Color HandleDiffuse(const Material* objectMaterial, const Ray& ray, const HitResult& rayHit) const;
    std::vector<SceneObject*> m_objects;
    std::vector<Light*> m_lights;
};