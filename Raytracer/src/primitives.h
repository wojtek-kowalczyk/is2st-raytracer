#pragma once

#include "vector3.h"

#include <ostream>

struct Ray
{
    Vector3 origin;
    Vector3 direction;

    friend std::ostream& operator<<(std::ostream& os, const Ray& r)
    {
		os << "Origin: " << r.origin << ", Direction: " << r.direction;
		return os;
	}
};

struct Sphere
{
    Vector3 center;
    float radius;

    bool Hit(Ray ray);

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

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t)
    {
        os << "V1: " << t.v1 << ", V2: " << t.v2 << ", V3: " << t.v3;
        return os;
    }
};
