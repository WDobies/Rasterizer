#include "Mesh.h"
#include <iostream>

void Mesh::SetLight()
{
	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	for (int i = 0; i < vSize; ++i)
	{
		Vector4 g = obj2view * camera * Vector4(normal[i], 1);
		Vector4 p = obj2view * camera * Vector4(-vertices[i], 1);
		Vector3 N = Vector3(g.x, g.y, g.z);
		N = N.Normalize();
		Vector3 V = Vector3(p.x, p.y, p.z);
		Vector3 fg = Vector3(2, 0, 1);
		//fg = fg.Normalize();
		Vector3 R = fg - (N * 2 * (Vector3::Dot(fg, N)));
		float diff = Vector3::Dot(fg, N);
		float specular = Vector3::Dot(R, V);
		std::cout << specular << "\n";
		if (diff < 0) diff = 0;
		if (diff > 0) diff = 1;
		Vector3 spec;
		if (specular > 0) {
			specular = pow(specular, 1);

			spec = Vector3(0, 0, 255) * specular * 0.1;
		}
		else { spec = Vector3(0, 0, 0); }
		//if (specular < 0) specular = 0;
		//if (specular > 0) specular = 1;

		Vector3 dif = Vector3(180, 0, 0) * diff;

		Vector3 amb(100, 0, 0);
		color[i] = dif + amb + spec;
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

void Mesh::SetTranslation(Vector3 transform)
{
	for (auto& t : triangles)
	{
		t.SetTranslation(transform);
	}
}

void Mesh::SetRotation(Vector3 axis, float angle)
{
	for (auto& t : triangles)
	{
		t.SetRotation((axis), angle);
	}
}

void Mesh::SetScale(Vector3 scale)
{
	for (auto& t : triangles)
	{
		t.SetScale(scale);
	}
}

void Mesh::SetView(Matrix4 obj2view, Matrix4 camera)
{
	for (auto& t : triangles)
	{
		t.SetView(obj2view, camera);
	}
}

void Mesh::Draw(int& i, int& j, ColorBuffer& buffer)
{
	for (auto& t : triangles)
	{
		t.Draw(i, j, buffer);
	}
}

void Mesh::SetColor(Vector3 color)
{
	for (auto& t : triangles)
	{
		t.colorV1 = color;
		t.colorV2 = color;
		t.colorV3 = color;
	}
}

Mesh::~Mesh()
{
	delete[] vertices, indices, normal, color;
	triangles.clear();
}
