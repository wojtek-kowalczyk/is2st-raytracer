#include "ray.h"

std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Origin: " << r.origin << ", Direction: " << r.direction;
	return os;
}
