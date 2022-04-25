#include "Mesh.h"
#include <iostream>

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
