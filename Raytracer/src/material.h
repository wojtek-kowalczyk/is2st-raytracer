#pragma once

#include "color.h"

enum class MaterialType
{
	Diffuse,
	Reflective,
	Refractive,
	Emissive,
};

struct Material
{
	Color color;				// albedo, should be clamped to [0,1]
	float ior;					// index of refraction, 1.52 glass, 1.33 water, 1.0 vacuum
	float roughness;			// 0 - perfectly smooth, 1 - perfectly diffuse

	MaterialType type;

	static Material* Default()
	{
		Material* mat = new Material{ Color(1, 1, 1, 1.0f), 1.52f, 0.0f, MaterialType::Diffuse };

		return mat;
	}
};
