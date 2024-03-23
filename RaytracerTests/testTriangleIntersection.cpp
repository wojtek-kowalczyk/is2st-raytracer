#include "pch.h"

#include "primitives.h"

TEST(TriangleIntersection, RegularHit)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray = Ray{
		Vector3(0.2f, 0.2f, -1),
		Vector3(0, 0, 1)
	};

	EXPECT_EQ(triangle.Hit(ray), true);
}

TEST(TriangleIntersection, RegularMiss)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray = Ray{
		Vector3(1, 1, -1),
		Vector3(0, 0, 1)
	};

	EXPECT_EQ(triangle.Hit(ray), false);
}

TEST(TriangleIntersection, RayParallelMiss)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray = Ray{
		Vector3(0, 0, 1),
		Vector3(1, 0, 0)
	};

	EXPECT_EQ(triangle.Hit(ray), false);
}

TEST(TriangleIntersection, RayParallelOnTriangle)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray = Ray{
		Vector3(0, 0, 0),
		Vector3(1, 1, 0)
	};

	EXPECT_EQ(triangle.Hit(ray), false);
}
TEST(TriangleIntersection, RayParallelOnTriangleThroughVertex)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray = Ray{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0)
	};

	EXPECT_EQ(triangle.Hit(ray), false);
}

TEST(TriangleIntersection, HitAtVertex)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray1 = Ray{
		Vector3(0, 0, -1),
		Vector3(0, 0, 1)
	};

	Ray ray2 = Ray{
		Vector3(1, 0, -1),
		Vector3(0, 0, 1)
	};

	Ray ray3 = Ray{
		Vector3(0, 1, -1),
		Vector3(0, 0, 1)
	};

	EXPECT_EQ(triangle.Hit(ray1), true);
	EXPECT_EQ(triangle.Hit(ray2), true);
	EXPECT_EQ(triangle.Hit(ray3), true);
}

TEST(TriangleIntersection, HitAtEdge)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(0, 1, 0),
		Vector3(1, 0, 0),
	};

	Ray ray1 = Ray{
		Vector3(0.5, 0, -1),
		Vector3(0, 0, 1)
	};

	Ray ray2 = Ray{
		Vector3(0, 0.5, -1),
		Vector3(0, 0, 1)
	};

	Ray ray3 = Ray{
		Vector3(0.5, 0.5, -1),
		Vector3(0, 0, 1)
	};

	EXPECT_EQ(triangle.Hit(ray1), true);
	EXPECT_EQ(triangle.Hit(ray2), true);
	EXPECT_EQ(triangle.Hit(ray3), true);
}

TEST(TriangleIntersection, MissCloseToVertex)
{
	/*
		The case is like this

				|\
				| \
			  x |__\
	*/
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray1 = Ray{
		Vector3(-0.001f, 0, -1),
		Vector3(0, 0, 1)
	};

	Ray ray2 = Ray{
		Vector3(0.001f, 0, -1),
		Vector3(0, 0, 1)
	};

	EXPECT_EQ(triangle.Hit(ray1), false);
	EXPECT_EQ(triangle.Hit(ray2), true);
}

TEST(TriangleIntersection, MissCloseToEdge)
{
	Triangle triangle = Triangle{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 1, 0)
	};

	Ray ray1 = Ray{
		Vector3(-0.001f, 0.5f, -1),
		Vector3(0, 0, 1)
	};

	Ray ray2 = Ray{
		Vector3(0.001f, 0.5f, -1),
		Vector3(0, 0, 1)
	};

	EXPECT_EQ(triangle.Hit(ray1), false);
	EXPECT_EQ(triangle.Hit(ray2), true);
}
