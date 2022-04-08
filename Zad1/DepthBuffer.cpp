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
}

DepthBuffer::DepthBuffer() {}

DepthBuffer::~DepthBuffer()
{
	delete[] depthbuff;
}
