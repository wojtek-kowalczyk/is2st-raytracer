#pragma once

#include <ostream>

struct Vector3 
{
    Vector3();
    Vector3(float x, float y, float z);

    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };

        struct
        {
            float r;
            float g;
            float b;
        };
    };

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    friend Vector3 operator*(float scalar, const Vector3& vector);
    Vector3 operator/(float scalar) const;
    Vector3 operator-() const;

    void Normalize();
    Vector3 Normalized() const;
    float Magnitude() const;
    float SquareMagnitude() const;
    bool IsNormalized() const;

    static Vector3 Reflect(const Vector3& incident, const Vector3& normal);
    static bool Refract(const Vector3& incident, const Vector3& normal, float ior, Vector3& outRefractedVector);
    static float Dot(const Vector3& a, const Vector3& b);
    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static float AngleRad(const Vector3& a, const Vector3& b);
    static float AngleDeg(const Vector3& a, const Vector3& b);

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};
