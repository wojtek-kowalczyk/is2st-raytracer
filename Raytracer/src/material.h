#pragma once

#include "color.h"

struct Material
{
	Color color;				// albedo, should be clamped to [0,1]
	float specular_amount;		// [0,infinity]. 0 = matt
	float specular_coeff;		// (0, infinity). for phong lighting a.k.a shineness.
	float reflect_fraction;		// [0,1]. 1 == total reflection, i.e. a perfect mirror
};
