#include <iostream>

#include "primitives.h"

int main()
{
	std::cout << std::boolalpha;

	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(1, 0, 0), Vector3(0, 0, 1) };

	std::cout << "Sphere: " << sphere << "\n";
	std::cout << "Ray: " << ray << "\n";
	std::cout << "Hit? " << sphere.Hit(ray) << std::endl;

	std::cout << "\n=======================\n";
	std::cout << "This is just dummy output to see if library linked properly\n";
	std::cout << "For proper intersection tests, run the unit tests\n";
	std::cout << "=======================\n";

	return 0;
}