#pragma once

struct HitResult
{
    Vector3 hitPoint;
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