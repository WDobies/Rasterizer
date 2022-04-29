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
	for (auto& i : triangles)
	{
		i.SetView(projection, camera, model);
	}
}
