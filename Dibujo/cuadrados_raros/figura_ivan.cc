#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"

const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

const int kNArrowPoints = 4;
esat::Vec3 g_arrow[kNArrowPoints] = {
    0.0f,
    1.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    0.0f,
    -3.0f,
    1.0f,
    -1.0f,
    0.0f,
    1.0f,
};

const int kNSquare = 4;
esat::Vec3 g_square[kNSquare] = {
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

esat::Mat3 UpdateArrow(esat::Vec2 pos, float angle, float scale_y = 10.0f)
{
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(10.0f, scale_y), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(pos.x, pos.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate((float)esat::MousePositionX(),
                                               (float)esat::MousePositionY()),
                           m);
    return m;
}

esat::Mat3 UpdateCornerArrow(float angle)
{
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Rotate(3.14f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, 7.5f), m);
    m = esat::Mat3Multiply(esat::Mat3Scale(10.0f, 20.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate((float)esat::MousePositionX(),
                                               (float)esat::MousePositionY()),
                           m);
    return m;
}

void DrawFigure(const int n_points, esat::Mat3 m, esat::Vec3 *points)
{
    esat::Vec2 tr_points[100];
    for (int i = 0; i < n_points; ++i)
    {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, points[i]);
        tr_points[i] = {tmp.x, tmp.y};
    }
    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0, 0);
    esat::DrawSolidPath(&tr_points[0].x, n_points);
}

int esat::main(int argc, char **argv)
{
    srand(time(nullptr));
    double current_time = 0.0;
    double last_time = 0.0;
    double fps = 60.0;
    esat::WindowInit(kWindowWidth, kWindowHeight);

    WindowSetMouseVisibility(true);

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
           esat::WindowIsOpened())
    {
        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(120, 120, 120);

        for (int j = 0; j < 4; ++j)
        {
            esat::Mat3 c_arrow = UpdateCornerArrow(1.57 * (float)j + 1.57f * 0.5f);
            DrawFigure(kNArrowPoints, c_arrow, g_arrow);
            for (int i = 0; i < 5; ++i)
            {
                esat::Mat3 m_arrow = UpdateArrow({i * 30 - 60.0f, 120.0f}, 6.28f / 4.0f * (float)j);
                DrawFigure(kNArrowPoints, m_arrow, g_arrow);
                esat::Mat3 m_square = UpdateArrow({i * 30 - 60.0f, 160.0f}, 6.28f / 4.0f * (float)j, 20.0f);
                DrawFigure(kNSquare, m_square, g_square);
            }
        }

        esat::DrawEnd();
        esat::WindowFrame();

        do
        {
            current_time = esat::Time();
        } while ((current_time - last_time) <= 1000.0 / fps);
    }
    esat::WindowDestroy();
    return 0;
}