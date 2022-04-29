#include "DirectionalLight.h"
#include <iostream>

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

	for (int i = 0; i < mesh.vSize; ++i)
	{
		//vertices and normals
		Vector4 normals = mesh.projection * mesh.camera *mesh.model * Vector4(mesh.normals[i], 1);
		Vector4 vertices = mesh.projection * mesh.camera * mesh.model * Vector4(-mesh.vertices[i], 1);
		Vector3 N = Vector3(normals.x, normals.y, normals.z);
		Vector3 V = Vector3(vertices.x, vertices.y, vertices.z);
		V = Vector3::Normalize(V);
		N = Vector3::Normalize(N);

		//light position
		Matrix4 d;
		d = Matrix4::Translate(d, Vector3(0, 0, 5));
		Vector4 pos = mesh.projection * mesh.camera  *Vector4(position, 1);
		Vector3 lightPosition = Vector3(pos.x, pos.y, pos.z);
		lightPosition = lightPosition.Normalize();

		//difffuse
		float diffuse = Vector3::Dot(lightPosition, N);
		if (diffuse < 0) diffuse = 0;
		Vector3 dif = diffuseColor * diffuse;

		//specular
		Vector3 R = (N * 2 * (Vector3::Dot(lightPosition, N))) - lightPosition;		
		R = Vector3::Normalize(R);
		float specular = Vector3::Dot(R , V);
		Vector3 spec;

		if (specular > 0) 
		{
			specular = pow(specular, 4);
			spec = specularColor * specular * 0.9f ;
		}

		mesh.colors.push_back( dif + spec + ambientColor );
		if (mesh.colors[i].x > 255) mesh.colors[i].x = 255;
		if (mesh.colors[i].y > 255) mesh.colors[i].y = 255;
		if (mesh.colors[i].z > 255) mesh.colors[i].z = 255;

	}

	int i = 0;
	for (auto& t : mesh.triangles)
	{
		t.colorV1 = mesh.colors[(int)mesh.indices[i].y];
		t.colorV2 = mesh.colors[(int)mesh.indices[i].x];
		t.colorV3 = mesh.colors[(int)mesh.indices[i].z];
		i++;
	}
}
