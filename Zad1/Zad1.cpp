#include <iostream>
#include <fstream>

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
    int r = 255;
    int g = 255;
    int b = 255;
    int minx, miny, maxx, maxy;

    std::ofstream img;
    img.open("image.ppm");

    float x1 = 1.3f;
    float y1 = 0.8f;

    float x2 = 0.0f;
    float y2 = -0.9f;

    float x3 = -0.9f;
    float y3 = 0.9f;

    int c1[] = { 255, 255, 1 };
    int c2[] = { 0, 0, 255 };
    int c3[] = { 0, 255, 0 };

    can(x1, y1, width, height);
    can(x2, y2, width, height);
    can(x3, y3, width, height);

    std::cout << x1 << " " << y1 << "\n";
    std::cout << x2 << " " << y2 << "\n";
    std::cout << x3 << " " << y3 << "\n";

    cut(x1, x2, x3, y1, y2, y3, minx, miny, maxx, maxy);

    float dx12 = x1 - x2;
    float dx23 = x2 - x3;
    float dx31 = x3 - x1;
    float dx32 = x3 - x2;
    float dx13 = x1 - x3;
    float dy12 = y1 - y2;
    float dy23 = y2 - y3;
    float dy31 = y3 - y1;
    float dy13 = y1 - y3;

    if (img.is_open()) {
        img << "P3\n";
        img << width << " " << height << "\n";
        img << "255\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i>miny && i<maxy && j>minx && j<maxx)
                {
                    if ((((dx12) * (i - y1) - (dy12) * (j - x1)) > 0) &&
                        (((dx23) * (i - y2) - (dy23) * (j - x2)) > 0) &&
                        (((dx31) * (i - y3) - (dy31) * (j - x3)) > 0))
                    {
                        float Y1 = (dy23 * (j - x3) + dx32 * (i - y3)) / (dy23 * dx13 + dx32 * dy13);
                        float Y2 = (dy31 * (j - x3) + dx13 * (i - y3)) / (dy31 * dx23 + dx13 * dy23);
                        float Y3 = 1 - Y2 - Y1;

                        int mR = Y1 * c1[0] + Y2 * c2[0] + Y3 * c3[0];
                        int mG = Y1 * c1[1] + Y2 * c2[1] + Y3 * c3[1];
                        int mB = Y1 * c1[2] + Y2 * c2[2] + Y3 * c3[2];

                        img <<mR<< " " << mG << " " <<mB << "\n";
                    }
                    else {
                        img << 0 << " " << 0 << " " << 0 << "\n";
                    }
                }
                else
                {
                    img << 0 << " " << 0 << " " << 0 << "\n";
                }
            }
        }
    }

    img.close();
}
