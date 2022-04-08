#pragma once
#define WIDTH 600
#define HEIGHT 600
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

