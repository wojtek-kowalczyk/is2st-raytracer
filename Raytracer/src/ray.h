#pragma once

#include "vector3.h"
#include <cstdint>

struct HitResult
{
    Vector3 hitPoint {0, 0, 0};
    uint32_t color = 0; // TODO : temporary implementation, ideally pass reference to the hit obj to get its material
    // SceneObject* hitObject; // TODO : object lifetime - care for invalid pointer
};

struct Ray
{
    Vector3 origin;
    Vector3 direction;

    Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction)
    {
	}

    friend std::ostream& operator<<(std::ostream& os, const Ray& r)
    {
        os << "Origin: " << r.origin << ", Direction: " << r.direction;
        return os;
    }
};