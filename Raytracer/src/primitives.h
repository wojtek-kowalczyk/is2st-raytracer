#pragma once

#include "vector3.h"

struct Sphere
{
    Vector3 center;
    float radius;
};

struct Plane 
{
    Vector3 point;
    Vector3 normal;
};

struct Triangle 
{
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;
};

struct Ray 
{
    Vector3 origin;
    Vector3 direction;
};