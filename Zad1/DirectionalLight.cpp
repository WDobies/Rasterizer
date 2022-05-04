#include "DirectionalLight.h"
#include <iostream>

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, int shininess, float specularStrenght)
{
	this->position = position;
	this->ambientColor = ambient;
	this->diffuseColor = diffuse;
	this->specularColor = specular;
	this->shininess = shininess;
	this->specularStrenght = specularStrenght;
}

void DirectionalLight::Calculate(Mesh& mesh)
{
	if (!mesh.colors.empty()) mesh.colors.clear();
	for (int i = 0; i < mesh.vSize; ++i)
	{
		//vertices and normals
		Vector4 normals = mesh.model * Vector4(mesh.normals[i], 0);
		Vector4 vertices = mesh.model * Vector4(-mesh.vertices[i], 0);
		Vector3 N = Vector3(normals.x, normals.y, normals.z);
		Vector3 V = Vector3(vertices.x, vertices.y, vertices.z);
		V = Vector3::Normalize(V);
		N = Vector3::Normalize(N);

		//light position
		Vector4 pos = Vector4(position, 0);
		Vector3 lightPosition = Vector3(pos.x, pos.y, pos.z);
		lightPosition = lightPosition.Normalize();

		//difffuse
		float diffuse = Vector3::Dot(lightPosition, N);
		if (diffuse < 0) diffuse = 0;
		Vector3 dif = diffuseColor * diffuse;

		//specular
		Vector3 R = lightPosition - (N * 2 * (Vector3::Dot(lightPosition, N)));
		R = Vector3::Normalize(R);
		float specular = Vector3::Dot(R , V);
		Vector3 spec;

		if (specular > 0) 
		{
			specular = pow(specular, shininess);
			spec = specularColor * specular * specularStrenght ;
		}

		mesh.colors.push_back( dif + spec + ambientColor );
		if (mesh.colors[i].x > 255) mesh.colors[i].x = 255;
		if (mesh.colors[i].y > 255) mesh.colors[i].y = 255;
		if (mesh.colors[i].z > 255) mesh.colors[i].z = 255;

	}

	int i = 0;
	for (auto& t : mesh.triangles)
	{
		t.colorV1 += mesh.colors[(int)mesh.indices[i].y];
		t.colorV2 += mesh.colors[(int)mesh.indices[i].x];
		t.colorV3 += mesh.colors[(int)mesh.indices[i].z];
		if (t.colorV1.x > 255) t.colorV1.x = 255;
		if (t.colorV1.y > 255) t.colorV1.y = 255;
		if (t.colorV1.z > 255) t.colorV1.z = 255;

		if (t.colorV2.x > 255) t.colorV2.x = 255;
		if (t.colorV2.y > 255) t.colorV2.y = 255;
		if (t.colorV2.z > 255) t.colorV2.z = 255;

		if (t.colorV3.x > 255) t.colorV3.x = 255;
		if (t.colorV3.y > 255) t.colorV3.y = 255;
		if (t.colorV3.z > 255) t.colorV3.z = 255;
		i++;
	}
}

Vector3 DirectionalLight::CalculatePhong(Triangle& triangle)
{
	Vector3 V = -triangle.dv1 * triangle.L1 + -triangle.dv2 * triangle.L2 + -triangle.dv3 * triangle.L3;
	V = Vector3::Normalize(V);
	Vector3 N = triangle.n1 * triangle.L1 + triangle.n2 * triangle.L2 + triangle.n3 * triangle.L3;
	N = Vector3::Normalize(N);

	position = Vector3::Normalize(position);

	float diffuse = Vector3::Dot(position, N);
	if (diffuse < 0) diffuse = 0;
	Vector3 dif = diffuseColor * diffuse;

	Vector3 R = position - (N * 2 * (Vector3::Dot(position, N)));
	R = Vector3::Normalize(R);
	float specular = Vector3::Dot(R, V);
	Vector3 spec;

	if (specular > 0)
	{
		specular = pow(specular, 99);
		spec = specularColor * specular * 0.9;
	}

	return spec + dif + ambientColor;
}
