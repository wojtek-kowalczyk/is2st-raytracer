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

    friend std::ostream& operator<<(std::ostream& os, const Sphere& s);
};