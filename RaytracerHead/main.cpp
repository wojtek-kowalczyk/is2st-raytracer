#include <iostream>

#include "primitives.h"

int main()
{
	std::cout << std::boolalpha;

	Sphere sphere{ Vector3(0, 0, 0), 1 };
	Ray ray{ Vector3(0, 0, 0), Vector3(0, 0, 1) };

	std::cout << "Sphere: " << sphere << "\n";
	std::cout << "Ray: " << ray << "\n";
	std::cout << "Hit? " << sphere.Hit(ray) << std::endl;

	return 0;
}