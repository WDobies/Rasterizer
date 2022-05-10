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
#include "DirectionalLightGourad.h"
#include "PointLightGourad.h"

int main()
{
	ColorBuffer buffer(WIDTH, HEIGHT);

	Sphere sphere(10, 10);
	Sphere shGourad(10, 10);
	//Sphere sph1(15, 15);
	//Cone cone(15, 1);
	//Cylinder cylinder(15, 5);

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	Matrix4 modelSphere;
	modelSphere = modelSphere.Translate(modelSphere, Vector3(2, -1, 7));

	Matrix4 mG;
	mG = mG.Translate(mG, Vector3(-2, -1, 7));
	//model = model.Rotate(model, Vector3(1, 0, 1), 45);

	//Matrix4 mS;
	//mS = mS.Translate(mS, Vector3(-3, -1, 13));
	////model = model.Rotate(model, Vector3(1, 0, 1), 45);

	//Matrix4 modelCone;
	//modelCone = modelCone.Translate(modelCone, Vector3(-2, 2, 9));
	////m = m.Rotate(m, Vector3(1, 0, 1), 45);

	//Matrix4 modelCylinder;
	//modelCylinder = modelCylinder.Translate(modelCylinder, Vector3( 3, -1, 9));
	//modelCylinder = modelCylinder.Rotate(modelCylinder, Vector3(-1, 0, 1), 15);

	sphere.SetModelMatrix(modelSphere);
	sphere.SetCamera(camera);
	sphere.SetProjection(obj2view);

	shGourad.SetModelMatrix(mG);
	shGourad.SetCamera(camera);
	shGourad.SetProjection(obj2view);

	//sph1.SetModelMatrix(mS);
	//sph1.SetCamera(camera);
	//sph1.SetProjection(obj2view);

	//cone.SetModelMatrix(modelCone);
	//cone.SetCamera(camera);
	//cone.SetProjection(obj2view);

	//cylinder.SetModelMatrix(modelCylinder);
	//cylinder.SetCamera(camera);
	//cylinder.SetProjection(obj2view);

	DirectionalLightGourad dl(Vector3(-0.6, 0, -0.1), Vector3(90,0,0),Vector3(190,0,0),Vector3(180,180,180));
	PointLightGourad pl(Vector3(5, 0, 2), Vector3(0, 90, 0), Vector3(0, 190, 0), Vector3(255, 255, 255));

	std::vector<Mesh> figures;
	figures = { sphere };

	shGourad.SetView();

	for (auto& f: figures)
	{
		f.SetView();
		//f.SetColor(Vector3(255, 255, 0));
		pl.Calculate(f);
		dl.Calculate(f);
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			for (auto& t : figures)
			{
				t.Draw(i, j, buffer);
			}
			for (auto& t : shGourad.triangles)
			{
				t.DrawPD(i, j, buffer);
			}
		}
	}

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);
}
