#include "color.h"

#include <math.h>
#include <assert.h>

static float ClampColorChannel(float value)
{
	return fmin(fmax(value, 0.0f), 1.0f);
}

void Color::Clamp()
{
	r = ClampColorChannel(r);
	g = ClampColorChannel(g);
	b = ClampColorChannel(b);
	a = ClampColorChannel(a);
}

Color Color::Clamped() const
{
	return Color(
		ClampColorChannel(r),
		ClampColorChannel(g),
		ClampColorChannel(b),
		ClampColorChannel(a));
}

bool Color::IsClamped() const
{
	return  r >= 0.0f && r <= 1.0f &&
			g >= 0.0f && g <= 1.0f &&
			b >= 0.0f && b <= 1.0f &&
			a >= 0.0f && a <= 1.0f;
}

uint32_t Color::ToInt(const Color& color)
{
	uint8_t r = (uint8_t)(ClampColorChannel(color.r) * 255.0f);
	uint8_t g = (uint8_t)(ClampColorChannel(color.g) * 255.0f);
	uint8_t b = (uint8_t)(ClampColorChannel(color.b) * 255.0f);
	uint8_t a = (uint8_t)(ClampColorChannel(color.a) * 255.0f);

	uint32_t intColor = 0;
	intColor |= a << 24;
	intColor |= r << 16;
	intColor |= g << 8;
	intColor |= b;

	return intColor;
}

Color Color::FromInt(uint32_t color)
{
	uint8_t a = (color >> 24) & 0xFF;
	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color & 0xFF;

	return Color(r, g, b, a);
}

Color Color::operator+(const Color& other) const
{
	return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Color Color::operator*(const Color& other) const
{
	return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

Color Color::operator*(float scalar) const
{
	return Color(r * scalar, g * scalar, b * scalar, a * scalar);
}

Color Color::operator/(float divisor) const
{
	assert(divisor != 0.0f);
	return (*this) * (1.0f / divisor);
}

Color& Color::operator+=(const Color& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;

	return *this;
}

Color& Color::operator*=(const Color& other)
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
	a *= other.a;

	return *this;
}

Color& Color::operator*=(float scalar)
{
	r *= scalar;
	g *= scalar;
	b *= scalar;
	a *= scalar;

	return *this;
}

Color& Color::operator/=(float divisor)
{
	assert(divisor != 0.0f);

	r /= divisor;
	g /= divisor;
	b /= divisor;
	a /= divisor;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
	os << "RGBA(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
	return os;
}
