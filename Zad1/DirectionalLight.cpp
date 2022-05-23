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


Vector3 DirectionalLight::Calculate(Vector3 V, Vector3 N, Vector3 texture)
{
	V = Vector3::Normalize(V);
	N = Vector3::Normalize(N);

	position = Vector3::Normalize(position);

	float diffuse = Vector3::Dot(position, N);
	if (diffuse < 0) diffuse = 0;
	Vector3 dif = diffuseColor * diffuse * texture * 0.00392f;

	Vector3 R = position - (N * 2 * (Vector3::Dot(position, N)));
	R = Vector3::Normalize(R);
	float specular = Vector3::Dot(R, V);
	Vector3 spec;

	if (specular > 0)
	{
		specular = pow(specular, shininess);
		spec = specularColor * specular * specularStrenght * texture * 0.00392f;
	}

	//ambientColor = texture;

	return spec + dif + ambientColor * texture * 0.00392f;
}
