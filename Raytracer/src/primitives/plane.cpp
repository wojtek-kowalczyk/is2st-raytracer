#include "plane.h"

#include <cassert>
#include "../ray.h"

Plane::Plane(Vector3 point, Vector3 normal):
	point(point), normal(normal)
{
	this->normal.Normalize();
}

bool Plane::Hit(Ray ray, HitResult& outHitResult) const
{
	assert(normal.IsNormalized());
	assert(ray.direction.IsNormalized());

	float denominator = Vector3::Dot(normal, ray.direction);
	if (fabs(denominator) < 0.000001f) // if denom is zero, the ray is parallel
	{
		return false;
	}

	Vector3 toPlanePointFromRayOrigin = point - ray.origin;
	float t = Vector3::Dot(toPlanePointFromRayOrigin, normal) / denominator;

	outHitResult.material = m_material;
	outHitResult.hitNormal = normal;
	outHitResult.hitPoint = ray.origin + ray.direction * t;

	return (t >= 0);
}

bool Plane::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
}

std::ostream& operator<<(std::ostream& os, const Plane& p)
{
	os << "Point: " << p.point << ", Normal: " << p.normal;
	return os;
}
