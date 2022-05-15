#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"

const unsigned int kWindowWidth = 1200;
const unsigned int kWindowHeight = 800;
const int kNPoints = 16;
const int kNPointsTriangle = 3;
float dPi = 3.141592f;

esat::Vec3 trident[16] = {
    {2.0f, 0.0f, 1.0f},
    {3.0f, 0.0f, 1.0f},
    {3.0f, 4.0f, 1.0f},
    {5.0f, 4.0f, 1.0f},
    {5.0f, 8.0f, 1.0f},
    {4.0f, 8.0f, 1.0f},
    {4.0f, 6.0f, 1.0f},
    {3.0f, 6.0f, 1.0f},
    {3.0f, 13.0f, 1.0f},
    {2.0f, 13.0f, 1.0f},
    {2.0f, 6.0f, 1.0f},
    {1.0f, 6.0f, 1.0f},
    {1.0f, 8.0f, 1.0f},
    {0.0f, 8.0f, 1.0f},
    {0.0f, 4.0f, 1.0f},
    {2.0f, 4.0f, 1.0f}};

esat::Vec3 triangle[kNPointsTriangle] = {
    {-1.0f, 0.0f,1.0f},
    {0.0f, 1.0f,1.0f},
    {1.0f, 0.0f,1.0f}};
    // {0.0f, 3.0f,1.0f}};

void NormalizeTrident(){
    for (int i = 0; i < kNPoints; i++){
        trident[i].x /= 5.0f;
        trident[i].y /= 13.0f;
    }
    
}
void NormalizeTriangle(){
    for (int i = 0; i < kNPointsTriangle; i++){
        // triangle[i].x /= 5.0f;
        triangle[i].y /= 3.0f;
    }
    
}

esat::Mat3 UpdateFigure(float scale_x,float scale_y, float trans_x, float trans_y, float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity(); 
    m = esat::Mat3Multiply(esat::Mat3Scale(scale_x,scale_y),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(-35.0f,0.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(trans_x,trans_y),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}
esat::Mat3 UpdateTriangle(float scale_x,float scale_y, float trans_x, float trans_y, float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity(); 
    m = esat::Mat3Multiply(esat::Mat3Scale(scale_x,scale_y),m);
    // m = esat::Mat3Multiply(esat::Mat3Rotate(6.28 / 4.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(trans_x,trans_y),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}

void DrawFigure(esat::Mat3 m, int size, esat::Vec3 *points){
    esat::Vec2 tr_points[100];

    for (int i = 0; i < size; i++){
        esat::Vec3 tmp;
        tmp = esat::Mat3TransformVec3(m,points[i]);
        tr_points[i] = {tmp.x,tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&tr_points[0].x,size);

}

int esat::main(int argc, char **argv)
{
    srand(time(nullptr));
    double current_time = 0.0;
    double last_time = 0.0;
    double fps = 60.0;
    NormalizeTrident();
    // NormalizeTriangle();

    esat::WindowInit(kWindowWidth, kWindowHeight);
    WindowSetMouseVisibility(true);

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        for (int i = 0; i < 6; i++){
            /* code */
        
            esat::Mat3 base = UpdateFigure(75.0f,150.0f,0.0f,100.0f, 6.28f/6 * i);
            DrawFigure(base,kNPoints,trident);
            esat::Mat3 triangleBase = UpdateTriangle(10.0f,30.0f,-28.0f,192.0f,6.28f/6 * i);
            DrawFigure(triangleBase,kNPointsTriangle,triangle);
            esat::Mat3 triangleBase2 = UpdateTriangle(10.0f,30.0f,32.0f,192.0f,6.28f/6.0f * i);
            DrawFigure(triangleBase2,kNPointsTriangle,triangle);

        }
            esat::DrawEnd();
            esat::WindowFrame();

        do
        {
            current_time = esat::Time();
        } while ((current_time - last_time) <= 1000.0 / fps);
    }
    esat::WindowDestroy();
    return 0;
}