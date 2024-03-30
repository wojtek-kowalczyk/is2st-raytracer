#include "triangle.h"

#include <ostream>
#include <cassert>
#include <math.h>

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3)
	: v1(v1), v2(v2), v3(v3)
{
}

bool Triangle::Hit(Ray ray, HitResult& outHitResult) const
{
	Vector3 edgeV1V2 = v2 - v1;
	Vector3 edgeV2V3 = v3 - v2;
	Vector3 edgeV3V1 = v1 - v3;
	Vector3 triangleNormal = Vector3::Cross(edgeV1V2, edgeV2V3);

	float dotRayDirectionTriangleNormal = Vector3::Dot(ray.direction, triangleNormal);
	bool isOrthogonalToNormal = fabs(dotRayDirectionTriangleNormal) < 1e-6;
	bool isParallelToTriangle = isOrthogonalToNormal;
	if (isParallelToTriangle)
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
	Vector3 cross2 = Vector3::Cross(edgeV2V3, v2ToIntersection);
	Vector3 cross3 = Vector3::Cross(edgeV3V1, v3ToIntersection);

	// >= makes it so we can hit edges and vertices

	bool isInsideTriangle = 
		Vector3::Dot(triangleNormal, cross1) >= 0 &&
		Vector3::Dot(triangleNormal, cross2) >= 0 &&
		Vector3::Dot(triangleNormal, cross3) >= 0;

	outHitResult.hitPoint = intersectionPoint;
	outHitResult.hitNormal = triangleNormal;
	outHitResult.material = m_material;

	return isInsideTriangle;
}

bool Triangle::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	os << "V1: " << t.v1 << ", V2: " << t.v2 << ", V3: " << t.v3;
	return os;
}
