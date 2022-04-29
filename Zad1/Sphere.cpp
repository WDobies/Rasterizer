#include "Sphere.h"
#include <iostream>

Sphere::Sphere(int vert, int horiz)
{
	tSize = 2 * vert * horiz;
	vSize = vert * (horiz + 2);

	float x,y,z, r;

	for (int yy = 0; yy <= horiz+1; ++yy)
	{
		y = cos(yy * 3.1415926 / (horiz + 1));
		float temp = 1 - y * y;
		r = sqrt(temp);

		for (int rr = 0; rr < vert; ++rr)
		{
			x = r * cos(2 * 3.1415926 * rr / vert);
			z = r * sin(2 * 3.1415926 * rr / vert);
			vertices.push_back(Vector3(x, y, z));
		}
	}

	for (int yy = 0; yy < horiz; ++yy)
	{
		for (int rr = 0; rr < vert; ++rr)
		{
			indices.push_back(Vector3(
				(rr + 1) % vert + yy * vert,
				rr + vert + yy * vert,
				(rr + 1) % vert + vert + yy * vert
			));
			indices.push_back(Vector3(
				rr + vert + yy * vert,
				rr+2*vert + yy*vert,				
				(rr + 1) % vert + vert + yy * vert
			));
		}
	}

	CalculateNormals();

	for (int i = 0; i < tSize; i++)
	{
		triangles.push_back(Triangle(vertices[(int)indices[i].y], vertices[(int)indices[i].x], vertices[(int)indices[i].z], Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), 1000, 1000));
	}
}

