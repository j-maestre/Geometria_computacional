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
float dPi = 3.141592f;

esat::Vec3 points[kNPoints] = {
    {0.0f, 0.0f,1.0f},
    {0.0f, 0.75f,1.0f},
    {0.125f, 1.0f,1.0f},
    {0.25f, 0.75f,1.0f},
    {0.25f, 0.0f,1.0f},
};

esat::Mat3 UpdateBaseFigure(float scale, float pos_x,float pos_y, float angle,bool inverted = false){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -0.5f), m);
    m = esat::Mat3Multiply(esat::Mat3Scale(scale,scale),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(pos_x,pos_y),m);

    if(inverted){
        m = esat::Mat3Multiply(esat::Mat3Rotate(dPi), m);
    }else{

    }

    // if(inverted){
    //     m = esat::Mat3Multiply(esat::Mat3Rotate(dPi), m);
    //     m = esat::Mat3Multiply(esat::Mat3Translate(pos_x,pos_y),m);
    // }else{
    //     m = esat::Mat3Multiply(esat::Mat3Translate(pos_x/2, pos_y/2), m);
    // };

    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);

    return m;
}

void DrawFigure(esat::Mat3 m,int size, esat::Vec3 *points){

    esat::Vec2 tr_points[100];
    for (int i = 0; i < size; i++){
        
        esat::Vec3 tmp = esat::Mat3TransformVec3(m,points[i]);
        tr_points[i] = {tmp.x,tmp.y};
    }
    
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&tr_points[0].x,size);
}






int esat::main(int argc, char **argv){
    srand(time(nullptr));
    double current_time = 0.0;
    double last_time = 0.0;
    double fps = 60.0;
    esat::WindowInit(kWindowWidth, kWindowHeight);
    // Normalize(8.0f,8.0f);
    WindowSetMouseVisibility(true);

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        for (size_t i = 0; i < 8; i++){
            //scale, x , y , angle
            esat::Mat3 base;
            if(i%2!=0){
                base = UpdateBaseFigure(100.0f,0.0f,350.0f,(dPi*2/8) * i);
            }else{
                base = UpdateBaseFigure(100.0f,0.0f,350.0f,(dPi*2/8) * i,true);
            }
            DrawFigure(base,kNPoints,points);
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