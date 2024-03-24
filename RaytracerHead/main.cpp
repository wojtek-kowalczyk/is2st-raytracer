#include <iostream>
#include <ostream>

#include "primitives.h"
#include "vector3.h"
#include "buffer.h"
#include "camera.h"

// TODO : when imlpementing camera, put matrix at 0,0,0, and put camera back, at the middle. 
// -Z forward? or +Z forward, make decision and be consistent

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
* Exercise 2
* Proszê zaimplementowaæ klasy obrazu, natê¿enia i kamery (ortogonaln¹ oraz perpsektywiczn¹),
* a nastêpnie wyrenderowaæ obraz, zawieraj¹cy dwie kule. wykorzystuj¹c rzut perspektywiczny i rzut ortogonalny.
* Nale¿y zaimplementowaæ podan¹ metod¹ antyaliasingu adaptacyjnego lub w³asn¹, zaproponowan¹ metodê.
*/

void Exercise2()
{
	Buffer buffer(600, 400);
	buffer.ClearColor(0xFF000000);

	OrthographicCamera camera(Vector3{ 0, 0, -200 }, Vector3{ 0, 0, 1 }, buffer.GetWidth(), buffer.GetHeight());

	// Pseudo-scene
	Sphere sphere1{ Vector3{ 300, 200, 0 }, 100};

	for (int y = 0; y < buffer.GetHeight(); y++)
	{
		for (int x = 0; x < buffer.GetWidth(); x++)
		{
			Ray ray = camera.ConstructRay(x, y);
			buffer.ColorAt(x, y) = sphere1.Hit(ray) ? 0xFFFFFFFF : 0xFF000000;
		}
	}

	buffer.SaveToFile("render.tga");
}

int main()
{
	//Exercise1();
	Exercise2();

	return 0;
}