#include "sphere.h"

#include <math.h>

Sphere::Sphere(Vector3 center, float radius) : SceneObject(), center(center), radius(radius)
{
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
			outHitResult.hitNormal = (outHitResult.hitPoint - center).Normalized();
			outHitResult.material = m_material;

			return true;
		}
		if (x2 > 0)
		{
			outHitResult.hitPoint = ray.origin + ray.direction * x2;
			outHitResult.hitNormal = -(outHitResult.hitPoint - center).Normalized();
			outHitResult.material = m_material;
			
			return true;
		}
	}
	else if (discriminant == 0) // floating point comparison
	{
		float x = -b / a;

		if (x > 0)
		{
			outHitResult.hitPoint = ray.origin + ray.direction * x;
			outHitResult.hitNormal = (outHitResult.hitPoint - center).Normalized();
			outHitResult.material = m_material;

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

std::ostream& operator<<(std::ostream& os, const Sphere& s)
{
	os << "Center: " << s.center << ", Radius: " << s.radius;
	return os;
}
