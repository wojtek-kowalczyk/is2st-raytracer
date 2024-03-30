#include "camera.h"

#include "mathHelpers.h"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY)
	: m_position(position), m_forward(forward), m_resolutionX(resolutionX), m_resolutionY(resolutionY)
{
}

OrthographicCamera::OrthographicCamera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY, float size)
	: Camera(position, forward, resolutionX, resolutionY), m_size(size)
{ 
}

Ray OrthographicCamera::ConstructRay(float pixelX, float pixelY) const
{
	float aspectRatio = m_resolutionX / (float)m_resolutionY;
	float x = ToCanonicalSpace(pixelX, (float)m_resolutionX) * aspectRatio * m_size;
	float y = ToCanonicalSpace(pixelY, (float)m_resolutionY) * m_size;
	Ray ray(m_position + Vector3{ x, y, 0 }, m_forward);

	return ray;
}

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& forward, int resolutionX, int resolutionY, float fov)
	: Camera(position, forward, resolutionX, resolutionY), m_degreesFOV(fov)
{
}

Ray PerspectiveCamera::ConstructRay(float pixelX, float pixelY) const
{
	float aspectRatio = m_resolutionX / (float)m_resolutionY;
	const float toRadians = (float)M_PI / 180.0f;
	double Px = ToCanonicalSpace(pixelX, (float)m_resolutionX) * tan(m_degreesFOV / 2 * toRadians) * aspectRatio;
	double Py = ToCanonicalSpace(pixelY, (float)m_resolutionY) * tan(m_degreesFOV / 2 * toRadians);
	Vector3 rayDirection = Vector3((float)Px, (float)Py, m_position.z + 1) - m_position;
	rayDirection.Normalize();

	return Ray(m_position, rayDirection);
}
