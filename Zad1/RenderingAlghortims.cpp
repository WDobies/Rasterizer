#include <iostream>
#include <fstream>
#include "Triangle.h"
#include "DepthBuffer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ColorBuffer.h"

int main()
{
	std::ofstream img;
	img.open("image.ppm");

	ColorBuffer buffer(WIDTH, HEIGHT);

	//float* depthBuffer = new float[WIDTH * HEIGHT];
	//int* R = new int[WIDTH * HEIGHT];
	//int* G = new int[WIDTH * HEIGHT];
	//int* B = new int[WIDTH * HEIGHT];

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			//R[i * HEIGHT + j] = 0;
			//G[i * HEIGHT + j] = 0;
			//B[i * HEIGHT + j] = 0;
			DEPTHBUFFER[i* HEIGHT +j] = INFINITY;
		}
	}

	Triangle t(Vector3(0.7, 0.5, 3), Vector3(0.3, -0.4, 2), Vector3(-0.9, 0.6, 3), Vector3(255, 0, 0), Vector3(0, 255, 0), Vector3(0, 0, 255), WIDTH, HEIGHT);
	//Triangle d(Vector3(0.9, 0.5, 3), Vector3(0.3, -0.9, 1), Vector3(-0.6, 0.9, 3), Vector3(255, 255, 0), Vector3(40, 180, 100), Vector3(90, 140, 180), WIDTH, HEIGHT);
	//Triangle d(Vector3(0.8, 0.0, 2), Vector3(-0.9, 0.2, 3), Vector3(-0.6, 0.8, 2), Vector3(255, 255, 0), Vector3(40, 180, 100), Vector3(90, 140, 180), WIDTH, HEIGHT);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			t.Draw(i, j, buffer);
			//d.Draw(i, j, buffer);
		}
	}



	//if (img.is_open()) {
	//	img << "P3\n";
	//	img << WIDTH << " " << HEIGHT << "\n";
	//	img << "255\n";

	//	for (int i = 0; i < HEIGHT; i++)
	//	{
	//		for (int j = 0; j < WIDTH; j++)
	//		{
	//			img << R[i * HEIGHT + j] << " " << G[i * HEIGHT + j] << " " << B[i * HEIGHT + j] << "\n";
	//		}
	//	}
	//}

	//img.close();

	stbi_write_png("Image.png", buffer.width, buffer.height, 3, buffer.data, 0);
	
	//delete[] R,G,B;
}
