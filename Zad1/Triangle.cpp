#include "Triangle.h"
#include <iostream>

Triangle::Triangle(float x1, float x2, float x3, float y1, float y2, float y3, int width, int height, int z1, int z2, int z3)
	: x1(x1), x2(x2), x3(x3), y1(y1), y2(y2), y3(y3), width(width), height(height), z1(z1), z2(z2), z3(z3)
{
	can();
	cut();

	dx12 = this->x1 - this->x2;
	dx23 = this->x2 - this->x3;
	dx31 = this->x3 - this->x1;
	dx32 = this->x3 - this->x2;
	dx13 = this->x1 - this->x3;
	dy12 = this->y1 - this->y2;
	dy23 = this->y2 - this->y3;
	dy31 = this->y3 - this->y1;
	dy13 = this->y1 - this->y3;

	if (dx12 < 0 || (dx12 == 0 && dx12 > 0)) { tl1 = true; }
	if (dx23 < 0 || (dx23 == 0 && dx23 > 0)) { tl2 = true; }
	if (dx31 < 0 || (dx31 == 0 && dx31 > 0)) { tl3 = true; }

	std::cout << tl1 << tl2 << tl3;

}

void Triangle::can()
{
	x1 = (int)((x1 + 1) * width * 0.5f);
	y1 = (int)((y1 + 1) * height * 0.5f);
	x2 = (int)((x2 + 1) * width * 0.5f);
	y2 = (int)((y2 + 1) * height * 0.5f);
	x3 = (int)((x3 + 1) * width * 0.5f);
	y3 = (int)((y3 + 1) * height * 0.5f);
}

void Triangle::cut()
{
	minx = std::min(x1, std::min(x2, x3));
	miny = std::min(y1, std::min(y2, y3));
	maxx = std::max(x1, std::max(x2, x3));
	maxy = std::max(y1, std::max(y2, y3));
}

void Triangle::Lambda(int& i, int& j)
{
	L1 = (dy23 * (j - x3) + dx32 * (i - y3)) / (dy23 * dx13 + dx32 * dy13);
	L2 = (dy31 * (j - x3) + dx13 * (i - y3)) / (dy31 * dx23 + dx13 * dy23);
	L3 = 1 - L2 - L1;

	R = L1 * c1[0] + L2 * c2[0] + L3 * c3[0];
	G = L1 * c1[1] + L2 * c2[1] + L3 * c3[1];
	B = L1 * c1[2] + L2 * c2[2] + L3 * c3[2];
}

bool Triangle::condition(int &i, int &j)
{
	float f1 = (((dx12) * (i - y1) - (dy12) * (j - x1)));
	float f2 = (((dx23) * (i - y2) - (dy23) * (j - x2)));
	float f3 = (((dx31) * (i - y3) - (dy31) * (j - x3)));

	if ((f1 == 0 ? tl1 : f1 > 0) &&
		(f2 == 0 ? tl2 : f2 > 0) &&
		(f3 == 0 ? tl3 : f3 > 0))
	{
		return true;
	}
	return false;
}

