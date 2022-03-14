#include <iostream>
#include <fstream>

void can(float &x, float &y, int width, int height) {
    x = (x + 1) * width * 0.5f;
    y = (y + 1) * height * 0.5f;
}

int main()
{
    int width = 200;
    int height = 200;
    int r = 255;
    int g = 50;
    int b = 0;

    std::ofstream img;
    img.open("image.ppm");

    float x1 = 0.7f;
    float y1 = 0.7f;

    float x2 = 0.5f;
    float y2 = -0.9f;

    float x3 = -0.9f;
    float y3 = 0.9f;

    can(x1, y1, width, height);
    can(x2, y2, width, height);
    can(x3, y3, width, height);

    std::cout << x1 << " " << y1 <<"\n";
    std::cout << x2 << " " << y2 << "\n";
    std::cout << x3 << " " << y3 << "\n";

    if (img.is_open()) {
        img << "P3\n";
        img << width<<" "<<height<< "\n";
        img << "255\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
               if((((x1 - x2) * (i - y1) - (y1 - y2) * (j - x1))> 0) && 
                   (((x2 - x3) * (i - y2) - (y2 - y3) * (j - x2)) > 0) &&
                   (((x3 - x1) * (i - y3) - (y3 - y1) * (j - x3)) > 0))
               {
                   img << r << " " << g << " " << b << "\n";
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
