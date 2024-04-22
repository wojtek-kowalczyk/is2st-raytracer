#include "exampleScenes.h"

#include "material.h"
#include "color.h"

Scene ExampleScenes::CreateSimple()
{
	Material* redMaterial = Material::Default();
	redMaterial->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	Material* greenMaterial = Material::Default();
	greenMaterial->color = Color(0.0f, 1.0f, 0.0f, 1.0f);

	Material* floorMaterial = Material::Default();
	floorMaterial->color = Color(0.6f, 0.8f, 0.6f, 1.0f);

	Material* ball1 = Material::Default();
	ball1->type = MaterialType::Reflective;
	ball1->roughness = 0.0f;

	Material* ball2 = Material::Default();
	ball2->color = Color(0.4f, 0.8f, 0.9f, 1.0f);
	ball2->type = MaterialType::Reflective;
	ball2->roughness = 0.23f;

	Material* emissiveMaterial = Material::Default();
	emissiveMaterial->type = MaterialType::Emissive;
	emissiveMaterial->color = Color(1, 1, 1, 1.0f) * 3.0f;

	Scene scene;

	/// OBJECTS /////////////////////////////

	Sphere* sphere1 = new Sphere(Vector3{ -1.1f, -0.1f, 3 }, 0.5f);
	sphere1->SetMaterial(ball2);
	scene.AddObject(sphere1);

	Sphere* sphere2 = new Sphere(Vector3{ 0.0f, -0.1f, 3 }, 0.5f);
	sphere2->SetMaterial(redMaterial);
	scene.AddObject(sphere2);

	Sphere* sphere3 = new Sphere(Vector3{ +1.1f, -0.1f, 3 }, 0.5f);
	sphere3->SetMaterial(ball1);
	scene.AddObject(sphere3);

	Sphere* sphere4 = new Sphere(Vector3{ +0.4f, -0.5f, 2.2f }, 0.1f);
	sphere4->SetMaterial(emissiveMaterial);
	scene.AddObject(sphere4);

	Plane* plane = new Plane(Vector3{ 0, -0.6, 0 }, Vector3{ 0, 1, 0 });
	plane->SetMaterial(floorMaterial);
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

	Material* metalSphereMaterial = Material::Default();
	metalSphereMaterial->type = MaterialType::Reflective;
	metalSphereMaterial->roughness = 0.0f;

	Material* mirrorMaterial = Material::Default();
	mirrorMaterial->type = MaterialType::Reflective;
	mirrorMaterial->roughness = 0.1f;

	Material* refractiveMaterial = Material::Default();
	refractiveMaterial->type = MaterialType::Refractive;

	Material* emissiveMaterial = Material::Default();
	emissiveMaterial->type = MaterialType::Emissive;
	emissiveMaterial->color = Color(1, 1, 1, 1.0f);

	/// OBJECTS /////////////////////////////
	
	Scene scene;
	scene.ambientColor = Color(0, 0, 0, 0.0f);
	
	Plane* floor = new Plane(Vector3{ 0, -1, 0 }, Vector3{ 0, 1, 0 });
	floor->SetMaterial(whiteMaterial);
	scene.AddObject(floor);

	Plane* ceiling = new Plane(Vector3{ 0, 1, 0 }, Vector3{ 0, -1, 0 });
	ceiling->SetMaterial(whiteMaterial);
	//ceiling->SetMaterial(emissiveMaterial);
	scene.AddObject(ceiling);

	Plane* backWall = new Plane(Vector3{ 0, 0, 5 }, Vector3{ 0, 0, -1 });
	backWall->SetMaterial(whiteMaterial);
	scene.AddObject(backWall);

	Plane* rightWall = new Plane(Vector3{ 1, 0, 0 }, Vector3{ -1, 0, 0 });
	rightWall->SetMaterial(redMaterial);
	scene.AddObject(rightWall);

	Plane* leftWall = new Plane(Vector3{ -1, 0, 0 }, Vector3{ 1, 0, 0 });
	leftWall->SetMaterial(greenMaterial);
	scene.AddObject(leftWall);

	Sphere* sphere1 = new Sphere(Vector3{ -0.5f, -0.5f, 4.0f }, 0.48f);
	sphere1->SetMaterial(metalSphereMaterial);
	scene.AddObject(sphere1);

	Sphere* sphere2 = new Sphere(Vector3{ +0.50f, -0.49f, 3.0f }, 0.48f);
	sphere2->SetMaterial(refractiveMaterial);
	scene.AddObject(sphere2);

	Triangle* mirrorTriangle1 = new Triangle(Vector3{ -0.99f, -0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 4.5f });
	mirrorTriangle1->SetMaterial(mirrorMaterial);
	scene.AddObject(mirrorTriangle1);

	Triangle* mirrorTriangle2 = new Triangle(Vector3{ -0.99f, -0.75f, 2.0f }, Vector3{ -0.99f, +0.75f, 4.5f }, Vector3{ -0.99f, -0.75f, 4.5f });
	mirrorTriangle2->SetMaterial(mirrorMaterial);
	scene.AddObject(mirrorTriangle2);

	// EMISSIVE OBJECTS

//#define QUAD_LIGHT

#ifdef QUAD_LIGHT
	{
		Vector3 center{ 0, 0.999f, 3 };
		float size = 0.25f;
	
		Triangle* lightTriangle1 = new Triangle(center + Vector3(-size, 0, -size), center + Vector3(+size, 0, +size), center + Vector3(+size, 0, -size));
		lightTriangle1->SetMaterial(emissiveMaterial);
		scene.AddObject(lightTriangle1);

		Triangle* lightTriangle2 = new Triangle(center + Vector3(-size, 0, -size), center + Vector3(-size, 0, +size), center + Vector3(+size, 0, +size));
		lightTriangle2->SetMaterial(emissiveMaterial);
		scene.AddObject(lightTriangle2);
	}
#else
	{
		Sphere* lightSphere = new Sphere(Vector3{ 0.0f, 1.0f, 3.0f }, 0.3f);
		lightSphere->SetMaterial(emissiveMaterial);
		scene.AddObject(lightSphere);
	}
#endif
	
	return scene;
}
