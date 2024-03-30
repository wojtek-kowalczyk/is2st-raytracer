#pragma once

#include "Scene.h"

#include "primitives/sphere.h"
#include "primitives/plane.h"
#include "primitives/triangle.h"

namespace ExampleScenes
{
	// Recommended camera setup for these scenes:
	/*
	PerspectiveCamera perspCamera(Vector3{ 0, 0, 0 }, Vector3{ 0, 0, 1 }, perspCameraTarget.GetWidth(), perspCameraTarget.GetHeight(), 45.0f);
	*/

	Scene CreateSimple();
	Scene CreateCornellBox();
}
