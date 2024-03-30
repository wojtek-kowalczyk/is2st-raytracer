#pragma once

#include "../vector3.h"
#include "../ray.h"
#include "../sceneObject.h"
#include "../camera.h"

#include <ostream>

struct Triangle : public SceneObject 
{
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3);

    bool Hit(Ray ray, HitResult& outHitResult) const override;
    bool Hit(Ray ray) const override;

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};
