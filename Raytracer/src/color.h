#pragma once

#include "vector3.h"
#include "stdint.h"

class Color
{
public:
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t = 255);
	Color(float r, float g, float b, float a = 1.0f);

	void Clamp();
	Color Clamped() const;
	bool IsClamped() const;

	static uint32_t ToInt(const Color& color);
	static Color FromInt(uint32_t color);

	Color operator+(const Color& other) const;
	Color operator*(const Color& other) const;
	Color operator*(float scalar) const;
	Color& operator+=(const Color& other);
	Color& operator*=(const Color& other);
	Color& operator*=(float scalar);
	
	friend std::ostream& operator<<(std::ostream& os, const Color& color);

private:
	float r, g, b, a;
};
