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

	outHitResult.color = this->color;

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

bool Plane::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
}

float Plane::aaFactor(float x, float y, Plane plane, Camera& camera, float size, int failsafe)
{
	int hitSum = 0;
	if (failsafe >= 2)
	{
		Ray ray = camera.ConstructRay(x, y);
		return (float)plane.Hit(ray); // awkward base class call
	}

	float hits[4] = {};
	float halfSize = size / 2.0f;

	hits[0] = aaFactor(x, y, plane, camera, halfSize, failsafe + 1);
	hits[1] = aaFactor(x + halfSize, y, plane, camera, halfSize, failsafe + 1);
	hits[2] = aaFactor(x, y + halfSize, plane, camera, halfSize, failsafe + 1);
	hits[3] = aaFactor(x + halfSize, y + halfSize, plane, camera, halfSize, failsafe + 1);
	float sumOfHits = hits[0] + hits[1] + hits[2] + hits[3];
	return sumOfHits / 4.0f;
}

unsigned int Plane::finalColor(unsigned int color, float aaFactor)
{
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

std::ostream& operator<<(std::ostream& os, const Plane& p)
{
	os << "Point: " << p.point << ", Normal: " << p.normal;
	return os;
}
