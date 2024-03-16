#include "pch.h"

#include "primitives.h"

TEST(PlaneIntersection, RegularCaseHit)
{
	Plane plane{ Vector3(0, 0, 0), Vector3(0, 1, 0) };
	Ray ray{ Vector3(0, 0, 1), Vector3(0, 1, 0) };

	EXPECT_EQ(plane.Hit(ray), true);
}

TEST(PlaneIntersection, RegularCaseMiss)
{
	Plane plane{ Vector3(0, 0, 0), Vector3(0, 1, 0) };
	Ray ray{ Vector3(0, 0, 1), Vector3(0, -1, 0) };

	EXPECT_EQ(plane.Hit(ray), false);
}

TEST(PlaneIntersection, RayParallelNoPoints)
{
	Plane plane{ Vector3(0, 0, 0), Vector3(0, 1, 0) };
	Ray ray{ Vector3(0, 0, 1), Vector3(0, 0, 1) };

	EXPECT_EQ(plane.Hit(ray), false);
}

TEST(PlaneIntersection, RayParallelInfinitePoints)
{
	Plane plane{ Vector3(0, 0, 0), Vector3(0, 1, 0) };
	Ray ray{ Vector3(0, 0, 0), Vector3(0, 0, 1) };

	EXPECT_EQ(plane.Hit(ray), false);
}
