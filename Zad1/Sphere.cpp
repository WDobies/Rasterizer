#include "Sphere.h"
#include <iostream>
#include "Mesh.h"

Sphere::Sphere(int vert, int horiz)
{
	tSize = 2 * vert * horiz;
	vSize = vert * (horiz + 2);

	vertices = new Vector3[vSize];
	indices = new Vector3[tSize];
	normal = new Vector3[vSize];
	color = new Vector3[vSize];

	float x,y,z,r;

	for (int yy = 0; yy <= horiz+1; ++yy)
	{
		y = cos(yy * PI / (horiz + 1));
		float temp = 1 - y * y;
		r = sqrt(temp);

		for (int rr = 0; rr < vert; ++rr)
		{
			x = r * cos(2 * PI * rr / vert);
			z = r * sin(2 * PI * rr / vert);
			vertices[(int)(rr + yy * vert)] = Vector3(x, y, z);
		}
	}

	for (int yy = 0; yy < horiz; ++yy)
	{
		for (int rr = 0; rr < vert; ++rr)
		{
			indices[(int)(rr + 2 * yy * vert)] = Vector3(
				(rr + 1) % vert + yy * vert,
				rr + vert + yy * vert,
				(rr + 1) % vert + vert + yy * vert
			);
			indices[(int)(rr + vert +2 * yy * vert)] = Vector3(
				rr + vert + yy * vert,
				rr+2*vert + yy*vert,				
				(rr + 1) % vert + vert + yy * vert
			);
		}
	}


	Vector3 n;
	for (int i = 0; i < vSize; ++i)
	{
		normal[i] = Vector3(0, 0, 0);
	}
	for (int i = 0; i < tSize; ++i)
	{
		Vector3 a1 = vertices[(int)indices[i].z] - vertices[(int)indices[i].x];
		Vector3 a2 = vertices[(int)indices[i].y] - vertices[(int)indices[i].x];

		n = Vector3::Cross(a1, a2);
		n = Vector3::Normalize(n);

		normal[i] += n;

	}
	for (int i = 0; i < vSize; ++i)
	{
		normal[i] = normal[i].Normalize();
		//std::cout << normal[i].ToString() << "\n";
	}

	for (int i = 0; i < tSize; i++)
	{
		triangles.push_back(Rasterizer(vertices[(int)indices[i].y], vertices[(int)indices[i].x], vertices[(int)indices[i].z]));
	}
}
