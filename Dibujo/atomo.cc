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
int kNPoints = 360;
esat::Vec3 circle[360];
esat::Vec3 miniCircle[360];
float g_angle = 0.5f;

void InitCircle(){
    float angle = (3.1415f*2) / (float) kNPoints;
    for(int i = 0; i<kNPoints; i++){
        circle[i].x = ((float) cos(angle * i) * 0.5f) * 0.3f;
        circle[i].y = (float) sin(angle * i) * 0.5f;
        circle[i].z = 1.0f;
     }
}

void InitMiniCircle(){
    float angle = (3.1415f*2) / (float) kNPoints;
    for(int i = 0; i<kNPoints; i++){
        miniCircle[i].x = ((float) cos(angle * i));
        miniCircle[i].y = (float) sin(angle * i);
        miniCircle[i].z = 1.0f;
     }
}

void DrawFigure(esat::Mat3 m, esat::Vec3 circle[360]){
    esat::Vec2 tr_circle[360];
    for (int i = 0; i < kNPoints; i++){
        esat::Vec3 tmp = esat::Mat3TransformVec3(m,circle[i]);
        tr_circle[i] = { tmp.x, tmp.y };
    }
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&tr_circle[0].x,kNPoints);
}

esat::Mat3 UpdateBaseFigure(){
    g_angle +=0.02f;
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(200.0f,200.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(g_angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(0.0f,0.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate((float) esat::MousePositionX(),(float) esat::MousePositionY()),m);
    return m;
}

esat::Mat3 UpdateCircleAchatao(esat::Mat3 base,float excentricidad ,float speed){

    esat::Mat3 m;
    m = esat::Mat3Multiply(esat::Mat3Scale(100.0f,100.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.005 * speed),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(15.0f,15.0f),m);
    m = esat::Mat3Multiply(base,m);

    return m;
}

esat::Mat3 UpdateDerivedFigure(esat::Mat3 base, float rotation){
    esat::Mat3 m = esat::Mat3Identity();
    // m = esat::Mat3Multiply(esat::Mat3Scale(0.5f,0.5f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(rotation),m);
    // m = esat::Mat3Multiply(esat::Mat3Translate(3.0f,0.0f),m);
    m = esat::Mat3Multiply(base,m);
    return m;
}


int esat::main(int argc, char **argv) {


	esat::WindowInit(900,900);
	WindowSetMouseVisibility(true);
	srand(time(NULL));
    InitCircle();
    InitMiniCircle();


  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time();
    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);

        esat::Mat3 base = UpdateBaseFigure();
        DrawFigure(base,circle);

        for (size_t i = 0; i < 3; i++){
            esat::Mat3 derived = UpdateDerivedFigure(base,(i*10));
            DrawFigure(derived,circle);
            DrawFigure(derived,miniCircle);
            

        }
        

        

        // esat::Mat3 derivedGrande = UpdateCircleAchatao(base,10,2);
        // DrawFigure(derivedGrande);
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
