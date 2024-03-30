#pragma once

#include "../sceneObject.h"
#include "../ray.h"
#include "../camera.h"

struct Sphere : public SceneObject
{
    Vector3 center;
    float radius;

    Sphere(Vector3 center, float radius);
    virtual bool Hit(Ray ray, HitResult& outHitResult) const override;
    virtual bool Hit(Ray ray) const override;

    // TODO : take a closer look at AA
    float aaFactor(float x, float y, Sphere sphere, Camera& camera, float size, int failsafe = 0);
    unsigned int finalColor(unsigned int color, float aaFactor);

    friend std::ostream& operator<<(std::ostream& os, const Sphere& s);
};