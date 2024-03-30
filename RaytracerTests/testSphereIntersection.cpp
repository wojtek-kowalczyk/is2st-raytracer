#include "pch.h"

#include "primitives/sphere.h"

TEST(SphereIntersection, NormalCase)
{
	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(0, 0, 0), Vector3(0, 0, 1) };

	EXPECT_EQ(sphere.Hit(ray), true);
}

TEST(SphereIntersection, MissCuzStartBehind)
{
	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(0, 0, 5), Vector3(0, 0, 1) };

	EXPECT_EQ(sphere.Hit(ray), false);
}

TEST(SphereIntersection, StartAtEdge)
{
	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(0, 0, 4), Vector3(0, 0, 1) };

	EXPECT_EQ(sphere.Hit(ray), false); // TODO : should this be false? I guess it doesn't matter that much?
}

TEST(SphereIntersection, StartRightBeforeEdge)
{
	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(0, 0, 3.999), Vector3(0, 0, 1) };

	EXPECT_EQ(sphere.Hit(ray), true);
}

TEST(SphereIntersection, HitEdge)
{
	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(1, 0, 0), Vector3(0, 0, 1) };

	EXPECT_EQ(sphere.Hit(ray), true);
}

TEST(SphereIntersection, MissEdge)
{
	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(1.01, 0, 0), Vector3(0, 0, 1) };

	EXPECT_EQ(sphere.Hit(ray), false);
}

TEST(SphereIntersection, HitNearEdge)
{
	Sphere sphere{ Vector3(0, 0, 3), 1 };
	Ray ray{ Vector3(0.99, 0, 0), Vector3(0, 0, 1) };

	EXPECT_EQ(sphere.Hit(ray), true);
}

TEST(SphereIntersection, HitDiagonal)
{
	Sphere sphere{ Vector3(3, 3, 3), 1 };
	Ray ray{ Vector3(0, 0, 0), Vector3(1, 1, 1) };

	EXPECT_EQ(sphere.Hit(ray), true);
}