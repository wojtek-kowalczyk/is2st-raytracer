#pragma once

#include "vector3.h"
#include "color.h"

#include <cstdint>

struct HitResult
{
    Vector3 hitPoint {0, 0, 0};
    Color color = Color(0, 0, 0, 1.0f); // TODO : maybe give scene object? and take material and color from it.
};

struct Ray
{
    Vector3 origin;
    Vector3 direction;

    Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction)
    {
	}
};

std::ostream& operator<<(std::ostream& os, const Ray& r);

