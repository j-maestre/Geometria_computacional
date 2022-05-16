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
const int kNPoints = 5;
const int kNPointsStar = 10;
float dPi = 3.141592f;

esat::Vec3 circle[kNPoints];
esat::Vec3 star[kNPointsStar*2];
    
void InitStar(){
    float angle = 6.28f/ (float) kNPointsStar;
    for (int i = 0; i < kNPointsStar; i++){
        star[i].x = cos(angle*i);
        star[i].y = sin(angle*i);
        star[i].z = 0.2f;
        
        star[i + kNPointsStar].x = cos(angle*i);
        star[i + kNPointsStar].y = sin(angle * i);
        star[i + kNPointsStar].z = -0.2f;

        if(i%2!=0){
            star[i].x *= 0.5f;
            star[i].y *= 0.5f;

            star[i + kNPointsStar].x *= 0.5f;
            star[i + kNPointsStar].y *= 0.5f;
        }
    }
    
}

void InitCircle(){
    float angle = 6.28f/(float)kNPoints;

    for (int i = 0; i < kNPoints; i++){
        circle[i].x = cos(angle*i);
        circle[i].y = sin(angle*i);
        circle[i].z = 1.0f;
    }
    
}

esat::Mat3 UpdateFigure(float scale,float translate_x,float translate_y,float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();

    // m = esat::Mat3Multiply(esat::Mat3Scale(scale,scale),m);
    m = esat::Mat3Multiply(esat::Mat3Scale(sin(esat::Time() * 0.001f) * 100.0f, sin(esat::Time() * 0.001f) * 100.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate_x,translate_y),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.002f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),esat::MousePositionY()),m);

    return m;
}

esat::Mat3 UpdateDerivedFigure(esat::Mat3 base,float scale, float translate_x, float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale,scale),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate_x,0.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001f),m);
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


esat::Mat4 Update3DFigure(float scale,float angle){
    esat::Mat4 m = esat::Mat4Identity();
    m = esat::Mat4Multiply(esat::Mat4RotateZ(-(3.1415f/2.0f)),m);
    m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time()*0.001f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f,0.0f,4.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Projection(),m);
    m = esat::Mat4Multiply(esat::Mat4Scale(200.0f,200.0f,1.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(esat::MousePositionX(), esat::MousePositionY(),0.0f), m);
    return m;
}

void Draw3DFigure(esat::Mat4 base, int size, esat::Vec3 *points){
    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0, 0);

    for (int i = 0; i < size; i++){
        esat::Vec3 cara1 = esat::Mat4TransformVec3(base,points[i]); 
        esat::Vec3 cara2 = esat::Mat4TransformVec3(base,points[i+1]); 
        
        esat::Vec3 fondo1 = esat::Mat4TransformVec3(base,points[i+size]); 
        esat::Vec3 fondo2 = esat::Mat4TransformVec3(base,points[i+size+1]);


        if(i==(size-1)){
            cara2 = esat::Mat4TransformVec3(base, points[0]);
            fondo2 = esat::Mat4TransformVec3(base, points[size]);
        } 

        esat::DrawLine(cara1.x,cara1.y,cara2.x,cara2.y);
        esat::DrawLine(fondo1.x,fondo1.y,fondo2.x,fondo2.y);
        
        esat::DrawLine(cara1.x,cara1.y,fondo1.x,fondo1.y);
        esat::DrawLine(cara2.x,cara2.y,fondo2.x,fondo2.y);

    }
    
}


int esat::main(int argc, char **argv)
{
    srand(time(nullptr));
    double current_time = 0.0;
    double last_time = 0.0;
    double fps = 60.0;
    InitCircle();
    InitStar();

    esat::WindowInit(kWindowWidth, kWindowHeight);
    WindowSetMouseVisibility(true);

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        esat::Mat4 cube = Update3DFigure(0.0f,0.0f);
        Draw3DFigure(cube,kNPointsStar,star);


        esat::Mat3 base = UpdateFigure(100.0f,150.0f,0.0f,-(3.1415f/2.0f));
        DrawFigure(base,kNPoints,circle);

        float angle = 6.28f/(float)kNPoints;
        for (int i = 0; i <kNPoints; i++){
        
            esat::Mat3 derived = UpdateDerivedFigure(base,0.5f,1.5f,angle*i);
            DrawFigure(derived,kNPoints,circle);
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