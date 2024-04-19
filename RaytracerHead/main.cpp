#include "primitives/plane.h"
#include "ray.h"
#include "vector3.h"
#include "buffer.h"
#include "camera.h"

#include "exampleScenes.h"

#include <bits/chrono.h>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <ratio>

static constexpr int NUMBER_SAMPLES = 10;
static constexpr int MAX_BOUNCES = 8;

void RenderScene(const Scene& scene, const Camera& camera, Buffer& target)
{
	const float pixelSize = 1.0f;

	auto startTime = std::chrono::steady_clock::now();
	int linesRendered = 0;
   
   	#pragma omp parallel for
	for (int y = 0; y < target.GetHeight(); y++)
	{
		for (int x = 0; x < target.GetWidth(); x++)
		{
			const Color startingColor = Color(1, 1, 1, 1.0f);

			Color finalColor = Color(0, 0, 0, 1.0f);

			for (int sample = 0; sample < NUMBER_SAMPLES; sample++)
			{
				const Ray ray = camera.ConstructRay((float)x, (float)y);
				const Color color = scene.TraceRay(ray, startingColor, MAX_BOUNCES).Clamped();
				finalColor += color;
			}

			finalColor /= NUMBER_SAMPLES;

			target.ColorAt(x, y) = Color::ToInt(finalColor);
		}

		// ++linesRendered;
		// std::cout << linesRendered << "/" << target.GetHeight() << '\n';
	}

	auto endTime = std::chrono::steady_clock::now();
	unsigned long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	printf("Rendering took: %.2fs\n", milliseconds * 0.001);
}

int main()
{
	Buffer perspCameraTarget(600, 400);
	perspCameraTarget.ClearColor(0xFF000000);

	PerspectiveCamera perspCamera(Vector3{ 0, 0, 0 }, perspCameraTarget.GetWidth(), perspCameraTarget.GetHeight(), 45.0f);

	Scene scene = ExampleScenes::CreateCornellBox();
	
	RenderScene(scene, perspCamera, perspCameraTarget);

	perspCameraTarget.SaveToFile("render_persp.tga");

	return 0;
}