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

	Mesh *cylinder = new Cylinder(20,2,0.9);
	Mesh *sphere = new Sphere(15, 15);
	Mesh* cone = new Cone(15);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	//cylinder->SetColor(Vector3(255, 0, 0));
	cylinder->SetTranslation(Vector3(2, 1, 8));
	cylinder->SetRotation(Vector3(1, 0, 0), 30);
	cylinder->SetView(obj2view, camera);

	sphere->SetTranslation(Vector3(0, -1, 9));
	sphere->SetView(obj2view, camera);

	cone->SetTranslation(Vector3(-3, -1, 11));
	cone->SetRotation(Vector3(1, 0, 0), 30);
	cone->SetView(obj2view, camera);

	std::vector<Mesh*> objects = { cylinder,sphere,cone };

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
