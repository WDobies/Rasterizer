#include <iostream>
#include <fstream>
#include "Triangle.h"

void can(float& x, float& y, int width, int height) {
    x = (int)((x + 1) * width * 0.5f);
    y = (int)((y + 1) * height * 0.5f);
}

void cut(float& x1, float& x2, float& x3, float& y1, float& y2, float& y3, int& minx, int& miny, int& maxx, int& maxy) {
    minx = std::min(x1, std::min(x2, x3));
    miny = std::min(y1, std::min(y2, y3));
    maxx = std::max(x1, std::max(x2, x3));
    maxy = std::max(y1, std::max(y2, y3));
}

int main()
{
    int width = 200;
    int height = 200;

    std::ofstream img;
    img.open("image.ppm");

    float x1 = 0.8f;
    float y1 = 0.0f;

    float x2 = 0.5f;
    float y2 = -0.9f;

    float x3 = -0.9f;
    float y3 = 0.2f;

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

    Triangle t(x1, x2, x3, y1, y2, y3, width, height, -2, 1, -2);
    Triangle d(0.9f, 0.2, -0.6, 0.8f, -0.6, 0.8f, width, height, 1, -2, 1);

    if (img.is_open()) {
        img << "P3\n";
        img << width << " " << height << "\n";
        img << "255\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
               // if (i > t.miny && i<t.maxy && j>t.minx && j < t.maxx) 
                
                if (t.condition(i, j))
                {
                    t.Lambda(i, j);

                    float depth = t.L1 * t.z1 + t.L2 * t.z2 + t.L3 * t.z3;
                    if (depth < depthBuffer[i][j])
                    {
                        R[i][j] = t.R;
                        G[i][j] = t.G;
                        B[i][j] = t.B;
                        depthBuffer[i][j] = depth;
                    }
                    //img << t.R << " " << t.G << " " << t.B << "\n";
                }
                if (d.condition(i,j)) {
                    d.Lambda(i, j);

                    float depth = d.L1 * d.z1 + d.L2 * d.z2 + d.L3 * d.z3;
                    if (depth < depthBuffer[i][j])
                    {
                        R[i][j] = d.R;
                        G[i][j] = d.G;
                        B[i][j] = d.B;
                    }
                }
                
            }
        }
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
