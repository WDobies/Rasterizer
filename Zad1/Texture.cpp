#include "Texture.h"
#include <iostream>

Texture::Texture(const char* fileName)
{
	this->data = stbi_load(fileName, &this->width, &this->height, &this->chanels , 3);
}

Vector3 Texture::GetColor(int x, int y)
{
	int pixel = (y * width + x) * 3;
	return Vector3(data[pixel], data[pixel + 1], data[pixel + 2]);
}
