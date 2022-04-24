#include "Sphere.h"
#include <iostream>

Sphere::Sphere(int vert, int horiz)
{
	tSize = 2 * vert * horiz;
	vSize = vert * (horiz + 2);

	vertices = new Vector3[vSize];
	indices = new Vector3[tSize];

	float x,y,z, r;

	for (int yy = 0; yy <= horiz+1; ++yy)
	{
		y = cos(yy * 3.1415926 / (horiz + 1));

		float temp = 1 - y * y;
		r = 0.5;
		if (yy == 0 || yy == horiz + 1) {
			r = 0;
			if(yy==0) y = cos((yy+1) * 3.1415926 / (horiz + 1));
			if (yy == horiz + 1) y = cos((yy - 1) * 3.1415926 / (horiz + 1));
		}

		for (int rr = 0; rr < vert; ++rr)
		{

			x = r * cos(2 * 3.1415926 * rr / vert);
			z = r * sin(2 * 3.1415926 * rr / vert);
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
}

Sphere::~Sphere()
{
	delete[] vertices, indices;
}
