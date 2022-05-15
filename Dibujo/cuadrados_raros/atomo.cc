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
const int kNPoints = 32;
const int kNPoints_ovalo = 32;

esat::Vec3 points[kNPoints];
esat::Vec3 points_ovalo[kNPoints];

void InitCircle(){
    float angle = 6.28f/(float) kNPoints;
    for (int i = 0; i < kNPoints; i++){
        points[i].x = cos(angle*i);
        points[i].y = sin(angle*i);
        points[i].z = 1.0f;
    }

}
void InitOvalo(){
    float angle = 6.28f / (float) kNPoints_ovalo;
    for (int i = 0; i < kNPoints_ovalo; i++){
        points_ovalo[i].x = cos(angle*i);
        points_ovalo[i].y = sin(angle*i) * 0.5f;
        points_ovalo[i].z = 1.0f;
    }
}


esat::Mat3 UpdateBaseFigure(float scalate_x, float scalate_y,float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scalate_x, scalate_y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.0005f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}

esat::Mat3 UpdateDerivedFigure(esat::Mat3 base,float scale_x,float scale_y,float translate_x = 0.0f,float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(0.1f,0.4f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(cos(esat::Time()*0.001),sin(esat::Time()*0.001f)),m);
    // m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(base,m);
    return m;
}

void DrawFigure(esat::Mat3 base, int size, esat::Vec3 *points){
    esat::Vec2 tr_points[100];

    for (int i = 0; i < size; i++){
        esat::Vec3 tmp;
        tmp = esat::Mat3TransformVec3(base,points[i]);
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
    InitCircle();
    InitOvalo();
    esat::WindowInit(kWindowWidth, kWindowHeight);
    WindowSetMouseVisibility(true);


    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        esat::Mat3 base = UpdateBaseFigure(20.0f,20.0f);
        DrawFigure(base,kNPoints,points);
        // 15.0f, 3.75f

        float angle = 6.28f/3.0f;
        for (int i = 0; i < 3; i++){
            esat::Mat3 ovalo = UpdateBaseFigure(200.0f, 50.0f, angle * i);
            DrawFigure(ovalo, kNPoints, points);

            esat::Mat3 circulillo = UpdateDerivedFigure(ovalo, 0.07, 0.07, 1.0f, esat::Time() * 0.001f);
            DrawFigure(circulillo, kNPoints, points);
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