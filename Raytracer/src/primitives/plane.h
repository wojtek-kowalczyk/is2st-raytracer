#pragma once

#include "../vector3.h"
#include "../sceneObject.h"
#include "../camera.h" // TODO : shouldn't be needed

struct Plane : public SceneObject
{
    Vector3 point;
    Vector3 normal;

    Plane(Vector3 point, Vector3 normal);

    bool Hit(Ray ray, HitResult& outHitResult) const override;
    bool Hit(Ray ray) const override;
    float aaFactor(float x, float y, Plane plane, Camera& camera, float size, int failsafe = 0);
    unsigned int finalColor(unsigned int color, float aaFactor);


    friend std::ostream& operator<<(std::ostream& os, const Plane& p);
};

