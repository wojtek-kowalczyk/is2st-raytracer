#include "primitives.h"
#include <iostream>

void TestVector() 
{
    Vector3 v0;
    Vector3 v1 (1, 1, 1);
    Vector3 v2 (3, 4, 5);

    std::cout << v1 + v2 << '\n';
    std::cout << v1 - v2 << '\n';
    std::cout << v2 * 3  << '\n';

    std::cout << v1.Magnitude() << '\n';
    std::cout << v2.Normalized() << '\n';
    std::cout << v2 << '\n';
    Vector3 v3 = v2;
    std::cout << v3 << '\n';
    v3.Normalize();
    std::cout << v3 << '\n';

    std::cout << Vector3::Dot(v1, v2) << '\n';
    std::cout << Vector3::Cross(Vector3(1,0,0), Vector3(0,1,0)) << '\n';
    std::cout << Vector3::AngleRad(Vector3(1,0,0), Vector3(0,1,0)) << '\n';
    std::cout << Vector3::AngleDeg(Vector3(1,0,0), Vector3(0,1,0)) << '\n';
}
