#pragma once
#include "Vector3.h"
class Sphere
{
public:
	int vSize;
	int tSize;

	Vector3* vertices;
	Vector3* indices;

	Sphere(int vert, int horiz);
	~Sphere();
};

