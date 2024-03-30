#pragma once

#include "vector3.h"
#include "ray.h"
#include <cstdint>

class SceneObject 
{
public:
    virtual bool Hit(Ray ray, HitResult& outHitResult) const = 0;
    uint32_t color; // TODO : TMP - switch to materials later
    
    virtual bool Hit(Ray ray) const = 0;

private:
};