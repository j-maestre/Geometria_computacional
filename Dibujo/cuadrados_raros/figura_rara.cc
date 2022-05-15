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
const int kNPoints = 4;
const int kNPointsSquare = 5;
const int kNPointsHexagon = 6;
float dPi = 3.141592f;

esat::Vec3 arrow[kNPoints] = {
    {0.0f, 1.0f,1.0f},
    {1.0f, 0.0f,1.0f},
    {0.0f, -3.0f,1.0f},
    {-1.0f, 0.0f,1.0f}
};

esat::Vec3 square[kNPointsSquare] = {
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {-1.0f, -1.0f,1.0f}
};

esat::Vec3 hexagon[kNPointsHexagon];

void InitHexagon(){
    float angle = 6.28f / (float) kNPointsHexagon;

    for (int i = 0; i < kNPointsHexagon; i++){
        hexagon[i].x = cos(i*angle);
        hexagon[i].y = sin(i*angle);
        hexagon[i].z = 1.0f;
    }
    
}

void DrawFigure(esat::Mat3 base,int size, esat::Vec3 *figure){
    esat::Vec2 tr_points[100];

    for (int i = 0; i < size; i++){
        esat::Vec3 tmp;
        tmp = esat::Mat3TransformVec3(base,figure[i]);
        tr_points[i] = {tmp.x,tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&tr_points[0].x,size);
    
}

esat::Mat3 UpdateHexagon(float scale_x,float scale_y){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale_x,scale_y),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.0005),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}
esat::Mat3 UpdateFigure(float scale_x,float scale_y,float trans_x,float trans_y,float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale_x,scale_y),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(trans_x, trans_y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}
esat::Mat3 UpdateCornerFigure(float scale_x,float scale_y,float trans_x,float trans_y,float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale_x,scale_y),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(6.28f/4.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(6.28f/2.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(trans_x, trans_y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    // m = esat::Mat3Multiply(esat::Mat3Rotate(6.28f/4.0f),m);
    // m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);
    return m;
}


esat::Mat3 UpdateDerivedFigure(esat::Mat3 base,esat::Mat3 derived){
    esat::Mat3 m = esat::Mat3Multiply(base,derived);
    return m;
}



int esat::main(int argc, char **argv){
    srand(time(nullptr));
    double current_time = 0.0;
    double last_time = 0.0;
    double fps = 60.0;
    InitHexagon();
    esat::WindowInit(kWindowWidth, kWindowHeight);
    WindowSetMouseVisibility(true);

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        esat::Mat3 hexa = UpdateHexagon(70.0f, 70.0f);
        DrawFigure(hexa, kNPointsHexagon, hexagon);
        
        esat::Mat3 cuadrado = UpdateHexagon(70.0f, 70.0f);
        DrawFigure(cuadrado, kNPointsSquare, square);
        

        for (int j = 0; j < 4; j++){
            // esat::Mat3 corner = UpdateCornerFigure(20.0f,40.0f,-180.0f,0.0f, ((6.28/4.0f * (float) j)) + ((6.28/4.0f) * 0.5f) );
            esat::Mat3 corner = UpdateCornerFigure(0.3f,0.5f,-3.0f,0.0f, ((6.28/4.0f * (float) j)) + ((6.28/4.0f) * 0.5f) );
            corner = UpdateDerivedFigure(hexa,corner);
            DrawFigure(corner,kNPoints,arrow);
            
            for (int i = 0; i < 5; i++){
                esat::Mat3 base = UpdateFigure(10.0f,10.0f,(i*25) - 50.0f,130.0f,(6.28/4.0f * (float) j));
                DrawFigure(base,kNPoints,arrow);
                esat::Mat3 rectangulo = UpdateFigure(10.0f,20.0f,(i*25) - 50.0f,170.0f,(6.28/4.0f * (float) j));
                DrawFigure(rectangulo, kNPointsSquare, square);
            }
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