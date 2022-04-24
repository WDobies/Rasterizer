#include "Cylinder.h"

Cylinder::Cylinder(int vert, int horiz, float radius)
{
	tSize = 2 * vert * horiz;
	vSize = vert * (horiz + 2);

	vertices = new Vector3[vSize];
	indices = new Vector3[tSize];

	float x, y, z, r;

	for (int yy = 0; yy <= horiz + 1; ++yy)
	{
		y = cos(yy * PI / (horiz + 1));

		float temp = 1 - y*y;
		
		if (yy == 0) 
		{ 
			r = 0;
			y = cos((yy + 1) * PI / (horiz + 1));
		}
		else if (yy == horiz + 1)
		{	r = 0;
			y = cos((yy - 1) * PI / (horiz + 1));
		}
		else r = radius;
	

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
			indices[(int)(rr + vert + 2 * yy * vert)] = Vector3(
				rr + vert + yy * vert,
				rr + 2 * vert + yy * vert,
				(rr + 1) % vert + vert + yy * vert
			);
		}
	}

	for (int i = 0; i < tSize; i++)
	{
		triangles.push_back(Rasterizer(vertices[(int)indices[i].y], vertices[(int)indices[i].x], vertices[(int)indices[i].z]));
	}
}
