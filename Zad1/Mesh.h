#pragma once
#include "Vector3.h"
#include <vector>
#include "Rasterizer.h"
#include "ColorBuffer.h"
#define PI 3.1415926
class Mesh
{
public:
	int vSize;
	int tSize;

	Vector3* vertices;
	Vector3* indices;
	Vector3* normal;
	Vector3* color;

	std::vector<Rasterizer> triangles;

	void SetTranslation(Vector3 transform);
	void SetRotation(Vector3 axis, float angle);
	void SetScale(Vector3 scale);
	void SetView(Matrix4 obj2view, Matrix4 camera);
	void Draw(int& i, int& j, ColorBuffer& buffer);
	void SetColor(Vector3 color);

	~Mesh();
};

