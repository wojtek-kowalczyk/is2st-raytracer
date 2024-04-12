#pragma once

#include "vector3.h"
#include "material.h"

#include <cstdint>

struct HitResult
{
	Vector3 hitPoint{ 0, 0, 0 }; // point of intersection
	Vector3 hitNormal{ 0, 0, 0 }; // normal at the point of intersection, pointing outward from the geometry regardless of hit side.
	Material* material = nullptr; // material of the object that was hit
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

