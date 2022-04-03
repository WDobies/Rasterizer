#include "Triangle.h"
#include <iostream>
#include "Matrix4.h"


Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 c1, Vector3 c2, Vector3 c3, int width, int height) : 
	v1(v1), v2(v2), v3(v3), colorV1(c1), colorV2(c2), colorV3(c3), width(width), height(height)
{
	Matrix4 obj2view;
	obj2view.Perspective(45.f,1.f,-1.f,10.f);
	std::cout<<obj2view.ToString();

	Vector4 p1 = obj2view * Vector4(v1, 1);
	Vector4 p2 = obj2view * Vector4(v2, 1);
	Vector4 p3 = obj2view * Vector4(v3, 1);

	this->v1 = Vector3(p1.x / p1.w, p1.y / p1.w, p1.z / p1.w);
	this->v2 = Vector3(p2.x / p2.w, p2.y / p2.w, p2.z / p2.w);
	this->v3 = Vector3(p3.x / p3.w, p3.y / p3.w, p3.z / p3.w);

	std::cout << this->v1.ToString();
	std::cout << this->v2.ToString();
	std::cout << this->v3.ToString();

	can();
	cut();
	std::cout << this->v1.ToString();
	std::cout << this->v2.ToString();
	std::cout << this->v3.ToString();
	dx12 = this->v1.x - this->v2.x;
	dx23 = this->v2.x - this->v3.x;
	dx31 = this->v3.x - this->v1.x;
	dx32 = this->v3.x - this->v2.x;
	dx13 = this->v1.x - this->v3.x;
	dy12 = this->v1.y - this->v2.y;
	dy23 = this->v2.y - this->v3.y;
	dy31 = this->v3.y - this->v1.y;
	dy13 = this->v1.y - this->v3.y;

	if (dx12 < 0 || (dx12 == 0 && dx12 > 0)) { tl1 = true; }
	if (dx23 < 0 || (dx23 == 0 && dx23 > 0)) { tl2 = true; }
	if (dx31 < 0 || (dx31 == 0 && dx31 > 0)) { tl3 = true; }
}

void Triangle::can()
{
	v1.x = (int)((v1.x + 1) * width * 0.5f);
	v1.y = (int)((v1.y + 1) * height * 0.5f);
	v2.x = (int)((v2.x + 1) * width * 0.5f);
	v2.y = (int)((v2.y + 1) * height * 0.5f);
	v3.x = (int)((v3.x + 1) * width * 0.5f);
	v3.y = (int)((v3.y + 1) * height * 0.5f);
}

void Triangle::cut()
{
	minx = std::min(v1.x, std::min(v2.x, v3.x));
	miny = std::min(v1.y, std::min(v2.y, v3.y));
	maxx = std::max(v1.x, std::max(v2.x, v3.x));
	maxy = std::max(v1.y, std::max(v2.y, v3.y));
}

void Triangle::Lambda(int& i, int& j)
{
	L1 = (dy23 * (j - v3.x) + dx32 * (i - v3.y)) / (dy23 * dx13 + dx32 * dy13);
	L2 = (dy31 * (j - v3.x) + dx13 * (i - v3.y)) / (dy31 * dx23 + dx13 * dy23);
	L3 = 1 - L2 - L1;

	R = L1 * colorV1.x + L2 * colorV2.x + L3 * colorV3.x;
	G = L1 * colorV1.y + L2 * colorV2.y + L3 * colorV3.y;
	B = L1 * colorV1.z + L2 * colorV2.z + L3 * colorV3.z;
}

bool Triangle::condition(int &i, int &j)
{
	if(i > miny && i<maxy&& j>minx && j < maxx) 
	{
		float f1 = (((dx12) * (i - v1.y) - (dy12) * (j - v1.x)));
		float f2 = (((dx23) * (i - v2.y) - (dy23) * (j - v2.x)));
		float f3 = (((dx31) * (i - v3.y) - (dy31) * (j - v3.x)));

		if ((f1 == 0 ? tl1 : f1 > 0) &&
			(f2 == 0 ? tl2 : f2 > 0) &&
			(f3 == 0 ? tl3 : f3 > 0))
		{
			Lambda(i, j);
			return true;
		}
	}
	return false;
}

