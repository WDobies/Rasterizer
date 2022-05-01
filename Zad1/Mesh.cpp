#include "Mesh.h"

void Mesh::CalculateNormals()
{
	for (int i = 0; i < vSize; ++i)
	{
		normals.push_back(Vector3(0, 0, 0));
	}
	Vector3 n;
	for (int i = 0; i < tSize; ++i)
	{
		Vector3 a1 = vertices[(int)indices[i].z] - vertices[(int)indices[i].x];
		Vector3 a2 = vertices[(int)indices[i].y] - vertices[(int)indices[i].x];

		n = Vector3::Cross(a1, a2);
		n = Vector3::Normalize(n);

		normals[indices.at(i).x] += n;
		normals[indices.at(i).y] += n;
		normals[indices.at(i).z] += n;

	}
	for (int i = 0; i < vSize; ++i)
	{
		normals[i] = normals[i].Normalize();
	}
}

void Mesh::SetCamera(Matrix4& camera)
{
	this->camera = camera;
}

void Mesh::SetProjection(Matrix4& projection)
{
	this->projection = projection;
}

void Mesh::SetModelMatrix(Matrix4& model)
{
	this->model = model;
}

void Mesh::SetView()
{
	for (auto& t : triangles)
	{
		t.SetView(projection, camera, model);
	}
}

void Mesh::SetColor(const Vector3& color)
{
	for (auto& t : triangles)
	{
		t.colorV1 = color;
		t.colorV2 = color;
		t.colorV3 = color;
	}
}

void Mesh::SetColorPerVertex(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	for (auto& t : triangles)
	{
		t.colorV1 = v1;
		t.colorV2 = v2;
		t.colorV3 = v3;
	}
}

void Mesh::Draw(int& i, int& j, ColorBuffer& buffer)
{
	for (auto& t : triangles)
	{
		t.Draw(i, j, buffer);
	}
}
