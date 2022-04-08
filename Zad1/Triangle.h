#pragma once
#include "Vector3.h"
#include "ColorBuffer.h"
class Triangle
{
public:

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 c1, Vector3 c2, Vector3 c3, int width, int height);

    int width;
    int height;

    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    Vector3 colorV1;
    Vector3 colorV2;
    Vector3 colorV3;

    float minx;
    float miny;
    float maxx;
    float maxy;
             
    int R, G, B;

    float L1;
    float L2;
    float L3;

    void PixelCoords();
    void MinSpace();
    bool isInsideTriangle(int &i, int &j);
    void Draw(int& i, int& j, ColorBuffer& buffer);
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

