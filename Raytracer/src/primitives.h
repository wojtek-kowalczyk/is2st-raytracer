#pragma once

#include "vector3.h"
#include "ray.h"

#include <ostream>
#include "camera.h"

struct Sphere
{
    Vector3 center;
    float radius;

    bool Hit(Ray ray, HitResult& outHitResult) const;
    bool Hit(Ray ray) const;
    float aaFactor(float x, float y, Sphere sphere, Camera& camera, float size, int failsafe = 0);
    unsigned int finalColor(unsigned int color, float aaFactor);

    friend std::ostream& operator<<(std::ostream& os, const Sphere& s)
    {
        os << "Center: " << s.center << ", Radius: " << s.radius;
		return os;
    }
};

struct Plane 
{
    Vector3 point;
    Vector3 normal;

    bool Hit(Ray ray, HitResult& outHitResult) const;
    bool Hit(Ray ray) const;

    friend std::ostream& operator<<(std::ostream& os, const Plane& p)
    {
		os << "Point: " << p.point << ", Normal: " << p.normal;
        return os;
    }
};

struct Triangle 
{
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    bool Hit(Ray ray, HitResult& outHitResult) const;
    bool Hit(Ray ray) const;

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t)
    {
        os << "V1: " << t.v1 << ", V2: " << t.v2 << ", V3: " << t.v3;
        return os;
    }
};
