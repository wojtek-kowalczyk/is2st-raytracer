#pragma once

#include "../vector3.h"
#include "../sceneObject.h"

struct Plane : public SceneObject
{
    Vector3 point;
    Vector3 normal;

    Plane(Vector3 point, Vector3 normal);

    bool Hit(Ray ray, HitResult& outHitResult) const override;
    bool Hit(Ray ray) const override;

    friend std::ostream& operator<<(std::ostream& os, const Plane& p);
};

