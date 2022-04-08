#pragma once

class ColorBuffer
{
public:

	int width;
	int height;
	int lenght;
	unsigned char* data;

	ColorBuffer(int width, int height);

	void FillColor(int r, int g, int b);
	void SetColor(int x, int y, int r, int g, int b);
};

