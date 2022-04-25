#include "Cylinder.h"
#include <iostream>

Cylinder::Cylinder(int vert, int horiz, float radius)
{
	tSize = 2 * vert * horiz;
	vSize = vert * (horiz + 2);

	vertices = new Vector3[vSize];
	indices = new Vector3[tSize];
	normal = new Vector3[vSize];
	color = new Vector3[vSize];
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

	Matrix4 camera;
	camera = camera.LookAt(Vector3(0, 0, 0), Vector3(0, 0, 10), Vector3(0, 1, 0));

	Matrix4 obj2view;
	obj2view.Perspective(50, 1.f, 0.1f, 100.f);

	for (auto &t: triangles)
	{
		t.SetTranslation(Vector3(0, -1, 15));
	}

	for (int i = 0; i < vSize; ++i)
	{
		Vector4 g = obj2view * camera * Vector4(normal[i], 1);
		Vector4 p = obj2view * camera * Vector4(-vertices[i], 1);
		Vector3 N = Vector3(g.x, g.y, g.z);
		N = N.Normalize();
		Vector3 V = Vector3(p.x, p.y, p.z);
		Vector3 fg = Vector3(2, 0, 1);
		//fg = fg.Normalize();
		Vector3 R = fg - (N * 2 * (Vector3::Dot(fg, N)));
		float diff = Vector3::Dot(fg, N);
		float specular = Vector3::Dot(R, V);
		std::cout << specular << "\n";
		if (diff < 0) diff = 0;
		if (diff > 0) diff = 1;
		Vector3 spec;
		if (specular > 0) {
			specular = pow(specular, 1);

			spec = Vector3(0,0, 255) * specular * 0.1;
		}
		else { spec = Vector3(0, 0, 0); }
		//if (specular < 0) specular = 0;
		//if (specular > 0) specular = 1;
		
		Vector3 dif = Vector3(180, 0, 0)* diff;

		Vector3 amb(100, 0, 0);
		color[i] = dif + amb + spec;
		if (color[i].x > 255) color[i].x = 255;
		if (color[i].y > 255) color[i].y = 255;
		if (color[i].z > 255) color[i].z = 255;
		//SetColor(col);
		
	}

	for (int i = 0; i < tSize; i++)
	{
		triangles.push_back(Rasterizer(vertices[(int)indices[i].y], vertices[(int)indices[i].x], vertices[(int)indices[i].z], color[(int)indices[i].y], color[(int)indices[i].x], color[(int)indices[i].z]));
	}
}
