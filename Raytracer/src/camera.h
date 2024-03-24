#pragma once

#include "vector3.h"
#include "ray.h"

class OrthographicCamera
{
public:
	OrthographicCamera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY);
	Ray ConstructRay(int pixelX, int pixelY) const;

private:
	Vector3 m_position;
	Vector3 m_forward;
	int m_resolutionX;
	int m_resolutionY;
};