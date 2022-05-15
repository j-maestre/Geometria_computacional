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
const int kNPoints = 9;
const int kNPointsOctogono = 8;
float dPi = 3.141592f;

esat::Vec3 figure[kNPoints] = {
    {1.0f, 0.0f,1.0f},
    {1.0f, 3.0f,1.0f},
    {3.0f, 7.0f,1.0f},
    {1.0f, 7.0f,1.0f},
    {0.0f, 5.0f,1.0f},
    {-1.0f, 7.0f,1.0f},
    {-3.0f, 7.0f,1.0f},
    {-1.0f, 3.0f,1.0f},
    {-1.0f, 0.0f,1.0f}};

esat::Vec3 octogono[kNPointsOctogono];

void InitOctogono(){
    float angle = 6.28f/kNPointsOctogono;
    for (int i = 0; i < kNPointsOctogono; i++){
        octogono[i].x = cos(angle*i);
        octogono[i].y = sin(angle*i);
        octogono[i].z = 1.0f;
    }
    
}


esat::Mat3 UpdateOctogonoFigure(float scale){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale,scale),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}
esat::Mat3 UpdateBaseFigure(float scale,float trans_x,float trans_y,float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale,scale),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(trans_x,trans_y),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}

void DrawFigure(esat::Mat3 base,int size, esat::Vec3 *points){
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
    InitOctogono();

    esat::WindowInit(kWindowWidth, kWindowHeight);
    WindowSetMouseVisibility(true);

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        esat::Mat3 octogonoFigure = UpdateOctogonoFigure(150.0f);
        DrawFigure(octogonoFigure,kNPointsOctogono,octogono);
        for (int i = 0; i < kNPointsOctogono; i++){
        
            esat::Mat3 base = UpdateBaseFigure(20.0f,0.0f,150.0f,6.28f/8.0f *i);
            DrawFigure(base,kNPoints,figure);
            esat::Mat3 baseinterior = UpdateBaseFigure(10.0f,0.0f,0.0f,6.28f/8.0f *i);
            DrawFigure(baseinterior,kNPoints,figure);


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