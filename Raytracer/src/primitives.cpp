#include "primitives.h"
#include "vector3.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <math.h>

// TODO : write unit tests for hit point

bool Sphere::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
}


bool Sphere::Hit(Ray ray, HitResult& outHitResult) const
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

		if (x1 > 0)
		{
			outHitResult.hitPoint = ray.origin + ray.direction * x1;
			return true;
		}
		if (x2 > 0)
		{
			outHitResult.hitPoint = ray.origin + ray.direction * x2;
			return true;
		}
	}
	else if (discriminant == 0) // floating point comparison
	{
		float x = -b / a;

		if (x > 0)
		{
			outHitResult.hitPoint = ray.origin + ray.direction * x;
			return true;
		}
	}

	return false;
}

float Sphere::aaFactor(float x, float y, Sphere sphere, Camera& camera, float size, int failsafe) {
	int hitSum = 0;
	if (failsafe >= 2) {
		// put stuff here
		Ray ray = camera.ConstructRay(x, y);
		//std::cout << "big boom" << std::endl;
		return (float)sphere.Hit(ray);
	}

	float hits[4] = {};
	float halfSize = size / 2.0f;

	hits[0] = aaFactor(x, y, sphere, camera, halfSize, failsafe + 1);
	hits[1] = aaFactor(x + halfSize, y, sphere, camera, halfSize, failsafe + 1);
	hits[2] = aaFactor(x, y + halfSize, sphere, camera, halfSize, failsafe + 1);
	hits[3] = aaFactor(x + halfSize, y + halfSize, sphere, camera, halfSize, failsafe + 1);
	//Ray ray = camera.ConstructRay(x, y); //construct ray on floats
	//if (sphere.Hit(ray)) {
	//	hitSum += sphere.Hit(ray);
	//	aaColor(x, y, sphere, color, camera, halfSize, failsafe + 1);
	//}
	//ray = camera.ConstructRay(x + 1, y);
	//if (sphere.Hit(ray)) {
	//	hitSum += sphere.Hit(ray);
	//	aaColor(x, y, sphere, color, camera, halfSize, failsafe + 1);
	//}
	//camera.ConstructRay(x, y + 1);
	//if (sphere.Hit(ray)) {
	//	hitSum += sphere.Hit(ray);
	//	aaColor(x, y, sphere, color, camera, halfSize, failsafe + 1);
	//}
	//camera.ConstructRay(x + 1, y + 1);
	//if (sphere.Hit(ray)) {
	//	hitSum += sphere.Hit(ray);
	//	aaColor(x, y, sphere, color, camera, halfSize, failsafe + 1);
	//}
	// 
	//perspCameraTarget.ColorAt(x, y) = sphere1.Hit(ray) ? 0xFFFF0000 : 0xFF000000;
	//float colFactor = (float)colSum / 4.0f;
	//unsigned char finalAlpha = (0xFF >> 24) * colFactor; // is necessary?
	//unsigned char finalRed = ((0x00FF0000 >> 16) & 0xFF) * colFactor;
	//if failsafe == 0 do the color already
	float sumOfHits = hits[0] + hits[1] + hits[2] + hits[3];
	//std::cout << sumOfHits / 4.0f << std::endl;
	return sumOfHits / 4.0f;
}

unsigned int Sphere::finalColor(unsigned int color, float aaFactor) {
	unsigned char r = (color >> 16) & 0xFF;
	unsigned char g = (color >> 8) & 0xFF;
	unsigned char b = color & 0xFF;

	unsigned char finalR = (unsigned char)(r * aaFactor);
	unsigned char finalG = (unsigned char)(g * aaFactor);
	unsigned char finalB = (unsigned char)(b * aaFactor);

	unsigned int finalColor = (0xFF << 24) | (finalR << 16) | (finalG << 8) | finalB;
	return finalColor;
}

bool Plane::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
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
	outHitResult.hitPoint = ray.origin + ray.direction * t;
	return (t >= 0);
}

bool Triangle::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
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

	return isInsideTriangle;
}
