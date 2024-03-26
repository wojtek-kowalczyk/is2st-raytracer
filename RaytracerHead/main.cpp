#include <iostream>
#include <ostream>

#include "primitives.h"
#include "vector3.h"
#include "buffer.h"
#include "camera.h"

void Exercise1() 
{
	std::cout << std::boolalpha; // print true/false instead of 1/0

	// 2.
	Vector3 a {1,2,3};
	Vector3 b {2, 3, 4};
	std::cout << "2. " << a + b << " | " << b + a << '\n';

	// 3.
	std::cout << "3. "<< Vector3::AngleDeg(Vector3{0,3,0}, Vector3{5,5,0}) << '\n';

	// 4.
	std::cout << "4. "<< Vector3::Cross(Vector3{4,5,1}, Vector3{4,1,3}) << '\n';

	// 5.
	std::cout << "5. "<< Vector3::Cross(Vector3{4,5,1}, Vector3{4,1,3}).Normalized() << '\n';

	// 7, 8, 9, 10
	Sphere sphere{Vector3{0, 0, 0}, 10};
	Ray ray1 {Vector3{0,0,-20}, Vector3 (0,0,1)};
	Ray ray2 {Vector3{0,0,-20}, Vector3 (0,1,0)};

	HitResult result1;
	HitResult result2;
	std::cout << "10. " << sphere.Hit(ray1, result1) << ", " << sphere.Hit(ray2, result2) << '\n';

	// 11. 
	std::cout << "11. " << result1.hitPoint << ", " << result2.hitPoint << '\n';

	// 12.
	Ray ray3{Vector3{0,10,-1}, Vector3{0,0,1}};
	HitResult result3;
	std::cout << "12. " << sphere.Hit(ray3, result3) << ", intersection at: " << result3.hitPoint << '\n';

	Plane plane {Vector3{0, 0, 0}, Vector3{0,1,1}.Normalized()};
	HitResult result4;
	std::cout << "14. " << plane.Hit(ray2, result4) << ", intersection at: " << result4.hitPoint << '\n';

	// 15.
	Triangle triangle {
		Vector3{0, 0, 0},
		Vector3{1, 0, 0},
		Vector3{0, 1, 0}
	};
	
	// 15.1
	{
		Vector3 p1 = Vector3{-1, 0.5, 0};
		Vector3 p2 = Vector3{1, 0.5, 0};
		Ray ray {p1, (p2-p1).Normalized()};
		HitResult result;
		std::cout << "15.1. " << triangle.Hit(ray, result) << ", intersection at: " << result.hitPoint << '\n';
	}

	// 15.2
	{
		Vector3 p1 = Vector3{2, -1, 0};
		Vector3 p2 = Vector3{2, 2, 0};
		Ray ray {p1, (p2-p1).Normalized()};
		HitResult result;
		std::cout << "15.2. " << triangle.Hit(ray, result) << ", intersection at: " << result.hitPoint << '\n';
	}

	// 15.3
	{
		Vector3 p1 = Vector3{0, 0, -1};
		Vector3 p2 = Vector3{0, 0, 1};
		Ray ray {p1, (p2-p1).Normalized()};
		HitResult result;
		std::cout << "15.3. " << triangle.Hit(ray, result) << ", intersection at: " << result.hitPoint << '\n';
	}
}

/*
* Exercise 2 Checklist
* 
* Proszê zaimplementowaæ klasy obrazu...........................(DONE)
* natê¿enia.....................................................(CAN USE Vector3) 
* kamery (ortogonaln¹ oraz perpsektywiczn¹).....................(DONE),
* wyrenderowaæ obraz zawieraj¹cy dwie kule: persp i ortho.......(DONE)
* 
* Nale¿y zaimplementowaæ podan¹ metod¹ antyaliasingu adaptacyjnego lub w³asn¹, zaproponowan¹ metodê. (TODO)
*/

void Exercise2()
{
	Buffer orthoCameraTarget(600, 400);
	Buffer perspCameraTarget(600, 400);

	// Pseudo-scene
	Sphere sphere1{ Vector3{ 0, 0, 0 }, 1.0f };
	Sphere sphere2{ Vector3{ 2, 2, 5 }, 1.0f };

	OrthographicCamera orthoCamera(Vector3{ 0, 0, -5 }, Vector3{ 0, 0, 1 }, orthoCameraTarget.GetWidth(), orthoCameraTarget.GetHeight(), 3.0f);
	PerspectiveCamera perspCamera(Vector3{ 0, 0, -5 }, Vector3{ 0, 0, 1 }, perspCameraTarget.GetWidth(), perspCameraTarget.GetHeight(), 45.0f);
	
	for (int y = 0; y < orthoCameraTarget.GetHeight() - 1; y++)
	{
		for (int x = 0; x < orthoCameraTarget.GetWidth() - 1; x++)
		{
			// DO othrographic
			{
				Ray ray = orthoCamera.ConstructRay(x, y);
				orthoCameraTarget.ColorAt(x, y) = sphere1.Hit(ray) ? 0xFFFF0000 : 0xFF000000;
				orthoCameraTarget.ColorAt(x, y) = sphere2.Hit(ray) ? 0xFF00FF00 : orthoCameraTarget.ColorAt(x, y);
			}

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