#pragma once

#include <ostream>

struct Vector3 
{
    Vector3();
    Vector3(float x, float y, float z);

    float x;
    float y;
    float z;

    Vector3& operator+(const Vector3& other);
    Vector3& operator-(const Vector3& other);
    Vector3& operator*(float scalar);

    void Normalize();
    Vector3 Normalized() const;
    float Magnitude() const;

    static float Dot(const Vector3& a, const Vector3& b);
    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static float AngleRad(const Vector3& a, const Vector3& b);
    static float AngleDeg(const Vector3& a, const Vector3& b);

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};