#pragma once
#include "Vector3.h"
#include "ColorBuffer.h"
#include "Matrix4.h"
#include "Texture.h"
class Triangle
{
public:

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3, Vector3 t1, Vector3 t2, Vector3 t3);

    int width;
    int height;

    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    Vector3 dv1, dv2, dv3;

    Vector3 n1,n2,n3;
    Vector3 t1, t2, t3;

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


    bool isInsideTriangle(int &i, int &j);
    void Draw(int& i, int& j, ColorBuffer& buffer, Texture& texture);
    void Lambda(int& i, int& j);
    void SetView(Matrix4 obj2view, Matrix4 camera, Matrix4 m);
    void SetTranslation(Vector3 t);
    void SetRotation(Vector3 axis, float angle);
    void SetScale(Vector3 s);
    

    Matrix4 model;
private:
    void PixelCoords();
    void MinSpace();
    void CutColorRange();

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

