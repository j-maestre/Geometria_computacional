#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "xemath.cc"

unsigned char fps=60;
double current_time,last_time;
int kNPoints = 10;
float circulo[10];
esat::Vec3 circle[10];
float g_angle = 0.5f;
// esat::Vec3 g_circle[kNPoints];
// esat::Vec3 circulo[kNPoints];

void InitCircle(){
    float angle = (3.1415f*2) / (float) kNPoints;
    for(int i = 0; i<kNPoints; i++){
        
        if(i%2 == 0){
            circle[i].x = (float) cos(angle * i) * 0.5f;
            circle[i].y = (float) sin(angle * i) * 0.5f;
        }else{
            circle[i].y = (float) sin(angle * i);
            circle[i].x = (float) cos(angle * i);
        }
        circle[i].z = 1.0f;
        // circulo[i*2] = (float) cos(angle * i);
        // circulo[i*2+1] = (float) sin(angle * i);
     }
}

void DrawFigure(esat::Mat3 m){
    esat::Vec2 tr_circle[10];
    for (int i = 0; i < kNPoints; i++){
        esat::Vec3 tmp = esat::Mat3TransformVec3(m,circle[i]);
        tr_circle[i] = { tmp.x, tmp.y };
    }
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0);
    esat::DrawSolidPath(&tr_circle[0].x,kNPoints);
}

esat::Mat3 UpdateBaseFigure(){
    g_angle +=0.02f;
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(100.0f,100.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(g_angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(0.0f,0.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate((float) esat::MousePositionX(),(float) esat::MousePositionY()),m);
    return m;
}

esat::Mat3 UpdateDerivedFigure(esat::Mat3 base, float speed){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(0.5f,0.5f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001f*speed),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(3.0f,0.0f),m);
    m = esat::Mat3Multiply(base,m);
    return m;
}


int esat::main(int argc, char **argv) {


	esat::WindowInit(900,900);
	WindowSetMouseVisibility(true);
	srand(time(NULL));
    InitCircle();


  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time();
    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);

        esat::Mat3 base = UpdateBaseFigure();
        DrawFigure(base);

        esat::Mat3 derived = UpdateDerivedFigure(base,1.5f);
        DrawFigure(derived);

        esat::Mat3 derived2 = UpdateDerivedFigure(derived,1.7f);
        DrawFigure(derived2);
        // esat::MAt3 derived = UpdateDerivedFigure(base);
        // DrawFigure(derived);

    	esat::DrawEnd();

    	//Control fps
    	do{
    		current_time = esat::Time();
    	}while((current_time-last_time)<=1000.0/fps);
    	esat::WindowFrame();
  }


  esat::WindowDestroy();

  return 0;

}
