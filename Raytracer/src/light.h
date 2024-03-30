#pragma once

#include "color.h"

class Light
{
public:
	Light(Color color) : m_color(color) {}
	
	virtual Vector3 GetDirection() const = 0;
	
	Color GetColor() const { return m_color; }

protected:
	Color m_color;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight(Color color, Vector3 direction) : Light(color), m_direction(direction) {}

	virtual Vector3 GetDirection() const override { return m_direction; }

private:
	Vector3 m_direction;
};

//class PointLight : public Light
//{
//	Vector3 position;
//};

//class SpotLight : public Light
//{
//	Vector3 position;
//	Vector3 direction;
//	float angle;
//};