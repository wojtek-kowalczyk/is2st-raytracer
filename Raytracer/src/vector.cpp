#include "vector3.h"

#include <math.h>
#include <cassert>
#include <iostream>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <math.h>

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

Vector3 operator*(float scalar, const Vector3& vector) 
{
    return vector * scalar;
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
    return sqrt(SquareMagnitude());
}

float Vector3::SquareMagnitude() const 
{
    float value = x*x + y*y + z*z;
    assert(value >= 0);

    if (value == 0)
    {
        std::cerr << "[WARNING] Vector3::Magnitude() called on zero vector. Make sure this isn't a mistake.\n";
    }

    return value;
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

// Source: https://stackoverflow.com/questions/42218704/how-to-properly-handle-refraction-in-raytracing
static inline Vector3 refract(Vector3 i, Vector3 n, float eta)
{
    eta = 2.0f - eta;
    float cosi = Vector3::Dot(n, i);
    Vector3 o = (i * eta - n * (-cosi + eta * cosi));
    return o;
}

// Source: https://stackoverflow.com/questions/29758545/how-to-find-refraction-vector-from-incoming-vector-and-surface-normal
bool Vector3::Refract(const Vector3& incident, const Vector3& normal, float ior, Vector3& outRefractedVector) 
{
    Vector3 I = incident.Normalized();
    Vector3 N = normal.Normalized();

    bool hitFrontFace = Vector3::Dot(I, N) < 0;
    double ri = hitFrontFace ? ior : (1.0 / ior);
    outRefractedVector = refract(I, N, (float)ri);

    return true;
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

static float GetRandomFloat(float minInclusive, float maxInclusive)
{
    float random01 = (float)rand() / RAND_MAX;
    return minInclusive + random01 * (maxInclusive - minInclusive);
}

// Source: https://math.stackexchange.com/questions/1163260/random-directions-on-hemisphere-oriented-by-an-arbitrary-vector
Vector3 Vector3::RandomInsideUnitSphere()
{
    float x, y, z, d;

    do
    {
        x = GetRandomFloat(-1, 1);
        y = GetRandomFloat(-1, 1);
        z = GetRandomFloat(-1, 1);
        d = sqrtf(x * x + y * y + z * z);
    } while (d > 1);

    x = x / d;
    y = y / d;
    z = z / d;

    return Vector3(x, y, z);
}

Vector3 Vector3::RandomHemisphereDirection(Vector3 normal)
{
    Vector3 randomDirection = RandomInsideUnitSphere();
    
    if (Vector3::Dot(randomDirection, normal) < 0)
    {
		randomDirection = -randomDirection;
	}

    return randomDirection;
}
