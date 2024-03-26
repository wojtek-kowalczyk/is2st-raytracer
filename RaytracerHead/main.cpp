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
				int colSum = 0;
				Ray ray = perspCamera.ConstructRay(x, y);
				colSum += sphere1.Hit(ray);
				ray = perspCamera.ConstructRay(x + 1, y);
				colSum += sphere1.Hit(ray);
				perspCamera.ConstructRay(x, y + 1);
				colSum += sphere1.Hit(ray);
				perspCamera.ConstructRay(x+ 1, y + 1);
				colSum += sphere1.Hit(ray);
				//perspCameraTarget.ColorAt(x, y) = sphere1.Hit(ray) ? 0xFFFF0000 : 0xFF000000;
				float colFactor = (float)colSum / 4.0f;
				unsigned char finalAlpha = (0xFF >> 24) * colFactor; // is necessary?
				unsigned char finalRed = ((0x00FF0000 >> 16) & 0xFF) * colFactor;
				perspCameraTarget.ColorAt(x, y) = sphere1.finalColor(0xFFFF0000, sphere1.aaFactor((float)x, (float)y, sphere1, perspCamera, 1.0f));
				//perspCameraTarget.ColorAt(x, y) = sphere2.Hit(ray) ? 0xFF00FF00 : perspCameraTarget.ColorAt(x, y);
				perspCameraTarget.ColorAt(x, y) = sphere2.finalColor(0xFFFF0000, sphere2.aaFactor((float)x, (float)y, sphere2, perspCamera, 1.0f));
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