#pragma once
class Triangle
{
public:

    Triangle(float x1, float x2, float x3, float y1, float y2, float y3, int width, int height, int z1, int z2, int z3);

    int width;
    int height;

    float x1;
    float y1;
    float z1;
             
    float x2;
    float y2;
    float z2;
             
    float x3;
    float y3;
    float z3;

    float minx;
    float miny;
    float maxx;
    float maxy;
             
    int c1[3] = {255,0,0};
    int c2[3] = { 0,255,0 };
    int c3[3] = { 0,0,255 };

    int R, G, B;

    float L1;
    float L2;
    float L3;

    void can();
    void cut();
    bool condition(int &i, int &j);
    void Lambda(int& i, int& j);

private:
    float dx12;
    float dx23;
    float dx31;
    float dx32;
    float dx13;
    float dy12;
    float dy23;
    float dy31;
    float dy13;

    bool tl1;
    bool tl2;
    bool tl3;
};

