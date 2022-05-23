#include "Mesh.h"
#include <iostream>

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

void Mesh::CalculateTexCoords()
{
	for (int i = 0; i < vSize; ++i)
	{
		texCoords.push_back(Vector3(0, 0, 0));
		//float v = 1 * asinf(vertices[(int)indices[i].x].y / 3.1415f) + 0.5f;
	}
	for (int i = 0; i < tSize; ++i)
	{
		float v1 = 1 * asinf(vertices[(int)indices[i].y].y / 3.1415f) + 0.5f;
		float v2 = 1 * asinf(vertices[(int)indices[i].x].y / 3.1415f) + 0.5f;
		float v3 = 1 * asinf(vertices[(int)indices[i].z].y / 3.1415f) + 0.5f;

		if (v1 < 0) v1 = 0;
		if (v2 < 0) v2 = 0;
		if (v3 < 0) v3 = 0;
		if (v1 > 1) v1 = 1;
		if (v2 > 1) v2 = 1;
		if (v3 > 1) v3 = 1;

		float u1 = 1 / (2 * 3.1415f) * atan2f(vertices[(int)indices[i].y].x, vertices[(int)indices[i].y].z) + 0.5f;
		float u2 = 1 / (2 * 3.1415f) * atan2f(vertices[(int)indices[i].x].x, vertices[(int)indices[i].x].z) + 0.5f;
		float u3 = 1 / (2 * 3.1415f) * atan2f(vertices[(int)indices[i].z].x, vertices[(int)indices[i].z].z) + 0.5f;

		if (u1 < 0) u1 = 0;
		if (u2 < 0) u2 = 0;
		if (u3 < 0) u3 = 0;
		if (u1 > 1) u1 = 1;
		if (u2 > 1) u2 = 1;
		if (u3 > 1) u3 = 1;

		texCoords[indices.at(i).y] = Vector3(u1,v1,0);
		texCoords[indices.at(i).x] = Vector3(u2,v2,0);
		texCoords[indices.at(i).z] = Vector3(u3,v3,0);
		//std::cout << u1 << " " << u2 << " " << u2 << "\n";
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

void Mesh::Draw(int& i, int& j, ColorBuffer& buffer,Texture& texture)
{
	for (auto& t : triangles)
	{
		t.Draw(i, j, buffer, texture);
	}
}
