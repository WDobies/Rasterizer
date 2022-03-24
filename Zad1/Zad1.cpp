#include <iostream>
#include <fstream>
#include "Triangle.h"

int main()
{
	int width = 200;
	int height = 200;

	std::ofstream img;
	img.open("image.ppm");

	float depthBuffer[200][200];
	int R[200][200];
	int G[200][200];
	int B[200][200];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			R[i][j] = 0;
			G[i][j] = 0;
			B[i][j] = 0;
			depthBuffer[i][j] = INFINITY;
		}
	}

	Triangle t(Vector3(0.8, 0, -2), Vector3(0.5, -0.9, 1), Vector3(-0.9, 0.2, -2), Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), width, height);
	Triangle d(Vector3(0.9, 0.8, 1), Vector3(0.2, -0.6, -2), Vector3(-0.6, 0.8, 1), Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), width, height);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (t.condition(i, j))
			{
				float depth = t.L1 * t.v1.z + t.L2 * t.v2.z + t.L3 * t.v3.z;
				if (depth < depthBuffer[i][j])
				{
					R[i][j] = t.R;
					G[i][j] = t.G;
					B[i][j] = t.B;
					depthBuffer[i][j] = depth;
				}
			}
			if (d.condition(i, j)) {

				float depth = d.L1 * d.v1.z + d.L2 * d.v2.z + d.L3 * d.v3.z;
				if (depth < depthBuffer[i][j])
				{
					R[i][j] = d.R;
					G[i][j] = d.G;
					B[i][j] = d.B;
					depthBuffer[i][j] = depth;
				}
			}

		}
	}
	if (img.is_open()) {
		img << "P3\n";
		img << width << " " << height << "\n";
		img << "255\n";

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				img << R[i][j] << " " << G[i][j] << " " << B[i][j] << "\n";
			}
		}
	}

	img.close();
}
