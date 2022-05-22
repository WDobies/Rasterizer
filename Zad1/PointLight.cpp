#include "PointLight.h"
#include <iostream>

PointLight::PointLight(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, int shininess, float specularStrenght)
{
	this->position = position;
	this->ambientColor = ambient;
	this->diffuseColor = diffuse;
	this->specularColor = specular;
	this->shininess = shininess;
	this->specularStrenght = specularStrenght;
}

Vector3 PointLight::Calculate(Vector3 V, Vector3 N)
{
		//vertices and normals
		
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
		
		return dif + spec + ambientColor;
	
}
