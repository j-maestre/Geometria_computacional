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
// #include "xemath.cc"

unsigned char fps=60;
double current_time,last_time;
int kNPoints = 10;
float circulo[10];
esat::Vec3 circle[10];
float g_angle = 0.5f;
// esat::Vec3 g_circle[kNPoints];
// esat::Vec3 circulo[kNPoints];

const int kNCircle = 6;
esat::Vec3 g_circle[kNCircle];
const int kNCuadrado = 4;
esat::Vec3 g_cuadrado[kNCuadrado];


void InitCircle(){
    float angle = (3.1415f*2) / (float) kNCircle;

    for (int i = 0; i < kNCircle; i++){
        g_circle[i].x = (float) cos(i * angle);
        g_circle[i].y = (float) sin(i * angle);
        g_circle[i].z = 1.0f;
    }
}
void InitCuadrado(){
    float angle = (3.1415f*2) / (float) kNCuadrado;

    for (int i = 0; i < kNCuadrado; i++){
        g_cuadrado[i].x = (float) cos(i * angle);
        g_cuadrado[i].y = (float) sin(i * angle);
        g_cuadrado[i].z = 1.0f;
    }
}


const int kNArrowPoints = 4;
esat::Vec3 g_arrow[kNArrowPoints] = {
  0.0f, 1.0f, 1.0f,
  1.0f, 0.0f, 1.0f,
  0.0f, -3.0f, 1.0f,
  -1.0f, 0.0f, 1.0f,
};

const int kNSquarePoints = 4;
esat::Vec3 g_square[kNSquarePoints] = {
    -1.0f,
    -1.0f,
    1.0f,
    1.0f,
    -1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    -1.0f,
    1.0f,
    1.0f,
};

void DrawFigure(const int n_points, esat::Mat3 m, esat::Vec3* points){
    esat::Vec2 tr_points[100]; //100 por ejemplo

    for (int i = 0; i < n_points; i++){
        esat::Vec3 tmp = esat::Mat3TransformVec3(m,points[i]);
        tr_points[i] = { tmp.x,tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0);
    esat::DrawSolidPath(&tr_points[0].x,n_points);
    
}

esat::Mat3 UpdateCornerArrow(float angle){
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Rotate(3.14f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(0.0f,7.5f),m);
    m = esat::Mat3Multiply(esat::Mat3Scale(10.0f,20.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);
    return m;
}


esat::Mat3 UpdateArrow(esat::Vec2 pos, float angle, float scale_y = 10.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(10.0f,scale_y),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(pos.x,pos.y),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()),m);
    return m;
    // m = esat::Mat3Multiply(esat::Mat3Rotate(3.14f),m);
    // m = esat::Mat3Multiply(esat::Mat3Translate(0.0f,7.0f),m);
    // m = esat::Mat3Multiply(esat::Mat3Scale(10.0f,20.0f),m);
    // m = esat::Mat3Multiply(esat::Mat3Rotate(angle),m);
}

esat::Mat3 UpdateCircle(float scale_x,float scale_y, float angle = 0.0f){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale_x, scale_y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);

    return m;
}

int esat::main(int argc, char **argv) {


	esat::WindowInit(900,900);
	WindowSetMouseVisibility(true);
	srand(time(NULL));
    InitCircle();
    InitCuadrado();

    float rotation = 0.001f;

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time();
    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);
        for (size_t j = 0; j < 4; j++){
            esat::Mat3 corner = UpdateCornerArrow(1.57f * (float) j + 1.57f*0.5f);
            DrawFigure(kNArrowPoints,corner,g_arrow);
            for (int i = 0; i < 4; i++){
                esat::Mat3 arrow = UpdateArrow({(i*45) - 60.0f,120.0f},6.28f / 4 * (float) j);
                DrawFigure(kNArrowPoints,arrow,g_arrow);

                esat::Mat3 square = UpdateArrow({(i*45) - 60.0f,180.0f}, 6.28f / 4 * (float)j, 20.0f);
                DrawFigure(kNSquarePoints,square,g_square);
            }
        }

        if(esat::IsKeyDown('P'))rotation += 0.001f;
        printf("%f\n",rotation);

        esat::Mat3 cuadrado = UpdateCircle(110.0f,110.0f,6.28 / 0.039f );
        DrawFigure(kNCuadrado,cuadrado,g_cuadrado);

        esat::Mat3 hexagon = UpdateCircle(80.0f,80.0f);
        DrawFigure(kNCircle,hexagon,g_circle);

        
    

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
