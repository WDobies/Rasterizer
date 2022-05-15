#include "Triangle.h"
#include <iostream>
#include "Matrix4.h"
#include "ColorBuffer.h"
#include "DepthBuffer.h"


Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3, Vector3 c1, Vector3 c2, Vector3 c3, int width, int height) : 
	v1(v1), v2(v2), v3(v3), n1(n1), n2(n2), n3(n3),colorV1(c1), colorV2(c2), colorV3(c3), width(width), height(height)
{
	dv1 = v1;
	dv2 = v2;
	dv3 = v3;
	model = Matrix4::Identity();
}

void Triangle::SetView(Matrix4 obj2view, Matrix4 camera, Matrix4 m) {

	Vector4 p1 = obj2view * camera * m * Vector4(v1, 1);
	Vector4 p2 = obj2view * camera * m * Vector4(v2, 1);
	Vector4 p3 = obj2view * camera * m * Vector4(v3, 1);

	this->v1 = Vector3(p1.x / p1.w, p1.y / p1.w, p1.z / p1.w);
	this->v2 = Vector3(p2.x / p2.w, p2.y / p2.w, p2.z / p2.w);
	this->v3 = Vector3(p3.x / p3.w, p3.y / p3.w, p3.z / p3.w);

	PixelCoords();
	MinSpace();

	dx12 = this->v1.x - this->v2.x;
	dx23 = this->v2.x - this->v3.x;
	dx31 = this->v3.x - this->v1.x;
	dx32 = this->v3.x - this->v2.x;
	dx13 = this->v1.x - this->v3.x;
	dy12 = this->v1.y - this->v2.y;
	dy23 = this->v2.y - this->v3.y;
	dy31 = this->v3.y - this->v1.y;
	dy13 = this->v1.y - this->v3.y;

	//find top and left edges
	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) { tl1 = true; }
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) { tl2 = true; }
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) { tl3 = true; }
}

void Triangle::Draw(int& i, int& j, ColorBuffer& buffer)
{
	if (isInsideTriangle(i, j))
	{
		L1 = (dy23 * (j - v3.x) + dx32 * (i - v3.y)) / (dy23 * dx13 + dx32 * dy13);
		L2 = (dy31 * (j - v3.x) + dx13 * (i - v3.y)) / (dy31 * dx23 + dx13 * dy23);
		L3 = 1 - L2 - L1;

		R = L1 * colorV1.x + L2 * colorV2.x + L3 * colorV3.x;
		G = L1 * colorV1.y + L2 * colorV2.y + L3 * colorV3.y;
		B = L1 * colorV1.z + L2 * colorV2.z + L3 * colorV3.z;

		float depth = L1 * v1.z + L2 * v2.z + L3 * v3.z;
		if (depth < DEPTHBUFFER[i * HEIGHT + j])
		{
			buffer.SetColor(j, i, R, G, B);
			DEPTHBUFFER[i * HEIGHT + j] = depth;
		}
	}
}

void Triangle::PixelCoords()
{
	v1.x = (int)((v1.x + 1) * WIDTH * 0.5f);
	v1.y = (int)((v1.y + 1) * HEIGHT * 0.5f);
	v2.x = (int)((v2.x + 1) * WIDTH * 0.5f);
	v2.y = (int)((v2.y + 1) * HEIGHT * 0.5f);
	v3.x = (int)((v3.x + 1) * WIDTH * 0.5f);
	v3.y = (int)((v3.y + 1) * HEIGHT * 0.5f);
}

void Triangle::MinSpace()
{
	minx = std::min(v1.x, std::min(v2.x, v3.x));
	miny = std::min(v1.y, std::min(v2.y, v3.y));
	maxx = std::max(v1.x, std::max(v2.x, v3.x));
	maxy = std::max(v1.y, std::max(v2.y, v3.y));
}

void Triangle::Lambda(int& i, int& j)
{
	//baricentric cords
	L1 = (dy23 * (j - v3.x) + dx32 * (i - v3.y)) / (dy23 * dx13 + dx32 * dy13);
	L2 = (dy31 * (j - v3.x) + dx13 * (i - v3.y)) / (dy31 * dx23 + dx13 * dy23);
	L3 = 1 - L2 - L1;

	//Vector3 V = -dv1 * L1 + -dv2 * L2 + -dv3 * L3;
	//V = Vector3::Normalize(V);
	//Vector3 N = n1 * L1 + n2 * L2 + n3 * L3;
	//N = Vector3::Normalize(N);

	//Vector3 lightPosition(0.2, 0, -0.5);
	//lightPosition = lightPosition.Normalize();

	//float diffuse = Vector3::Dot(lightPosition, N);
	//if (diffuse < 0) diffuse = 0;
	//Vector3 dif = Vector3(255,0,0) * diffuse;

	//Vector3 Rr = lightPosition - (N * 2 * (Vector3::Dot(lightPosition, N)));
	//Rr = Vector3::Normalize(Rr);
	//float specular = Vector3::Dot(Rr, V);
	//Vector3 spec;

	//if (specular > 0)
	//{
	//	specular = pow(specular, 99);
	//	spec = Vector3(255,255,255) * specular * 0.9;
	//}

	//colorV1 = dif + spec + Vector3(40, 0, 0);
	//colorV2 = dif + spec + Vector3(40, 0, 0);
	//colorV3 = dif + spec + Vector3(40, 0, 0);

	//CutColorRange();
	//std::cout << p.ToString() << "\n";

	//color for each pixel
	R = L1 * colorV1.x + L2 * colorV2.x + L3 * colorV3.x;
	G = L1 * colorV1.y + L2 * colorV2.y + L3 * colorV3.y;
	B = L1 * colorV1.z + L2 * colorV2.z + L3 * colorV3.z;
}

void Triangle::SetTranslation(Vector3 t)
{
	model = Matrix4::Translate(model,t);
}

void Triangle::SetRotation(Vector3 axis, float angle)
{
	model = Matrix4::Rotate(model, axis, angle);
}

void Triangle::SetScale(Vector3 s)
{
	model = Matrix4::Scale(model, s);
}

void Triangle::CutColorRange()
{
	if (colorV1.x > 255) colorV1.x = 255;
	if (colorV1.y > 255) colorV1.y = 255;
	if (colorV1.z > 255) colorV1.z = 255;
	if (colorV2.x > 255) colorV2.x = 255;
	if (colorV2.y > 255) colorV2.y = 255;
	if (colorV2.z > 255) colorV2.z = 255;
	if (colorV3.x > 255) colorV3.x = 255;
	if (colorV3.y > 255) colorV3.y = 255;
	if (colorV3.z > 255) colorV3.z = 255;
}

bool Triangle::isInsideTriangle(int &i, int &j)
{
	if(i >= miny && i<maxy&& j>=minx && j < maxx) 
	{
		// check if pixel is inside triangle
		float f1 = (((dx12) * (i - v1.y) - (dy12) * (j - v1.x)));
		float f2 = (((dx23) * (i - v2.y) - (dy23) * (j - v2.x)));
		float f3 = (((dx31) * (i - v3.y) - (dy31) * (j - v3.x)));

		//test if its top or left edge
		if ((f1 == 0 ? tl1 : f1 > 0) &&
			(f2 == 0 ? tl2 : f2 > 0) &&
			(f3 == 0 ? tl3 : f3 > 0))
		{
			return true;
		}
	}
	return false;
}

