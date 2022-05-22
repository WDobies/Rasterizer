#pragma once
#include "stb_image.h"
#include "Vector3.h"

#define PI 3.14159265
#define TWO_PI 6.2831853

class Texture
{
public:
	Texture(const char* fileName);

	Vector3 GetColor(int x, int y);

	int width;
	int height;
	int chanels;
	unsigned char* data;
};

