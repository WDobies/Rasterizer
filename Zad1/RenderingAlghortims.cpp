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
#include "PointLight.h"

int main()
{
	ColorBuffer buffer(WIDTH, HEIGHT);



	Sphere sphere(15, 15);
	Sphere cone(15, 15);
	Sphere cylinder(15, 15);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	Matrix4 model;
	model = model.Translate(model, Vector3(0, -1, 10.4));
	//model = model.Rotate(model, Vector3(1, 0, 1), 45);

	Matrix4 m;
	m = m.Translate(m, Vector3(-2, 2, 9));
	//m = m.Rotate(m, Vector3(1, 0, 1), 45);

	Matrix4 mC;
	mC = mC.Translate(mC, Vector3( 3, -1, 9));
	//mC = mC.Rotate(mC, Vector3(-1, 0, 1), 60);

	sphere.SetModelMatrix(model);
	sphere.SetCamera(camera);
	sphere.SetProjection(obj2view);

	cone.SetModelMatrix(m);
	cone.SetCamera(camera);
	cone.SetProjection(obj2view);

	cylinder.SetModelMatrix(mC);
	cylinder.SetCamera(camera);
	cylinder.SetProjection(obj2view);

	sphere.SetView();
	cone.SetView();
	cylinder.SetView();

	DirectionalLight dl(Vector3(0.9f, 0.0, -0.4f), Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0));
	PointLight pl(Vector3(0,0.4, 10), Vector3(0, 0, 30), Vector3(0, 0, 170), Vector3(255, 255, 255));

	dl.Calculate(sphere);
	pl.Calculate(sphere);
	dl.Calculate(cone);
	pl.Calculate(cone);
	dl.Calculate(cylinder);
	pl.Calculate(cylinder);


	std::vector<Mesh> figures;
	figures = { sphere, cone, cylinder };
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
