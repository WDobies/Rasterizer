#include <iostream>
#include <fstream>
#include "Triangle.h"
#include "DepthBuffer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ColorBuffer.h"
#include "Sphere.h"
#include <vector>
#include "Cylinder.h"
#include "Cone.h"
#include "DirectionalLight.h"

int main()
{
	ColorBuffer buffer(WIDTH, HEIGHT);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			DEPTHBUFFER[i* HEIGHT +j] = INFINITY;
		}
	}

	Sphere sphere(15, 15);
	//Cylinder cylinder(6, 6);
	//Cone cone(4, 0.5f);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	for (auto& t : sphere.triangles)
	{
		t.SetTranslation(Vector3(0, 0.0f, 5));
		//t.SetRotation(Vector3(1, 0, 0), 90);
		t.SetView(obj2view, camera);
	}

	DirectionalLight dl;
	dl.Calculate(camera, obj2view, sphere.vSize, sphere.normals, sphere.vertices, sphere.colors, sphere.indices, sphere.triangles);

	std::vector<Mesh> figures;
	figures = { sphere};
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			for (auto& t : figures)
			{
				for (auto& g : t.triangles)
				{
					g.Draw(i, j, buffer);
				}
			}
		}
	}

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);
}
