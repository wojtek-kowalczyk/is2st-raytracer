#include <ios>
#include <iostream>
#include <ostream>
#include <cassert>

#include "primitives/plane.h"
#include "ray.h"
#include "vector3.h"
#include "buffer.h"
#include "camera.h"

#include "exampleScenes.h"

static constexpr int NUMBER_SAMPLES = 1;
static constexpr int MAX_BOUNCES = 8;

void RenderScene(const Scene& scene, const Camera& camera, Buffer& target)
{
	const float pixelSize = 1.0f;

	for (int y = 0; y < target.GetHeight(); y++)
	{
		for (int x = 0; x < target.GetWidth(); x++)
		{
			Color finalColor = Color(0,0,0, 1.0f);

			for (int sample = 0; sample < NUMBER_SAMPLES; sample++)
			{
				Ray ray = camera.ConstructRay(x, y);
				Color color = scene.TraceRay(ray, MAX_BOUNCES).Clamped();
				finalColor += color;
			}

			finalColor /= NUMBER_SAMPLES;

			target.ColorAt(x, y) = Color::ToInt(finalColor);
		}	
	}
}

int main()
{
	Buffer perspCameraTarget(600, 400);
	perspCameraTarget.ClearColor(0xFF000000);

	PerspectiveCamera perspCamera(Vector3{ 0, 0, 0 }, perspCameraTarget.GetWidth(), perspCameraTarget.GetHeight(), 45.0f);

	Scene scene = ExampleScenes::CreateSimple();
	
	RenderScene(scene, perspCamera, perspCameraTarget);

	perspCameraTarget.SaveToFile("render_persp.tga");

	return 0;
}