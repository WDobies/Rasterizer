#include <iostream>
#include <fstream>
#include "Triangle.h"
#include "DepthBuffer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ColorBuffer.h"
#include "Sphere.h"
#include <vector>

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

	Triangle tr(Vector3(0.5, 1.0, 0), Vector3(0.5, 0.0, 0), Vector3(-0.5, 1.0, 0), Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), WIDTH, HEIGHT);
	Triangle d(Vector3(-0.5, 0.0, 0), Vector3(-0.5, 1.0, 0), Vector3(0.5, 0.0, 0), Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), WIDTH, HEIGHT);
	Triangle down(Vector3(0.5, 0.0, 0), Vector3(0.5, -1.0, 0), Vector3(-0.5, 0.0, 0), Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), WIDTH, HEIGHT);

	Sphere sphere(15, 2);
	Sphere sph(15, 15);
	std::vector<Triangle> triangles;
	std::vector<Triangle> trSph;

	for (int i = 0; i < sphere.tSize; i++)
	{
		triangles.push_back(Triangle(sphere.vertices[(int)sphere.indices[i].y], sphere.vertices[(int)sphere.indices[i].x], sphere.vertices[(int)sphere.indices[i].z], Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), WIDTH, HEIGHT));
	}
	for (int i = 0; i < sph.tSize; i++)
	{
		trSph.push_back(Triangle(sph.vertices[(int)sph.indices[i].x], sph.vertices[(int)sph.indices[i].y], sph.vertices[(int)sph.indices[i].z], Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), WIDTH, HEIGHT));
	}

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	std::cout << triangles.size();

	for (auto& t : triangles)
	{
		t.SetTranslation(Vector3(0, 0.0f, 3));
		t.SetRotation(Vector3(1, 0, 0), 20);
		t.SetView(obj2view, camera);
	}
	for (auto& t : trSph)
	{
		t.SetTranslation(Vector3(0.8f, 0.0f, 7));
		//t.SetRotation(Vector3(1, 1, 1), 45);
		t.SetView(obj2view, camera);
	}

	tr.SetTranslation(Vector3(0, 0, 4));
	tr.SetView(obj2view, camera);

	d.SetTranslation(Vector3(0, 0, 4));
	d.SetView(obj2view, camera);

	down.SetTranslation(Vector3(0, 0, 4));
	down.SetView(obj2view, camera);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			//tr.Draw(i, j, buffer);
			//d.Draw(i, j, buffer);
			//down.Draw(i, j, buffer);
			for (auto& t : triangles)
			{
				t.Draw(i, j, buffer);
			}
			//for (auto& t : trSph)
			//{
			//	t.Draw(i, j, buffer);
			//}
		}
	}

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);
}
