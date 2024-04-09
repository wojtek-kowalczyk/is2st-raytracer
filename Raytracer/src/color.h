#pragma once

#include "vector3.h"
#include "stdint.h"

class Color
{
public:
	// constexpr constructors allow us to define constexpr members of this type
	constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) { }
	constexpr Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) { }

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
