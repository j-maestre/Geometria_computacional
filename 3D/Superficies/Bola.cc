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
const int kNPoints = 10;
// esat::Vec4 circle[kNPoints];
const int kNPointsCirculo = 45;
esat::Vec3 circle[kNPointsCirculo];



esat::Vec3 gr_points[kNPoints] = {
    0.0f, 0.0f, 1.0f,
    0.45f, 0.0f, 1.0f,
    0.8f, 0.35f, 1.0f,
    0.9f, 0.35f, 1.0f,
    1.0f, 0.25f, 1.0f,
    1.0f, 0.35f, 1.0f,
    0.9f, 0.45f, 1.0f,
    0.8f, 0.45f, 1.0f,
    0.45f, 0.1f, 1.0f,
    0.0f, 0.1f, 1.0f
};

    

 void Initcircle()
 {
     float angle = 6.28f / kNPointsCirculo;
     for (int i = 0; i < kNPointsCirculo; i++)
     {
         circle[i].x = cos(i * angle);
         circle[i].y = sin(i * angle);
         circle[i].z = 1.0f;
     }
}


void DrawFigure(esat::Mat3 base, esat::Vec3 *figura_points, int n_points){
    esat::Vec3 tmp;
    esat::Vec2 points[100];

    for (int i = 0; i < n_points; i++){
        tmp = esat::Mat3TransformVec3(base, figura_points[i]);
        points[i] = {tmp.x,tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&points[0].x,n_points);
    
}

esat::Mat3 UpdateDerivedFigure(esat::Mat3 base, bool inverted, float angle){
    esat::Mat3 m = esat::Mat3Identity();
    if(!inverted)m = esat::Mat3Multiply(esat::Mat3Scale(1.0f, 1.0f), m);
    if(inverted)m = esat::Mat3Multiply(esat::Mat3Scale(1.0f, -1.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(1.0f, 0.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    // m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);
    m = esat::Mat3Multiply(base, m);

    return m;
}
esat::Mat3 UpdateCircleFigure(){
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(100.0f, 100.0f), m);
    // m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.005f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);
    return m;
}

int esat::main(int argc, char **argv){
    srand(time(NULL));

    esat::WindowInit(700, 700);
    WindowSetMouseVisibility(true);
    // esat::Mat4 base = CreateCube();
    Initcircle();

    // InitCircle();

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape))
    {

        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        esat::Mat3 d_circle = UpdateCircleFigure();
        DrawFigure(d_circle,circle,kNPointsCirculo);
        float angle(6.28f/7.0f);
        for (int i = 0; i < 7; i++){
            /* code */
    
            esat::Mat3 figura = UpdateDerivedFigure(d_circle,false,angle);
            esat::Mat3 figura2 = UpdateDerivedFigure(d_circle,true,angle);
            DrawFigure(figura, gr_points, kNPoints);
            DrawFigure(figura2, gr_points, kNPoints);
        }

        // esat::Mat4 cubo2 = DrawDerivatedCube(base);
        // DrawCube(cubo2);

        // esat::DrawLine(cubo.x,cubo.y);
        // esat::Mat3 base = UpdateBaseFigure();
        // DrawCircle(base);

        esat::DrawEnd();

        // Control FPS
        do
        {
            current_time = esat::Time();
        } while ((current_time - last_time) <= 1000.0 / fps);

        esat::WindowFrame();
    }

    esat::WindowDestroy();

    return 0;
}
