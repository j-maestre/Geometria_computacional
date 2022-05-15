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
const int kNPoints = 8;
esat::Vec3 circle[kNPoints*2];

//?  Formula->  T * S * P * Transformo * Point

void InitCircle(){
    float angle = 6.28f/kNPoints;

    for (int i = 0; i < kNPoints; i++){
        circle[i].x = cos(angle*i);
        circle[i+kNPoints].x = cos(angle*i);

        circle[i].y = sin(angle*i);
        circle[i+kNPoints].y = sin(angle*i);
        
        circle[i].z = 0.2f;
        circle[i+kNPoints].z = -0.2f;
    }
    
}


esat::Mat4 UpdateBaseFigure(float rotation,float height = 0.0f){
    esat::Mat4 m = esat::Mat4Identity();
    // m = esat::Mat4Multiply(esat::Mat4RotateX(esat::Time()*0.001f),m);


    // m = esat::Mat4Multiply(esat::Mat4Scale(1.0f,1.0f,3.0f),m);
    m = esat::Mat4Multiply(esat::Mat4RotateX(3.1415f/2.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(3.0f,0.0f,0.0f),m);
    m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time()*0.001f),m);
    m = esat::Mat4Multiply(esat::Mat4RotateY(rotation),m);

    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f,0.0f,7.0f),m); //Camara
    m = esat::Mat4Multiply(esat::Mat4Projection(),m);
    m = esat::Mat4Multiply(esat::Mat4Scale(250.0f,250.0f,1.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(400.0f,70.0f + (height + (height*0.7f)), 0.0f), m);
    return m;
}

void DrawFigure(esat::Mat4 base){
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);

    for (int i = 0; i < kNPoints; i++){
        
        esat::Vec3 cara1 = esat::Mat4TransformVec3(base,circle[i]);
        esat::Vec3 cara2 = esat::Mat4TransformVec3(base,circle[i+1]);
        
        esat::Vec3 fondo1 = esat::Mat4TransformVec3(base,circle[i+kNPoints]);
        esat::Vec3 fondo2 = esat::Mat4TransformVec3(base,circle[i+kNPoints+1]);

        if(i==kNPoints-1){
            cara2 = esat::Mat4TransformVec3(base, circle[0]);
            fondo2 = esat::Mat4TransformVec3(base, circle[kNPoints]);
        }

        esat::DrawLine(cara1.x,cara1.y,cara2.x,cara2.y);
        esat::DrawLine(fondo1.x,fondo1.y,fondo2.x,fondo2.y);
        
        esat::DrawLine(cara1.x,cara1.y,fondo1.x,fondo1.y);
        esat::DrawLine(cara2.x,cara2.y,fondo2.x,fondo2.y);
    }
    
}


int esat::main(int argc, char **argv){
    srand(time(NULL));

    esat::WindowInit(1000, 800);
    WindowSetMouseVisibility(true);

    InitCircle();


    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)){

        esat::DrawBegin();
        esat::DrawClear(0,0,0);

        for (int j = 0; j < 3; j++){

            for (int i = 0; i < 16; i++){
            
                esat::Mat4 base = UpdateBaseFigure(i * (6.28f/16),i*10.0f + (j*150));
                DrawFigure(base);
            }
        }

     


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
