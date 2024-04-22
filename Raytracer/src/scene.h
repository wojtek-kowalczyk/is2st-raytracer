#pragma once

#include "vector3.h"
#include "ray.h"
#include "sceneObject.h"
#include "light.h"
#include "color.h"

#include <vector>

class Scene 
{
public:
    ~Scene();
    void AddObject(SceneObject* object);
    void AddLight(Light* light);
    Color TraceRay(Ray ray, Color color, int ttl) const;

private:
    bool GetClosestHit(Ray ray, HitResult& outHitResult, float& outDistanceToHit, bool ignoreRefractiveObjects = false) const;
    Color HandleDiffuse(const Material* objectMaterial, const Ray& ray, const HitResult& rayHit) const;

private:
    static constexpr Color BACKGROUND_COLOR = Color( 1.0f, 1.0f, 1.0f, 1.0f );
    static constexpr Color OUT_OF_BOUNCES_COLOR = Color(1.0f, 0.0f, 1.0f, 1.0f);

    std::vector<SceneObject*> m_objects;
    std::vector<Light*> m_lights;
};