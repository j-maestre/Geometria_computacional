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
float radio = 30.0f;


struct TColor{
  int r = 255;
  int g = 255;
  int b = 255;
  int a = 0;
};
TColor Rojo = {180,0,0};
const double dPI = 3.141592653589793238462643383279502884197169;



// void Createcircle(float x, float y, float radio, TColor color,float excentricidadX = 1.0f,float excentricidadY = 1.0f, int points = 360, int extravagancia = -1, float peculiaridad = -1.0f){
//     //Iniciar circulo
//     float *circulo = (float*) malloc(sizeof(float)*(points * 2));
//     float angle = (dPI*2) / (float) points;
//     for(int i = 0; i<points; i++){
//         if(extravagancia ==-1){
//             *(circulo + (i * 2)) = (float) cos(angle * i) * excentricidadX;
//             *(circulo + (i * 2 +1)) = (float) sin(angle * i) * excentricidadY;
//         }else{
//             //Cirulo raro
//             if(i%extravagancia == 0){
//                 *(circulo + (i * 2)) = ((float) cos(angle * i) * excentricidadX) * peculiaridad;
//                 *(circulo + (i * 2 +1)) = ((float) sin(angle * i) * excentricidadY) * peculiaridad;
//             }else{
//                 *(circulo + (i * 2)) = (float) cos(angle * i) * excentricidadX;
//                 *(circulo + (i * 2 +1)) = (float) sin(angle * i) * excentricidadY;
//             }
//         }
//     }
//     //Pintar circulo
//     esat::DrawSetStrokeColor(color.r,color.g,color.b);
//     esat::DrawSetFillColor(color.r,color.g,color.b,0);
//     float *circleToDraw = (float*) malloc(sizeof(float)*(points*2));
//     for(int i = 0; i<points; i++){
//         *(circleToDraw + (i * 2)) = *(circulo + (i * 2)) * radio + x;
//         *(circleToDraw + (i * 2 + 1)) = *(circulo + (i * 2 + 1)) * radio + y;
//     }
//     esat::DrawSolidPath(circleToDraw,points);
//     free(circulo);
//     free(circleToDraw);
// }

xemath::Vector3 puntos[7]={
    {0.0f, 2.0f,1.0f},
    {-5.0f, -8.0f,1.0f},
    {-8.0f,-8.0f,1.0f},
    {0.0f,8.0f,1.0f},
    {8.0f,-8.0f,1.0f},
    {5.0f,-8.0f,1.0f},
    {0.0f,2.0f,1.0f},
};
// float points[14] = {
//     0.0f, 2.0f,
//     -5.0f, -8.0f,
//     -8.0f,-8.0f,
//     0.0f,8.0f,
//     8.0f,-8.0f,
//     5.0f,-8.0f,
//     0.0f,2.0f
// };

float pointsNormalized[14];

void Normalize(){
    float reciprocal = 1.0f / 8.0f;
    for(int i = 0; i < 7; ++i) {
        puntos[i].x *= reciprocal;
        puntos[i].y *= reciprocal;
        puntos[i].z *= reciprocal;
    }

}

void DrawUpdate(){
    esat::Mat3 m = esat::Mat3Identity();
    
}













int esat::main(int argc, char **argv) {


	esat::WindowInit(900,900);
	WindowSetMouseVisibility(true);
	srand(time(NULL));

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time();
    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);
        Normalize();



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
