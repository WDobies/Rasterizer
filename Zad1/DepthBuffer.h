#pragma once
#define WIDTH 1000
#define HEIGHT 1000
#define DEPTHBUFFER DepthBuffer::Instance(WIDTH, HEIGHT).depthbuff
class DepthBuffer
{
public:

	float* depthbuff;
	static DepthBuffer& Instance(int width, int height);

private:
	DepthBuffer(int width, int height);
	DepthBuffer();
	~DepthBuffer();
};

