#include "primitives.h"

#include <cassert>

bool Sphere::Hit(Ray ray) const
{
	Vector3 oc = ray.origin - center;

	float a = Vector3::Dot(ray.direction, ray.direction);
	float b = Vector3::Dot(oc, ray.direction);
	float c = Vector3::Dot(oc, oc) - radius * radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float x1 = (-b - sqrt(discriminant)) / a;
		float x2 = (-b + sqrt(discriminant)) / a;

		if (x1 > 0 || x2 > 0)
		{
			return true;
		}
	}
	else if (discriminant == 0) // floating point comparison
	{
		float x = -b / a;

		if (x > 0)
		{
			return true;
		}
	}

	return false;
}

bool Plane::Hit(Ray ray) const
{
	assert(normal.IsNormalized());
	assert(ray.direction.IsNormalized());

	float denominator = Vector3::Dot(normal, ray.direction);
	if (denominator > 1e-6) // if denom is zero, the ray is parallel
	{
		Vector3 toPlanePointFromRayOrigin = point - ray.origin;
		float t = Vector3::Dot(toPlanePointFromRayOrigin, normal) / denominator;
		return (t >= 0);
	}

	return false;
}

bool Triangle::Hit(Ray ray) const
{
	Vector3 edgeV1V2 = v2 - v1;
	Vector3 edgeV1V3 = v3 - v1;
	Vector3 triangleNormal = Vector3::Cross(edgeV1V2, edgeV1V3);

	float dotRayDirectionTriangleNormal = Vector3::Dot(ray.direction, triangleNormal);
	bool isParallel = dotRayDirectionTriangleNormal < 1e-6;
	if (isParallel)
	{
		return false;
	}

	float distanceFromRayOriginToPlane = Vector3::Dot(v1 - ray.origin, triangleNormal) / dotRayDirectionTriangleNormal;

	bool isIntersectionBehindRayOrigin = distanceFromRayOriginToPlane < 0;
	if (isIntersectionBehindRayOrigin)
	{
		return false;
	}

	Vector3 intersectionPoint = ray.origin + ray.direction * distanceFromRayOriginToPlane;

	Vector3 v1ToIntersection = intersectionPoint - v1;
	Vector3 v2ToIntersection = intersectionPoint - v2;
	Vector3 v3ToIntersection = intersectionPoint - v3;

	Vector3 cross1 = Vector3::Cross(edgeV1V2, v1ToIntersection);
	Vector3 cross2 = Vector3::Cross(edgeV1V3, v2ToIntersection);
	Vector3 edgeV2V3 = v3 - v2;
	Vector3 cross3 = Vector3::Cross(edgeV2V3, v3ToIntersection);

	bool isInsideTriangle = 
		Vector3::Dot(triangleNormal, cross1) >= 0 &&
		Vector3::Dot(triangleNormal, cross2) >= 0 &&
		Vector3::Dot(triangleNormal, cross3) >= 0;

	return isInsideTriangle;
}
