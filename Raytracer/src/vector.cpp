#include "vector3.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <math.h>
#include <cassert>
#include <iostream>

Vector3::Vector3() 
    : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
    Vector3 result = *this;

    result.x += other.x;
    result.y += other.y;
    result.z += other.z;

    return result;
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
    Vector3 result = *this;

    result.x -= other.x;
    result.y -= other.y;
    result.z -= other.z;

    return result;
}

Vector3 Vector3::operator*(float scalar) const
{
    Vector3 result = *this;

    result.x *= scalar;
    result.y *= scalar;
    result.z *= scalar;

    return result;
}

Vector3 Vector3::operator/(float scalar) const
{
    Vector3 result = *this;

    result.x /= scalar;
    result.y /= scalar;
    result.z /= scalar;

	return result;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) 
{
    os << '(' << v.x << ", " << v.y << ", " << v.z << ')';

    return os;
}


void Vector3::Normalize() 
{
    const float mag = Magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
}

Vector3 Vector3::Normalized() const
{
    Vector3 normalized = *this;
    normalized.Normalize();

    return normalized;
}

float Vector3::Magnitude() const
{
    float tmp = x*x + y*y + z*z;
    assert(tmp >= 0);

    if (tmp == 0)
    {
        std::cerr << "[WARNING] Vector3::Magnitude() called on zero vector. Make sure this isn't a mistake.\n";
    }

    return sqrt(tmp);
}

bool Vector3::IsNormalized() const
{
    return Magnitude() - 1.0f < 0.0001f;
}

Vector3 Vector3::Reflect(const Vector3& incident, const Vector3& normal)
{
    assert(normal.IsNormalized());

    return incident - normal * Vector3::Dot(incident, normal) * 2.0f;
    
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b) 
{
    return Vector3(
        (a.y * b.z) - (a.z * b.y),
        (a.x * b.z) - (a.z * b.x),
        (a.x * b.y) - (a.y * b.x)
    );
}

float Vector3::AngleRad(const Vector3& a, const Vector3& b) 
{
    return acos(Vector3::Dot(a, b) / (a.Magnitude() * b.Magnitude()));
}

float Vector3::AngleDeg(const Vector3& a, const Vector3& b) 
{
    return AngleRad(a, b) * (float)(180.0 / M_PI);
}
