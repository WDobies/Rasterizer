#include "PointLightGourad.h"
#include <iostream>

PointLightGourad::PointLightGourad(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, int shininess, float specularStrenght)
{
	this->position = position;
	this->ambientColor = ambient;
	this->diffuseColor = diffuse;
	this->specularColor = specular;
	this->shininess = shininess;
	this->specularStrenght = specularStrenght;
}

void PointLightGourad::Calculate(Mesh& mesh)
{
	if (!mesh.colors.empty()) mesh.colors.clear();
	for (int i = 0; i < mesh.vSize; ++i)
	{
		//vertices and normals
		Vector4 normals = mesh.model * Vector4(mesh.normals[i], 0);
		Vector4 vertices = mesh.model * Vector4(mesh.vertices[i], 1);
		Vector3 N = Vector3(normals.x, normals.y, normals.z);
		Vector3 V = Vector3(vertices.x, vertices.y, vertices.z);
		
		N = Vector3::Normalize(N);

		//light position
		Vector4 pos = Vector4(position, 1);
		Vector3 lightPosition = Vector3(pos.x, pos.y, pos.z);
		Vector3 L =  lightPosition - V;	
		
		L = Vector3::Normalize(L);
		V = Vector3::Normalize(V);

		//difffuse
		float diffuse = Vector3::Dot(L, N);
		if (diffuse < 0) diffuse = 0;
		Vector3 dif = diffuseColor * diffuse;

		//specular
		Vector3 R = L - (N * 2 * (Vector3::Dot(L, N)));
		R = Vector3::Normalize(R);
		float specular = Vector3::Dot(R, V);
		Vector3 spec;

		if (specular > 0)
		{
			specular = pow(specular, shininess);
			spec = specularColor * specular * specularStrenght;
		}
		
		mesh.colors.push_back(dif + spec +ambientColor);
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
