#include "exampleScenes.h"

#include "material.h"
#include "color.h"

Scene ExampleScenes::CreateSimple()
{
	Material* redMaterial = Material::Default();
	redMaterial->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	Material* greenMaterial = Material::Default();
	greenMaterial->color = Color(0.0f, 1.0f, 0.0f, 1.0f);

	Material* mirrorMaterial = Material::Default();
	mirrorMaterial->type = MaterialType::Reflective;

	Scene scene;

	/// OBJECTS /////////////////////////////

	Sphere* sphere1 = new Sphere(Vector3{ -0.6, -0.2, 3 }, 0.5);
	sphere1->SetMaterial(mirrorMaterial);
	scene.AddObject(sphere1);

	Sphere* sphere2 = new Sphere(Vector3{ 0.6, 0, 3 }, 0.5);
	sphere2->SetMaterial(mirrorMaterial);
	scene.AddObject(sphere2);

	Plane* plane = new Plane(Vector3{ 0, -1, 0 }, Vector3{ 0, 1, 0 });
	plane->SetMaterial(greenMaterial);
	scene.AddObject(plane);

	/// LIGHTS //////////////////////////////

	PointLight* pointLight1 = new PointLight(Color(1.0f, 1.0f, 1.0f), Vector3{ 1, 2, 1 });
	scene.AddLight(pointLight1);

	// TODO : we're leaking memory here, the Scene Objects aren't deallocated.

	return scene;
}

Scene ExampleScenes::CreateCornellBox()
{
#if 0
	Scene scene;

	Plane* floor = new Plane(Vector3{ 0, -1, 0 }, Vector3{ 0, 1, 0 });
	floor->color = 0xFFcccccc;
	scene.AddObject(floor);

	Plane* ceiling = new Plane(Vector3{ 0, 1, 0 }, Vector3{ 0, -1, 0 });
	ceiling->color = 0xFFaaaaaa;
	scene.AddObject(ceiling);

	Plane* backWall = new Plane(Vector3{ 0, 0, 5 }, Vector3{ 0, 0, 1 });
	backWall->color = 0xFF777777;
	scene.AddObject(backWall);

	Plane* leftWall = new Plane(Vector3{ 1, 0, 0 }, Vector3{ -1, 0, 0 });
	leftWall->color = 0xFF9a9a9a;
	scene.AddObject(leftWall);

	Plane* rightWall = new Plane(Vector3{ -1, 0, 0 }, Vector3{ 1, 0, 0 });
	rightWall->color = 0xFF9a9a9a;
	scene.AddObject(rightWall);

	Sphere* sphere1 = new Sphere(Vector3{ -0.5f, -0.5f, 4.0f }, 0.5f);
	sphere1->color = 0xFFff0000;
	scene.AddObject(sphere1);

	Sphere* sphere2 = new Sphere(Vector3{ +0.30f, -0.25f, 2.75f }, 0.5f);
	sphere2->color = 0xFF00ff00;
	scene.AddObject(sphere2);

	Triangle* mirrorTriangle1 = new Triangle(Vector3{ -0.99f, -0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 4.5f });
	mirrorTriangle1->color = 0xFFFF00FF;
	scene.AddObject(mirrorTriangle1);

	Triangle* mirrorTriangle2 = new Triangle(Vector3{ -0.99f, -0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 4.5f }, Vector3{ -0.99f, -0.75f, 4.5f });
	mirrorTriangle2->color = 0xFFFF00FF;
	scene.AddObject(mirrorTriangle2);

	// TODO : put light at this sphere
	Sphere* lightSphere = new Sphere(Vector3{ 0.0f, 1.0f, 3.0f }, 0.1f);
	lightSphere->color = 0xFFFFFFFF;
	scene.AddObject(lightSphere);

	// TODO : we're leaking memory here, the Scene Objects aren't deallocated.

	return scene;
#endif
	return Scene();
}
