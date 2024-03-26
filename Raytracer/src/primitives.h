#pragma once

#include "vector3.h"
#include "ray.h"
#include "sceneObject.h"
#include "scene.h"
#include "camera.h"

#include <ostream>

struct Sphere : public SceneObject
{
    Vector3 center;
    float radius;

    Sphere(Vector3 center, float radius);
    virtual bool Hit(Ray ray, HitResult& outHitResult) const override;

    float aaFactor(float x, float y, Sphere sphere, Camera& camera, float size, int failsafe = 0);
    unsigned int finalColor(unsigned int color, float aaFactor);

    friend std::ostream& operator<<(std::ostream& os, const Sphere& s)
    {
        os << "Center: " << s.center << ", Radius: " << s.radius;
		return os;
    }
};

struct Plane : public SceneObject
{
    Vector3 point;
    Vector3 normal;

    bool Hit(Ray ray, HitResult& outHitResult) const override;
    float aaFactor(float x, float y, Plane plane, Camera& camera, float size, int failsafe = 0);
    unsigned int finalColor(unsigned int color, float aaFactor);

    friend std::ostream& operator<<(std::ostream& os, const Plane& p)
    {
		os << "Point: " << p.point << ", Normal: " << p.normal;
        return os;
    }
};

struct Triangle : public SceneObject 
{
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    bool Hit(Ray ray, HitResult& outHitResult) const override;

    float aaFactor(float x, float y, Triangle triangle, Camera& camera, float size, int failsafe = 0);
    unsigned int finalColor(unsigned int color, float aaFactor);

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t)
    {
        os << "V1: " << t.v1 << ", V2: " << t.v2 << ", V3: " << t.v3;
        return os;
    }
};
