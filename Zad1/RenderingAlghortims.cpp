#include <iostream>
#include <fstream>
#include "Triangle.h"
#include "DepthBuffer.h"
#include "Texture.h"

#include "ColorBuffer.h"
#include "Sphere.h"
#include <vector>
#include "Cylinder.h"
#include "Cone.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"


int main()
{
	ColorBuffer buffer(WIDTH, HEIGHT);

	Texture texture1("earth.png");
	Texture texture2("UV.png");
	//std::cout<<texture.GetColor(10, 10).ToString();

	Sphere sphere(10,10);
	Sphere sphere2(10, 10);
	Sphere cylinder(10, 10);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, -5), Vector3(0, 0, 10), Vector3(0, 1, 0));

	Matrix4 modelSphere;
	modelSphere = modelSphere.Translate(modelSphere, Vector3(0, 0, 7));
	modelSphere = modelSphere.Rotate(modelSphere, Vector3(0, 1, 0), 90);

	Matrix4 modelSphere2;
	modelSphere2 = modelSphere2.Translate(modelSphere2, Vector3(2, 0, 5));
	modelSphere2 = modelSphere2.Rotate(modelSphere2, Vector3(0, 1, 0), 120);

	Matrix4 modelCylinder;
	modelCylinder = modelCylinder.Translate(modelCylinder, Vector3(-2, 0, 5));
	modelCylinder = modelCylinder.Rotate(modelCylinder, Vector3(0, 1, 0), 120);

	sphere.SetModelMatrix(modelSphere);
	sphere.SetCamera(camera);
	sphere.SetProjection(obj2view);

	sphere2.SetModelMatrix(modelSphere2);
	sphere2.SetCamera(camera);
	sphere2.SetProjection(obj2view);

	cylinder.SetModelMatrix(modelCylinder);
	cylinder.SetCamera(camera);
	cylinder.SetProjection(obj2view);

	//DirectionalLight dl(Vector3(-0.4f, 0.0, -0.2f), Vector3(50,0,0),Vector3(210,0,0),Vector3(255,255,255));
	PointLight pl(Vector3(5,0, 3), Vector3(75, 75, 75), Vector3(210, 210, 210), Vector3(255, 255, 255));


	sphere.SetView();
	sphere2.SetView();
	cylinder.SetView();

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			sphere.Draw(i, j, buffer,texture2,pl);
			sphere2.Draw(i, j, buffer, texture2);
			cylinder.Draw(i, j, buffer, texture1, pl);
		}
	}

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);
}
