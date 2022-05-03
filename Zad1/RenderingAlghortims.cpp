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
	Cone cone(15, 1);
	Cylinder cylinder(15, 5);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	Matrix4 modelSphere;
	modelSphere = modelSphere.Translate(modelSphere, Vector3(0, -1, 16));
	//model = model.Rotate(model, Vector3(1, 0, 1), 45);

	Matrix4 modelCone;
	modelCone = modelCone.Translate(modelCone, Vector3(-2, 2, 9));
	//m = m.Rotate(m, Vector3(1, 0, 1), 45);

	Matrix4 modelCylinder;
	modelCylinder = modelCylinder.Translate(modelCylinder, Vector3( 3, -1, 9));
	modelCylinder = modelCylinder.Rotate(modelCylinder, Vector3(-1, 0, 1), 15);

	sphere.SetModelMatrix(modelSphere);
	sphere.SetCamera(camera);
	sphere.SetProjection(obj2view);

	cone.SetModelMatrix(modelCone);
	cone.SetCamera(camera);
	cone.SetProjection(obj2view);

	cylinder.SetModelMatrix(modelCylinder);
	cylinder.SetCamera(camera);
	cylinder.SetProjection(obj2view);

	DirectionalLight dl(Vector3(0.9f, 0.0, -0.6f), Vector3(30,0,0),Vector3(140,0,0),Vector3(255,255,255));
	PointLight pl(Vector3(2,0, 10), Vector3(0, 15, 0), Vector3(0, 170, 0), Vector3(255, 255, 255));

	std::vector<Mesh> figures;
	figures = { sphere, cone, cylinder };

	for (auto& f: figures)
	{
		f.SetView();
		pl.Calculate(f);
		dl.Calculate(f);
	}

	//figures[2].SetColorPerVertex(Vector3(0, 255, 0), Vector3(0, 0, 255), Vector3(255, 0, 0));


	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			for (auto& t : figures)
			{
				t.Draw(i, j, buffer);
			}
		}
	}

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);
}
