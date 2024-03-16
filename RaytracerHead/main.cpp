#include <iostream>

#include "vector3.h"

int main()
{
	Vector3 v(1, 2, 3);
	std:: cout << v + Vector3(3, 4, 5) << std::endl;
	return 0;
}