#pragma once

#include "color.h"

class Light
{
public:
	Light(Color color) : m_color(color) {}
	
	virtual Vector3 GetDirection(Vector3 to) const = 0; // from light to given vector
	
	Color GetColor() const { return m_color; }

protected:
	Color m_color;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight(Color color, Vector3 direction) : Light(color), m_direction(direction) {}

	virtual Vector3 GetDirection(Vector3 _) const override { abort() ; return m_direction; } // TODO : this dir is probably flipped

private:
	Vector3 m_direction;
};

class PointLight : public Light
{
public:
	PointLight(Color color, Vector3 position) : Light(color), m_position(position) {}
	virtual Vector3 GetDirection(Vector3 to) const override { return to - m_position; }

private:
	Vector3 m_position;
};

//class SpotLight : public Light
//{
//	Vector3 position;
//	Vector3 direction;
//	float angle;
//};