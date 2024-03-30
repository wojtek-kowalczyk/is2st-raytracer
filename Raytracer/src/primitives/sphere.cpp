#include "sphere.h"

Sphere::Sphere(Vector3 center, float radius) : SceneObject(), center(center), radius(radius)
{
}

bool Sphere::Hit(Ray ray, HitResult& outHitResult) const
{
	outHitResult.color = this->color;

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

bool Sphere::Hit(Ray ray) const
{
	HitResult _;
	return Hit(ray, _);
}

// TODO : PIOTR
// This is left for reference to implement adaptive anti-aliasing using the new system.
// After that's done, please remove this code.

#if 0 

float Sphere::aaFactor(float x, float y, Sphere sphere, Camera& camera, float size, int failsafe)
{
	int hitSum = 0;
	if (failsafe >= 2)
	{
		Ray ray = camera.ConstructRay(x, y);
		return (float)sphere.Hit(ray);
	}

	float hits[4] = {};
	float halfSize = size / 2.0f;

	hits[0] = aaFactor(x, y, sphere, camera, halfSize, failsafe + 1);
	hits[1] = aaFactor(x + halfSize, y, sphere, camera, halfSize, failsafe + 1);
	hits[2] = aaFactor(x, y + halfSize, sphere, camera, halfSize, failsafe + 1);
	hits[3] = aaFactor(x + halfSize, y + halfSize, sphere, camera, halfSize, failsafe + 1);
	float sumOfHits = hits[0] + hits[1] + hits[2] + hits[3];

	return sumOfHits / 4.0f;
}

unsigned int Sphere::finalColor(unsigned int color, float aaFactor)
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
#endif

std::ostream& operator<<(std::ostream& os, const Sphere& s)
{
	os << "Center: " << s.center << ", Radius: " << s.radius;
	return os;
}
