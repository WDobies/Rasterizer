#include "DepthBuffer.h"
#include <iostream>

DepthBuffer& DepthBuffer::Instance(int width, int height)
{
	static DepthBuffer buffer(WIDTH, HEIGHT);
	return buffer;
}

DepthBuffer::DepthBuffer(int width, int height)
{
	depthbuff = new float[width * height];

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			depthbuff[i * HEIGHT + j] = INFINITY;
		}
	}
}

DepthBuffer::~DepthBuffer()
{
	delete[] depthbuff;
}
