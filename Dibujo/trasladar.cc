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
int kNPoints = 4;
esat::Vec3 g_circle[kNPoints];

void DrawFigure(esat::Mat3 m){
    esat::Vec2 tr_circle[kNPoints];
    for (int i = 0; i < kNPoints; i++){
        /* code */esat::Vec3 tmp = esat::Mat3TransformVec3(m,g_circle[i]);
        tr_circle[i] = { tmp.x, tmp.y };
    }
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0);
    esat::DrawSolidPath(&tr_circle[0].x,kNPoints);
}

esat::Mat3 UpdateBaseFigure(){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(100.0f,100.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(0.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(400.0f,300.0f),m);
    return m;
}


int esat::main(int argc, char **argv) {


	esat::WindowInit(900,900);
	WindowSetMouseVisibility(true);
	srand(time(NULL));

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time();
    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);

        esat::Mat3 base = UpdateBaseFigure();
        DrawFigure(base)
        esat::MAt3 derived = UpdateDerivedFigure(base);
        DrawFigure(derived);





        // Createcircle(esat::MousePositionX(),esat::MousePositionY(),100,Rojo,1,1,16,2,0.6);
        // Createcircle(esat::MousePositionX(),esat::MousePositionY(),80,Rojo,1,1,16,2,0.6);

        esat::DrawSolidPath(pointsNormalized,7);

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
