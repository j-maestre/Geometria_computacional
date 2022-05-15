#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned char fps = 60;
double current_time, last_time;
const double dPI = 3.141592653589793238462643383279502884197169;
const int kNPoints = 4;
esat::Vec3 circle[kNPoints];

//?  Formula->  T * S * P * Transformo * Point

esat::Vec3 puntos1[4] = {
    {-1,-1,1},
    {1,-1,1},
    {1,1,1},
    {-1,1,1},
};
esat::Vec3 puntos2[4] = {
    {-1,-1,-1},
    {1,-1,-1},
    {1,1,-1},
    {-1,1,-1},
};

esat::Vec3 triangle[20];

void InitTriangle(){
    float angle = 6.28f/10.0f;

    for (int i = 0; i < 10; i++){
        triangle[i].x = cos(angle*i);
        triangle[i+10].x = cos(angle*i);

        triangle[i].y = sin(angle*i);
        triangle[i+10].y = sin(angle*i);

        triangle[i].z = 0.2f;
        triangle[i+10].z = -0.2f;

        if(i%2!=0){
            triangle[i].x *= 0.4f;
            triangle[i+10].x *= 0.4f;

            triangle[i].y *= 0.4f;
            triangle[i+10].y *= 0.4f;
        }
    }
    
}


esat::Mat4 UpdateBaseFigure(){
    esat::Mat4 m = esat::Mat4Identity();

    m = esat::Mat4Multiply(esat::Mat4RotateX(esat::Time()*0.001 ),m);
    m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time()*0.001 ),m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ(esat::Time()*0.001 ),m);

    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f,0.0f,4.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Projection(),m);
    m = esat::Mat4Multiply(esat::Mat4Scale(100.0f,100.0f,1.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(esat::MousePositionX(),esat::MousePositionY(),0.0f),m);
    return m;
}

void DrawCube(esat::Mat4 base){
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    for (int i = 0; i < kNPoints; i++){
        esat::Vec3 cara1 = esat::Mat4TransformVec3(base,puntos1[i]);
        esat::Vec3 cara2 = esat::Mat4TransformVec3(base,puntos1[i+1]);
        
        esat::Vec3 fondo1 = esat::Mat4TransformVec3(base,puntos2[i]);
        esat::Vec3 fondo2 = esat::Mat4TransformVec3(base,puntos2[i+1]);


        if(i==kNPoints-1){
            cara2 = esat::Mat4TransformVec3(base,puntos1[0]);
            fondo2 = esat::Mat4TransformVec3(base,puntos2[0]);
        }


        esat::DrawLine(cara1.x,cara1.y,cara2.x,cara2.y);
        esat::DrawLine(fondo1.x,fondo1.y,fondo2.x,fondo2.y);

        esat::DrawLine(cara1.x,cara1.y,fondo1.x,fondo1.y);
        esat::DrawLine(cara2.x,cara2.y,fondo2.x,fondo2.y);
    }
    
}


void DrawTriangle(esat::Mat4 base, int size){
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);

    for (int i = 0; i < size; i++){
        
        esat::Vec3 cara1 = esat::Mat4TransformVec3(base,triangle[i]);
        esat::Vec3 cara2 = esat::Mat4TransformVec3(base,triangle[i+1]);
        
        esat::Vec3 fondo1 = esat::Mat4TransformVec3(base,triangle[i+10]);
        esat::Vec3 fondo2 = esat::Mat4TransformVec3(base,triangle[i+11]);

        if(i==size-1){
            cara2 = esat::Mat4TransformVec3(base, triangle[0]);
            fondo2 = esat::Mat4TransformVec3(base, triangle[10]);
        }


        esat::DrawLine(cara1.x,cara1.y,cara2.x,cara2.y);
        esat::DrawLine(fondo1.x, fondo1.y, fondo2.x, fondo2.y);

        esat::DrawLine(cara1.x,cara1.y,fondo1.x,fondo1.y);
        esat::DrawLine(cara2.x,cara2.y,fondo2.x,fondo2.y);
    }
    
}


esat::Mat4 UpdateTrianglefigure(){
    esat::Mat4 m = esat::Mat4Identity();
    m = esat::Mat4Multiply(esat::Mat4RotateX(esat::Time()*0.001f),m);
    m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time()*0.001f),m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ(esat::Time()*0.001f),m);
    

    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f,0.0f,4.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Projection(),m);
    m = esat::Mat4Multiply(esat::Mat4Scale(300.0f,300.0f,1.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(esat::MousePositionX(), esat::MousePositionY(), 0.0f), m);

    return m;
}

int esat::main(int argc, char **argv){
    srand(time(NULL));

    esat::WindowInit(700, 700);
    WindowSetMouseVisibility(true);

    InitTriangle();


    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)){

        esat::DrawBegin();
        esat::DrawClear(0,0,0);

        // esat::Mat4 base = UpdateBaseFigure();
        // DrawCube(base);

        esat::Mat4 star = UpdateTrianglefigure();
        DrawTriangle(star,10);

     


		esat::DrawEnd();

		//Control FPS
		do {
        current_time = esat::Time();
		} while ((current_time - last_time) <= 1000.0 / fps);

		esat::WindowFrame();
    }

    esat::WindowDestroy();

    return 0;
}
