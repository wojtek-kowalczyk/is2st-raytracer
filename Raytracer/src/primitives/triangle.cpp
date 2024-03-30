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
	outHitResult.color = this->color;

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

	return isInsideTriangle;
}

bool Triangle::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
}

float Triangle::aaFactor(float x, float y, Triangle triangle, Camera& camera, float size, int failsafe) {
	int hitSum = 0;
	if (failsafe >= 2) {
		Ray ray = camera.ConstructRay(x, y);
		return (float)triangle.Hit(ray); // TODO : awkward base class call
	}

	float hits[4] = {};
	float halfSize = size / 2.0f;

	hits[0] = aaFactor(x, y, triangle, camera, halfSize, failsafe + 1);
	hits[1] = aaFactor(x + halfSize, y, triangle, camera, halfSize, failsafe + 1);
	hits[2] = aaFactor(x, y + halfSize, triangle, camera, halfSize, failsafe + 1);
	hits[3] = aaFactor(x + halfSize, y + halfSize, triangle, camera, halfSize, failsafe + 1);
	float sumOfHits = hits[0] + hits[1] + hits[2] + hits[3];

	return sumOfHits / 4.0f;
}

unsigned int Triangle::finalColor(unsigned int color, float aaFactor) {
	unsigned char alpha = (color >> 24) & 0xFF;
	unsigned char r = (color >> 16) & 0xFF;
	unsigned char g = (color >> 8) & 0xFF;
	unsigned char b = color & 0xFF;

	unsigned char finalAlpha = (unsigned char)(alpha * aaFactor);
	unsigned char finalR = (unsigned char)(r * aaFactor);
	unsigned char finalG = (unsigned char)(g * aaFactor);
	unsigned char finalB = (unsigned char)(b * aaFactor);

	unsigned int finalColor = (finalAlpha << 24) | (finalR << 16) | (finalG << 8) | finalB;
	return finalColor;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	os << "V1: " << t.v1 << ", V2: " << t.v2 << ", V3: " << t.v3;
	return os;
}
