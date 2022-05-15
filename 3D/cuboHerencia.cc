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



// T1-> (400,300,00)
// S-> (100,100,1)
// T2-> (0,0,4)

//* for(0 ... n_points por cara)
    //*
// void InitCircle(){
//     float angle = 6.28 / (float) kNPoints;
//     for (int i = 0; i < kNPoints; i++){
//         circle[i].x = (float) cos(angle * i);
//         circle[i].y = (float) sin(angle * i);
//         circle[i].z = 1.0f;
//     }
// }

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

esat::Mat4 CreateCube(){
    esat::Mat4 m = esat::Mat4Identity();
    m = esat::Mat4Multiply(esat::Mat4RotateX((esat::Time()*0.05f) * (dPI/180)),m);
    m = esat::Mat4Multiply(esat::Mat4RotateY((esat::Time()*0.05f) * (dPI/180)),m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ((esat::Time()*0.05f) * (dPI/180)),m);

    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f,0.0f,4.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Projection(),m);
    m = esat::Mat4Multiply(esat::Mat4Scale(75.0f,75.0f,1.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(esat::MousePositionX(),esat::MousePositionY(),0.0f),m);


    //*Transformar a Vec3 y ya podemos pintar

    return m;
}


void DrawCube(esat::Mat4 m){
    
    esat::DrawSetFillColor(255,255,255);
    esat::DrawSetStrokeColor(255,255,255);
     for (int i = 0; i < 4; i++){
            /* code */
            //Punto 1
            esat::Vec3 cara1 = esat::Mat4TransformVec3(m,puntos1[i]);
            esat::Vec3 cara2 = esat::Mat4TransformVec3(m,puntos1[i+1]);

            esat::Vec3 fondo1 = esat::Mat4TransformVec3(m,puntos2[i]);
            esat::Vec3 fondo2 = esat::Mat4TransformVec3(m,puntos2[i+1]);

            if(i == 3){
                cara2 = esat::Mat4TransformVec3(m,puntos1[0]);
                fondo2 = esat::Mat4TransformVec3(m,puntos2[0]);
            }

            esat::DrawLine(cara1.x,cara1.y,cara2.x,cara2.y);
            esat::DrawLine(fondo1.x, fondo1.y, fondo2.x, fondo2.y);

            esat::DrawLine(cara1.x,cara1.y,fondo1.x,fondo1.y);
            esat::DrawLine(cara2.x,cara2.y,fondo2.x,fondo2.y);

            

        }
}


esat::Mat4 UpdateBaseFigure(){
    esat::Mat4 m = esat::Mat4Identity();
    //trasladar justo delante (0,0,4) proyectar, escalar, trasladar a la posicion que queremos
    m = esat::Mat4Multiply(esat::Mat4RotateX((esat::Time()*0.05f) * (dPI/180)),m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ((esat::Time()*0.05f) * (dPI/180)),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f,0.0f,5.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Projection(),m);
    m = esat::Mat4Multiply(esat::Mat4Scale(100.0f,100.0f,1.0f),m);
    m = esat::Mat4Multiply(esat::Mat4Translate(esat::MousePositionX(), esat::MousePositionY(), 0.0f), m);

    return m;
}

esat::Mat4 DrawDerivatedCube(esat::Mat4 base){

    esat::Mat4 m = esat::Mat4Identity();

    m = esat::Mat4Multiply(esat::Mat4RotateX((esat::Time() * 0.05f) * (dPI / 180)), m);
    m = esat::Mat4Multiply(esat::Mat4RotateY((esat::Time() * 0.05f) * (dPI / 180)), m);
    // m = esat::Mat4Multiply(esat::Mat4RotateZ((esat::Time() * 0.05f) * (dPI / 180)), m);

    // m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 4.0f), m);
    // m = esat::Mat4Multiply(esat::Mat4Projection(), m);
    m = esat::Mat4Multiply(esat::Mat4Scale(0.5f, 0.5f, 0.5f), m);
    m = esat::Mat4Multiply(esat::Mat4Translate(4.0f,0.0f, 0.0f), m);
    m = esat::Mat4Multiply(base,m);
    // m = esat::Mat4Multiply(esat::Mat4Translate(100.0f, 100.0f, 0.0f), m);


    //*Transformar a Vec3 y ya podemos pintar

    return m;
}


int esat::main(int argc, char **argv){
    srand(time(NULL));

    esat::WindowInit(700, 700);
    WindowSetMouseVisibility(true);
    esat::Mat4 base = CreateCube();

    // InitCircle();

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)){

        esat::DrawBegin();
        esat::DrawClear(0,0,0);

        base = UpdateBaseFigure();
        DrawCube(base);
        esat::Mat4 cubo2 = DrawDerivatedCube(base);
        DrawCube(cubo2);

        // esat::DrawLine(cubo.x,cubo.y);
        // esat::Mat3 base = UpdateBaseFigure();
        // DrawCircle(base);


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
