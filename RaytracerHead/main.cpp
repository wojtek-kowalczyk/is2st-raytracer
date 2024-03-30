#include <iostream>
#include <ostream>

#include "ray.h"
#include "vector3.h"
#include "buffer.h"
#include "camera.h"
#include "scene.h"

#include "primitives/sphere.h"

/*
* Exercise 2 Checklist
* 
* Prosz� zaimplementowa� klasy obrazu...........................(DONE)
* nat�enia.....................................................(CAN USE Vector3) 
* kamery (ortogonaln� oraz perpsektywiczn�).....................(DONE),
* wyrenderowa� obraz zawieraj�cy dwie kule: persp i ortho.......(DONE)
* 
* Nale�y zaimplementowa� podan� metod� antyaliasingu adaptacyjnego lub w�asn�, zaproponowan� metod�. (TODO)
*/

void Exercise2()
{
	Buffer orthoCameraTarget(600, 400);
	orthoCameraTarget.ClearColor(0xFF000000);
	Buffer perspCameraTarget(600, 400);
	perspCameraTarget.ClearColor(0xFF000000);

	Sphere sphere1(Vector3{ 0, 0, 0 }, 1.0f);
	sphere1.color = 0xFFFF0000;
	Sphere sphere2(Vector3{ 1, 0, 0 }, 1.0f);
	sphere2.color = 0xFF00FF00;
	Scene scene;
	scene.AddObject(&sphere1);
	scene.AddObject(&sphere2);

	OrthographicCamera orthoCamera(Vector3{ 0, 0, -5 }, Vector3{ 0, 0, 1 }, orthoCameraTarget.GetWidth(), orthoCameraTarget.GetHeight(), 3.0f);
	PerspectiveCamera perspCamera(Vector3{ 0, 0, -5 }, Vector3{ 0, 0, 1 }, perspCameraTarget.GetWidth(), perspCameraTarget.GetHeight(), 45.0f);
	
	const float pixelSize = 1.0f;

	for (int y = 0; y < orthoCameraTarget.GetHeight() - 1; y++)
	{
		for (int x = 0; x < orthoCameraTarget.GetWidth() - 1; x++)
		{
			// DO othrographic
			{
				Ray ray1 = orthoCamera.ConstructRay(x + pixelSize * 0.25f - 0.5f, y + pixelSize * 0.25f - 0.5f);
				Ray ray2 = orthoCamera.ConstructRay(x + pixelSize * 0.75f - 0.5f, y + pixelSize * 0.25f - 0.5f);
				Ray ray3 = orthoCamera.ConstructRay(x + pixelSize * 0.25f - 0.5f, y + pixelSize * 0.75f - 0.5f);
				Ray ray4 = orthoCamera.ConstructRay(x + pixelSize * 0.75f - 0.5f, y + pixelSize * 0.75f - 0.5f);

				Color color1 = scene.TraceRay(ray1);
				Color color2 = scene.TraceRay(ray2);
				Color color3 = scene.TraceRay(ray3);
				Color color4 = scene.TraceRay(ray4);

				Color finalColor = (color1 + color2 + color3 + color4) * 0.25f;

				orthoCameraTarget.ColorAt(x, y) = Color::ToInt(finalColor);
			}

#if 0 // TMP disabled

			// DO Perspective
			{
				perspCameraTarget.ColorAt(x, y) = sphere2.finalColor(0xFF00FF00, sphere2.aaFactor((float)x, (float)y, sphere2, perspCamera, 1.0f));

				unsigned int sphere1Color = sphere1.finalColor(0xFFFF0000, sphere1.aaFactor((float)x, (float)y, sphere1, perspCamera, 1.0f));



				float sphere1Alpha = static_cast<float>((sphere1Color >> 24) & 0xFF) / 255.0f;

				perspCameraTarget.ColorAt(x, y) = ((unsigned char)(((sphere1Color >> 24) & 0xFF) * sphere1Alpha) << 24) |
												  ((unsigned char)(((sphere1Color >> 16) & 0xFF) * sphere1Alpha) << 16) |
												  ((unsigned char)(((sphere1Color >> 8) & 0xFF) * sphere1Alpha) << 8) | 
												  ((unsigned char)(((sphere1Color) & 0xFF) * sphere1Alpha))
												  +
												  ((unsigned char)(((perspCameraTarget.ColorAt(x, y) >> 24) & 0xFF) * (1.0f - sphere1Alpha)) << 24) |
												  ((unsigned char)(((perspCameraTarget.ColorAt(x, y) >> 16) & 0xFF) * (1.0f - sphere1Alpha)) << 16) |
												  ((unsigned char)(((perspCameraTarget.ColorAt(x, y) >> 8) & 0xFF) * (1.0f - sphere1Alpha)) << 8) |
												  ((unsigned char)(((perspCameraTarget.ColorAt(x, y)) & 0xFF) * (1.0f - sphere1Alpha)));

				
			}
#endif	
		}
	}

	orthoCameraTarget.SaveToFile("render_ortho.tga");
	perspCameraTarget.SaveToFile("render_persp.tga");
}

int main()
{
	Exercise2();

	return 0;
}