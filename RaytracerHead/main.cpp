#include <iostream>
#include <ostream>
#include <cassert>

#include "ray.h"
#include "vector3.h"
#include "buffer.h"
#include "camera.h"

#include "exampleScenes.h"

void RenderScene(const Scene& scene, const Camera& camera, Buffer& target)
{
	const float pixelSize = 1.0f;

	for (int y = 0; y < target.GetHeight() - 1; y++)
	{
		for (int x = 0; x < target.GetWidth() - 1; x++)
		{
			// TODO : implement a different antialiasing method

			// Simple 4x antialiasing

			Ray ray1 = camera.ConstructRay((x - 0.5f) + pixelSize * 0.25f, (y - 0.5f) + pixelSize * 0.25f);
			Ray ray2 = camera.ConstructRay((x - 0.5f) + pixelSize * 0.75f, (y - 0.5f) + pixelSize * 0.25f);
			Ray ray3 = camera.ConstructRay((x - 0.5f) + pixelSize * 0.25f, (y - 0.5f) + pixelSize * 0.75f);
			Ray ray4 = camera.ConstructRay((x - 0.5f) + pixelSize * 0.75f, (y - 0.5f) + pixelSize * 0.75f);

			Color color1 = scene.TraceRay(ray1).Clamped();
			Color color2 = scene.TraceRay(ray2).Clamped();
			Color color3 = scene.TraceRay(ray3).Clamped();
			Color color4 = scene.TraceRay(ray4).Clamped();

			Color finalColor = (color1 + color2 + color3 + color4) * 0.25f;

			target.ColorAt(x, y) = Color::ToInt(finalColor);
		}
	}
}

int main()
{
	Buffer orthoCameraTarget(600, 400);
	orthoCameraTarget.ClearColor(0xFF000000);
	Buffer perspCameraTarget(300, 150);
	perspCameraTarget.ClearColor(0xFF000000);

	OrthographicCamera orthoCamera(Vector3{ 0, 0, 0 }, orthoCameraTarget.GetWidth(), orthoCameraTarget.GetHeight(), 3.0f);
	PerspectiveCamera perspCamera(Vector3{ 0, 0, 0 }, perspCameraTarget.GetWidth(), perspCameraTarget.GetHeight(), 45.0f);

	//Scene scene = ExampleScenes::CreateCornellBox();
	Scene scene = ExampleScenes::CreateSimple();
	
	//RenderScene(scene, orthoCamera, orthoCameraTarget);
	RenderScene(scene, perspCamera, perspCameraTarget);

	orthoCameraTarget.SaveToFile("render_ortho.tga");
	perspCameraTarget.SaveToFile("render_persp.tga");

	return 0;
}