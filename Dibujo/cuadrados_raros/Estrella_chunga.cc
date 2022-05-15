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
const int kNPoints = 7;

esat::Vec3 points[kNPoints] = {
    {0.0f, 2.0f, 1.0f},
    {-5.0f, -8.0f, 1.0f},
    {-8.0f, -8.0f, 1.0f},
    {0.0f, 8.0f, 1.0f},
    {8.0f, -8.0f, 1.0f},
    {5.0f, -8.0f, 1.0f},
    {0.0f, 2.0f, 1.0f}
};

void Normalize(float xMax, float yMax){
    for (int i = 0; i < kNPoints; i++){
        points[i].x /= xMax;
        points[i].y /= yMax;
    }
    
}

esat::Mat3 UpdateTriangle(float scale,float translate_x,float translate_y,float angle,bool inside = false){
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(scale,scale),m);
    if(inside) m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate_x, translate_y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);
    return m;
}


void DrawFigura(esat::Mat3 m, esat::Vec3 *points){//*Points es un array, y aunque le diga que es un puntero puedo usarlo como si fuera un array en sintaxy
    esat::Vec2 tr_points[100];
    for (int i = 0; i < kNPoints; i++){
        esat::Vec3 tmp = esat::Mat3TransformVec3(m,points[i]);
        tr_points[i] = {tmp.x,tmp.y};
    }
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawPath(&tr_points[0].x,kNPoints);
    
}



int esat::main(int argc, char **argv)
{
    srand(time(nullptr));
    double current_time = 0.0;
    double last_time = 0.0;
    double fps = 60.0;
    esat::WindowInit(kWindowWidth, kWindowHeight);
    Normalize(8.0f,8.0f);
    WindowSetMouseVisibility(true);

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        //? 12 triangulillos en total
        for (int i = 0; i < 12; i++){
            esat::Mat3 base = UpdateTriangle(50.0f,0.0f,180.0f,(6.28f/12.0f)*i );
            DrawFigura(base,points);
            /* code */
        }
        for (int i = 0; i < 6; i++){
            esat::Mat3 base = UpdateTriangle(30.0f,0.0f,70.0f,(6.28f/6.0f)*i,true);
            DrawFigura(base,points);
            /* code */
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