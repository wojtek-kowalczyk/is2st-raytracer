#include "pch.h"

#include "vector3.h"

TEST(VectorTests, TestAddition) 
{
	Vector3 v1 = Vector3(1, 2, 3);
	Vector3 v2 = Vector3(3, 4, 5);

	Vector3 result = v1 + v2;

	EXPECT_EQ(result.x, 4);
	EXPECT_EQ(result.y, 6);
	EXPECT_EQ(result.z, 8);

	EXPECT_EQ(v1.x, 1);
	EXPECT_EQ(v1.y, 2);
	EXPECT_EQ(v1.z, 3);

	EXPECT_EQ(v2.x, 3);
	EXPECT_EQ(v2.y, 4);
	EXPECT_EQ(v2.z, 5);
}

TEST(VectorTests, TestSubtraction)
{
	Vector3 v1 = Vector3(1, 2, 3);
	Vector3 v2 = Vector3(3, 4, 5);

	Vector3 result = v1 - v2;

	EXPECT_EQ(result.x, -2);
	EXPECT_EQ(result.y, -2);
	EXPECT_EQ(result.z, -2);

	EXPECT_EQ(v1.x, 1);
	EXPECT_EQ(v1.y, 2);
	EXPECT_EQ(v1.z, 3);

	EXPECT_EQ(v2.x, 3);
	EXPECT_EQ(v2.y, 4);
	EXPECT_EQ(v2.z, 5);
}

TEST(VectorTests, TestDivisionByScalar)
{
	Vector3 v1 = Vector3(1, 2, 3);

	Vector3 result = v1 / 4.0f;

	EXPECT_FLOAT_EQ(result.x, 0.25f);
	EXPECT_FLOAT_EQ(result.y, 0.5f);
	EXPECT_FLOAT_EQ(result.z, 0.75f);

	EXPECT_EQ(v1.x, 1);
	EXPECT_EQ(v1.y, 2);
	EXPECT_EQ(v1.z, 3);
}

TEST(VectorTests, TestMultiplicationByScalar)
{
	Vector3 v1 = Vector3(1, 2, 3);

	Vector3 result = v1 * 4.0f;

	EXPECT_FLOAT_EQ(result.x, 4.0f);
	EXPECT_FLOAT_EQ(result.y, 8.0f);
	EXPECT_FLOAT_EQ(result.z, 12.0f);

	EXPECT_EQ(v1.x, 1);
	EXPECT_EQ(v1.y, 2);
	EXPECT_EQ(v1.z, 3);
}

TEST(VectorTests, TestLength)
{
	Vector3 v1 = Vector3(2, 0, 0);

	float length = v1.Magnitude();

	EXPECT_FLOAT_EQ(length, 2.0);

	EXPECT_EQ(v1.x, 2);
	EXPECT_EQ(v1.y, 0);
	EXPECT_EQ(v1.z, 0);
}

TEST(VectorTests, TestNormalizationNonMutating)
{
	Vector3 v1 = Vector3(1, 2, 3);

	Vector3 normalized = v1.Normalized();

	EXPECT_FLOAT_EQ(normalized.Magnitude(), 1.0f);

	EXPECT_EQ(v1.x, 1);
	EXPECT_EQ(v1.y, 2);
	EXPECT_EQ(v1.z, 3);
}

TEST(VectorTests, TestNormalizationMutating)
{
	Vector3 v1 = Vector3(1, 2, 3);
	v1.Normalize();

	EXPECT_FLOAT_EQ(v1.Magnitude(), 1.0f);

	EXPECT_NE(v1.x, 1);
	EXPECT_NE(v1.y, 2);
	EXPECT_NE(v1.z, 3);
}

TEST(VectorTests, TestDotProduct)
{
	Vector3 v1 = Vector3(1, 2, 3);
	Vector3 v2 = Vector3(3, 4, 5);

	float dot = Vector3::Dot(v1, v2);

	EXPECT_FLOAT_EQ(dot, 26);
}

TEST(VectorTests, TestCrossProduct)
{
	Vector3 v1 = Vector3(1, 0, 0);
	Vector3 v2 = Vector3(0, 1, 0);

	Vector3 cross = Vector3::Cross(v1, v2);

	EXPECT_EQ(cross.x, 0);
	EXPECT_EQ(cross.y, 0);
	EXPECT_EQ(cross.z, 1);
}

TEST(VectorTests, TestAngleRad)
{
	Vector3 v1 = Vector3(1, 0, 0);
	Vector3 v2 = Vector3(0, 1, 0);

	float angle = Vector3::AngleRad(v1, v2);

	EXPECT_FLOAT_EQ(angle, 1.57079633f);
}

TEST(VectorTests, TestAngleDeg)
{
	Vector3 v1 = Vector3(1, 0, 0);
	Vector3 v2 = Vector3(0, 1, 0);

	float angle = Vector3::AngleDeg(v1, v2);

	EXPECT_FLOAT_EQ(angle, 90.0f);
}

TEST(VectorTests, TestIsNormalized)
{
	Vector3 v(4, 7, 9);
	v.Normalize();
	EXPECT_TRUE(v.IsNormalized());
	EXPECT_TRUE(Vector3(1, 0, 0).IsNormalized());
	EXPECT_TRUE(Vector3(4, 0, 0).Normalized().IsNormalized());
}