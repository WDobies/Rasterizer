#include "DirectionalLight.h"
#include <iostream>

void DirectionalLight::Calculate(Matrix4& camera, Matrix4& obj2view, int& vSize, std::vector<Vector3>& normals, std::vector<Vector3>& vertices, std::vector<Vector3>& color, std::vector<Vector3>& indices, std::vector<Triangle>& triangles)
{

	for (int i = 0; i < vSize; ++i)
	{
		Matrix4 model;
		model = model.Translate(model, Vector3(0, 0, 4));
		//model = model.Rotate(model,Vector3(1, 0, 0), 45);
		Vector4 g = obj2view * camera * model * Vector4(normals[i], 1);
		Vector4 p = obj2view * camera * model * Vector4(-vertices[i], 1);
		Vector3 N = Vector3(g.x, g.y, g.z);
		N = N.Normalize();
		Vector3 V = Vector3(p.x, p.y, p.z);

		Vector3 xd = Vector3(0.2f, 0, 0);
		Vector4 gg = obj2view * camera * Vector4(xd, 1);
		Vector3 fg = Vector3(gg.x, gg.y, gg.z);
		fg = fg.Normalize();
		Vector3 R = (N * 2 * (Vector3::Dot(fg, N))) - fg;
		float diff = Vector3::Dot(fg, N);
		float specular = Vector3::Dot(R = Vector3::Normalize(R), V=Vector3::Normalize(V));
		//specular = 1 / specular;
		//std::cout << diff << "\n";
		if (diff < 0) diff = 0;
		//if (diff > 1) diff = 1;
		Vector3 spec;
		if (specular > 0) {
			specular = pow(specular, 4);

			spec = Vector3(255, 255, 255) * specular * 0.7f ;
		}
		//else { spec = Vector3(0, 0, 0); }
		
		//if (specular < 0) specular = 0;
		//if (specular > 0) specular = 1;

		Vector3 dif = Vector3(140, 0, 0) * diff;

		Vector3 amb(30, 0, 0);
		color.push_back( dif + spec + amb );
		if (color[i].x > 255) color[i].x = 255;
		if (color[i].y > 255) color[i].y = 255;
		if (color[i].z > 255) color[i].z = 255;

	}
	int i = 0;
	for (auto& t : triangles)
	{
		t.colorV1 = color[(int)indices[i].y];
		t.colorV2 = color[(int)indices[i].x];
		t.colorV3 = color[(int)indices[i].z];
		i++;
	}
}
