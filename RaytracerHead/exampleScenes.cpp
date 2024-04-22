#include "exampleScenes.h"

#include "material.h"
#include "color.h"

Scene ExampleScenes::CreateSimple()
{
	Material* redMaterial = Material::Default();
	redMaterial->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	Material* greenMaterial = Material::Default();
	greenMaterial->color = Color(0.0f, 1.0f, 0.0f, 1.0f);

	Material* greyMaterial = Material::Default();
	greyMaterial->color = Color(0.6f, 0.6f, 0.6f, 1.0f);

	Material* reflectiveMaterial = Material::Default();
	reflectiveMaterial->type = MaterialType::Reflective;
	reflectiveMaterial->roughness = 0.0f;

	Material* refractiveMaterial = Material::Default();
	refractiveMaterial->type = MaterialType::Refractive;
	refractiveMaterial->ior = 1.5f;
	//refractiveMaterial->ior = 1.0f / 1.33f;

	Scene scene;

	/// OBJECTS /////////////////////////////

	Sphere* sphere1 = new Sphere(Vector3{ -1.1f, -0.1f, 3 }, 0.5f);
	sphere1->SetMaterial(refractiveMaterial);
	scene.AddObject(sphere1);

	Sphere* sphere2 = new Sphere(Vector3{ 0.0f, -0.1f, 3 }, 0.5f);
	sphere2->SetMaterial(redMaterial);
	scene.AddObject(sphere2);

	Sphere* sphere3 = new Sphere(Vector3{ +1.1f, -0.1f, 3 }, 0.5f);
	sphere3->SetMaterial(reflectiveMaterial);
	scene.AddObject(sphere3);

	Plane* plane = new Plane(Vector3{ 0, -0.6, 0 }, Vector3{ 0, 1, 0 });
	plane->SetMaterial(greyMaterial);
	scene.AddObject(plane);

	return scene;
}

Scene ExampleScenes::CreateCornellBox()
{
	Material* redMaterial = Material::Default();
	redMaterial->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	Material* greenMaterial = Material::Default();
	greenMaterial->color = Color(0.0f, 1.0f, 0.0f, 1.0f);

	Material* blueMaterial = Material::Default();
	blueMaterial->color = Color (0, 0, 1, 1.0f);

	Material* whiteMaterial = Material::Default();
	whiteMaterial->color = Color(1.0f, 1.0f, 1.0f, 1.0f);

	Material* reflectiveMaterial = Material::Default();
	reflectiveMaterial->type = MaterialType::Reflective;
	reflectiveMaterial->roughness = 0.2f; // TODO : make this only for e.g. mirror

	Material* refractiveMaterial = Material::Default();
	refractiveMaterial->type = MaterialType::Refractive;

	Scene scene;

	/// OBJECTS /////////////////////////////

	Plane* floor = new Plane(Vector3{ 0, -1, 0 }, Vector3{ 0, 1, 0 });
	floor->SetMaterial(whiteMaterial);
	scene.AddObject(floor);

	// Plane* ceiling = new Plane(Vector3{ 0, 1, 0 }, Vector3{ 0, -1, 0 });
	// ceiling->SetMaterial(whiteMaterial);
	// scene.AddObject(ceiling);

	// Plane* backWall = new Plane(Vector3{ 0, 0, 5 }, Vector3{ 0, 0, 1 });
	// backWall->SetMaterial(whiteMaterial);
	// scene.AddObject(backWall);

	// Plane* rightWall = new Plane(Vector3{ 1, 0, 0 }, Vector3{ -1, 0, 0 });
	// rightWall->SetMaterial(redMaterial);
	// scene.AddObject(rightWall);

	Plane* leftWall = new Plane(Vector3{ -1, 0, 0 }, Vector3{ 1, 0, 0 });
	leftWall->SetMaterial(greenMaterial);
	scene.AddObject(leftWall);

	Sphere* sphere1 = new Sphere(Vector3{ -0.5f, -0.5f, 4.0f }, 0.48f);
	sphere1->SetMaterial(reflectiveMaterial);
	scene.AddObject(sphere1);

	Sphere* sphere2 = new Sphere(Vector3{ +0.50f, -0.49f, 3.0f }, 0.48f);
	sphere2->SetMaterial(refractiveMaterial);
	scene.AddObject(sphere2);

	Triangle* mirrorTriangle1 = new Triangle(Vector3{ -0.99f, -0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 4.5f });
	mirrorTriangle1->SetMaterial(reflectiveMaterial);
	scene.AddObject(mirrorTriangle1);

	Triangle* mirrorTriangle2 = new Triangle(Vector3{ -0.99f, -0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 4.5f }, Vector3{ -0.99f, -0.75f, 4.5f });
	mirrorTriangle2->SetMaterial(reflectiveMaterial);
	scene.AddObject(mirrorTriangle2);

	// LIGHT SPHERE
	//Sphere* lightSphere = new Sphere(Vector3{ 0.0f, 1.0f, 3.0f }, 0.1f);
	//lightSphere->SetMaterial(whiteMaterial); // TODO : emissive white, i.e. all pixels are pure white
	//scene.AddObject(lightSphere);
	
	return scene;
}
