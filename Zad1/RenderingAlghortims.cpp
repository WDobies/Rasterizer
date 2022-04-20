#include <iostream>
#include <fstream>
#include "Triangle.h"
#include "DepthBuffer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ColorBuffer.h"

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

	Triangle t(Vector3(0.5, 0.5, 0), Vector3(0.5, -0.5, 0), Vector3(-0.5, 0.5, 0), Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), WIDTH, HEIGHT);
	Triangle d(Vector3(0.5, 0.5, 0), Vector3(-0.9, 0.2, 0), Vector3(-0.6, 0.8, 0), Vector3(255, 255, 0), Vector3(40, 180, 100), Vector3(90, 140, 180), WIDTH, HEIGHT);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	t.SetTranslation(Vector3(0, 2, 8));
	t.SetRotation(Vector3(0, 0, 1), 45);
	t.SetView(obj2view, camera);

	d.SetTranslation(Vector3(0, 0, 7));
	d.SetView(obj2view, camera);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			t.Draw(i, j, buffer);
			d.Draw(i, j, buffer);
		}
	}

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);
}
