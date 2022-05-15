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



unsigned char fps = 60;
double current_time, last_time;
const double dPI = 3.1415926535;
const int kNPoints = 5;
float g_angle = 0.5f;
int i = 0;
esat::Vec3 circle[kNPoints];

void DrawLinea(float x,float y, xemath::Vector2 centro){
    esat::DrawLine(x,y,centro.x + x,centro.y + y);
}

void InitCircle(){
	float angle = 6.28 / (float) kNPoints;  
	for (int i = 0; i < kNPoints; i++){
		circle[i].x = (float) cos(angle * i);
		circle[i].y = (float) sin(angle * i);
		circle[i].z = 1.0f;
	}
	
}

esat::Mat3 UpdateBaseFigure(){
	esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(200.0f,200.0f),m);
	m = esat::Mat3Multiply(esat::Mat3Translate(500.0f,500.0f),m);
	return m;
}

void CheckNewColision(esat::Vec2 circle[kNPoints]){
	//Puntos del jugador
	float j1X = (float) esat::MousePositionX();
    float j1Y = (float) esat::MousePositionY();

	//500 500 es el centro de la figura
    xemath::Vector2 centro = {(500-j1X), (500-j1Y)};
    centro = xemath::Vec2Normalize(centro);
    centro.x *=60;
    centro.y *=60;
	float j2X = centro.x + j1X;
	float j2Y = centro.y + j1Y;
	bool colision = false;

	esat::DrawSetStrokeColor(0,255,0);
	esat::DrawLine(circle[i].x,circle[i].y,circle[i+1].x,circle[i+1].y);

	esat::DrawSetStrokeColor(0,255,255);
	if(esat::IsKeyDown('Q')){
		if(i>=kNPoints){
			i=0;
		}else{
			i++;
		}
	}
	// for (int i = 0; i < kNPoints-1; ++i){
		printf("Punto de %d\n",i);
		printf("X-> %f Y-> %f\n",circle[i].x,circle[i].y);
		//Puntos del circulo
		float h1X = circle[i].x;
		float h1Y = circle[i].y;
		float h2X;
		float h2Y;
		if(i==(kNPoints-1)){
			h2X = circle[0].x;
			h2Y = circle[0].y;
		}else{
		 	h2X = circle[i+1].x;
		 	h2Y = circle[i+1].y;
		}

		//Vectores de las lineas
		xemath::Vector2 V = {(h2X-h1X),(h2Y-h1Y)}; 	//Horizontal
		xemath::Vector2 W = {(j1X-j2X),(j1Y-j2Y)};	//Vertical

		xemath::Mat3 T = { (V.x), (W.x), (j1X-h1X) };
		xemath::Mat3 S = { (V.y), (W.y), (j1Y-h1Y) };

		xemath::Mat3 resultado = xemath::Mat32x2Solver(T,S);

		if((resultado.x >= 0 && resultado.x <=1) && (resultado.y >= 0 && resultado.y <=1))esat::DrawSetStrokeColor(255,0,0);



	// }

	esat::DrawLine(j1X,j1Y,j2X,j2Y);



}

void DrawCircle(esat::Mat3 m){

	esat::Vec2 tr_circle[360];
	for (int i = 0; i < kNPoints; i++){
		esat::Vec3 temp = esat::Mat3TransformVec3(m,circle[i]);
		tr_circle[i] = {temp.x,temp.y};
	}

	esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&tr_circle[0].x,kNPoints);
	CheckNewColision(tr_circle);
	
}






int esat::main(int argc, char **argv) {
	srand(time(NULL));

	esat::WindowInit(900, 900);
	WindowSetMouseVisibility(true);
	InitCircle();
    float x;
    float y;


  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

		esat::DrawBegin();
		esat::DrawClear(0,0,0);	

        esat::Mat3 base = UpdateBaseFigure();

       
		DrawCircle(base);
        // esat::DrawLine(x,y,500.0f,500.0f);

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
