#pragma once

#include "vector3.h"
#include "ray.h"

class Camera
{
public:
	virtual Ray ConstructRay(int pixelX, int pixelY) const = 0;

protected:
	Camera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY);

	Vector3 m_position;
	Vector3 m_forward;
	int m_resolutionX;
	int m_resolutionY;
};

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY, float size);
	virtual Ray ConstructRay(int pixelX, int pixelY) const override;

private:
	float m_size; // The camera can see size*2 units vertically and size*2*aspectRatio units horizontally
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY, float fov = 45.0f);
	virtual Ray ConstructRay(int pixelX, int pixelY) const override;

private:
	float m_degreesFOV; 
};
