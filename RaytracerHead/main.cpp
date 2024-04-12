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

Color antialias(float x, float y, const Scene& scene, const Camera& camera, float pixelSize, int threshold = 0, bool force = false) 
{
	// TODO : fix antialiasing
	return scene.TraceRay(camera.ConstructRay(x, y)).Clamped();

	// pixelSize *= 1.1f;

	if (threshold >= 2 || force)
	{
		Ray ray1 = camera.ConstructRay(x, y);
		Ray ray2 = camera.ConstructRay(x + pixelSize, y);
		Ray ray3 = camera.ConstructRay(x, y + pixelSize);
		Ray ray4 = camera.ConstructRay(x + pixelSize, y + pixelSize);

		// Ray ray1 = camera.ConstructRay(x + 0.25f * pixelSize, y + 0.25f * pixelSize);
		// Ray ray2 = camera.ConstructRay(x + 0.25f * pixelSize, y + 0.75f * pixelSize);
		// Ray ray3 = camera.ConstructRay(x + 0.75f * pixelSize, y + 0.25f * pixelSize);
		// Ray ray4 = camera.ConstructRay(x + 0.75f * pixelSize, y + 0.75f * pixelSize);

		Color color1 = scene.TraceRay(ray1).Clamped();
		Color color2 = scene.TraceRay(ray2).Clamped();
		Color color3 = scene.TraceRay(ray3).Clamped();
		Color color4 = scene.TraceRay(ray4).Clamped();
		Color finalColor = (color1 + color2 + color3 + color4) * 0.25f;

		return finalColor;
	}
	else 
	{
		float halfSize = pixelSize / 2.0f;

		Color color3 = antialias(x, y, scene, camera, halfSize, threshold + 1);
		Color color1 = antialias(x + halfSize, y, scene, camera, halfSize, threshold + 1);
		Color color2 = antialias(x, y + halfSize, scene, camera, halfSize, threshold + 1);
		Color color4 = antialias(x + halfSize, y + halfSize, scene, camera, halfSize, threshold + 1);

		Color finalColor = (color1 + color2 + color3 + color4) * 0.25f;

		return finalColor;
	}
}

void RenderScene(const Scene& scene, const Camera& camera, Buffer& target)
{
	const float pixelSize = 1.0f;

	for (int y = 0; y < target.GetHeight(); y++)
	{
		for (int x = 0; x < target.GetWidth(); x++)
		{
			Color finalColor = antialias((float)x, (float)y, scene, camera, pixelSize, 0, true);
			target.ColorAt(x, y) = Color::ToInt(finalColor);
		}	
	}
}

int main()
{
	Buffer perspCameraTarget(600, 400);
	perspCameraTarget.ClearColor(0xFF000000);

	PerspectiveCamera perspCamera(Vector3{ 0, 0, 0 }, perspCameraTarget.GetWidth(), perspCameraTarget.GetHeight(), 45.0f);

	// Scene scene = ExampleScenes::CreateCornellBox();
	Scene scene = ExampleScenes::CreateSimple();
	
	RenderScene(scene, perspCamera, perspCameraTarget);

	perspCameraTarget.SaveToFile("render_persp.tga");

	return 0;
}