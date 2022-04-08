#include "ColorBuffer.h"

ColorBuffer::ColorBuffer(int width, int height) : width(width), height(height)
{
	lenght = width * height;
	data = new unsigned char[lenght * 3];
}

void ColorBuffer::FillColor(int r, int g, int b)
{
	for (int i = 0; i < lenght; i++)
	{
		data[i * 3]		= r;	
		data[i * 3 + 1] = g;
		data[i * 3 + 2] = b;
	}
}

void ColorBuffer::SetColor(int x, int y, int r, int g, int b)
{
	int pixel = (y * width + x) * 3;
	data[pixel] = r;
	data[pixel + 1] = g;
	data[pixel + 2] = b;
}