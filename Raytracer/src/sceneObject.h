#pragma once

#include "vector3.h"
#include "ray.h"
#include "material.h"

#include <cstdint>

class SceneObject 
{
public:
    virtual bool Hit(Ray ray, HitResult& outHitResult) const = 0;
    virtual bool Hit(Ray ray) const = 0;

    void SetMaterial(Material* material) { m_material = material; }

protected:
    Material* m_material;
};