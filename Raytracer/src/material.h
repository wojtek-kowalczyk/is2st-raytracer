#pragma once

#include "color.h"

struct Material
{
	Color color;				// albedo, should be clamped to [0,1]
	float Ka;		// [0,1]. 1 == total reflection, i.e. a perfect mirror
	float Kd;					// [0,infinity]. 0 = matt
	float Ks;		// [0,1]. 1 == total reflection, i.e. a perfect mirror
	float specularPow;		// (0, infinity). for phong lighting a.k.a shineness.

	static Material* Default()
	{
		Material* mat = new Material{ Color(1, 1, 1, 1.0f), 1.0f, 1.0f, 1.0f, 4.0f };

		return mat;
	}
};
