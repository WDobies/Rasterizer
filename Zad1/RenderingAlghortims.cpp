#include <iostream>
#include <fstream>
#include "Rasterizer.h"
#include "DepthBuffer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ColorBuffer.h"
#include "Sphere.h"
#include <vector>
#include "Cylinder.h"

#include "Cone.h"

int main()
{
	ColorBuffer buffer(WIDTH, HEIGHT);

	Mesh *cylinder = new Cylinder(25,25,0.9);
	Mesh *sphere = new Sphere(9, 9);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	//cylinder->SetColor(Vector3(255, 0, 0));
	cylinder->SetTranslation(Vector3(0, -2, 15));
	cylinder->SetRotation(Vector3(1, 1, 1), 30);
	//cylinder->SetLight();
	cylinder->SetView(obj2view, camera);

	sphere->SetTranslation(Vector3(0, -1, 9));
	//sphere->SetLight();
	sphere->SetView(obj2view, camera);


	std::vector<Mesh*> objects = { cylinder, sphere};

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			for (Mesh* mesh : objects)
			{
				mesh->Draw(i, j, buffer);
			}
		}
	}

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);

	for (Mesh *mesh: objects)
	{
		delete mesh;
	}
	objects.clear();

}
