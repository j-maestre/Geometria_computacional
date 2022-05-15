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

esat::Vec3 circle[kNPoints];

/*
	a = {4,6}
	b = {10,6}
	v = b-a = {6,0}
	vn = Normal(v) = {1,0}

	Quedarse con si es mayor o menos que 0
	Si hay algun que no es positiva, no hay colision

	-----------------
	Esquina superior izquierda, punto de pivotaje, dibujo una figura transladandola de ahi (hecho)
	Tenemos una linea dibujada, de un punto A a un punto B
	Esa linea es solo una linea de una figura con unas cuantas lineas (infinitamente)

	Punto A = {4,6}
	Punto B = {10,6}

	Vector v = B-A  ok

	Normalizar v, resultado = {1,0} 

	De ese vector podemos sacar un par de perpendiculares

	SACAR LA NORMAL
	Vector n1 = invertir x e y, y multiplico y por -1
	Vector n2 = invertir x e y, y multiplico x por -1

	Resultado:

	{-y,x} = {0,1} {y,-x} = {0,-1}

	Podemos coger la que queramos, vamos a coger n1

	Punto Q = mousePosition {7,2}

	Vector W = Q-A

	W = {3,-4}


	Aplicamos el dot product de un vector normalizado y de otro que no está
	dot(n1,w) = 0 * 3 + 1 * (-4) = -4 -> Como está en negativo, está fuera, pero si estuviera en positivo estaria dentro
	Esto es porque hemos escogido n1, si hubieramos escogido n2, habria dado 4, por lo que seria positivo

	Si cogemos n1 en una linea, debemos escoger n1 en las otras lineas, y todos los valores tienen que dar positivo para 
	que haya colision, si solo un valor está en negativo, no hay colision
	-----------------

*/

void CheckColision(esat::Mat3 m){

	bool colision = true;
	// int i = 0;
	esat::Vec2 tr_circle[360];
	esat::Vec3 temp = esat::Mat3TransformVec3(m,circle[0]);
	tr_circle[0] = {temp.x,temp.y}; 
	esat::DrawLine(tr_circle[0].x,tr_circle[0].y,esat::MousePositionX(),esat::MousePositionY());
	printf("X [%f]\n",tr_circle[0].y);
	

	for (int i = 0; i < kNPoints-1; i++){

		



		//Punto V = B-A
		xemath::Vector2 vecV = {circle[i+1].x - circle[i].x,circle[i+1].y - circle[i].y};
		vecV = xemath::Vec2Normalize(vecV);
		xemath::Vector2 n1 = {vecV.y * (-1), vecV.x};

		xemath::Vector2 mouse = {(float) esat::MousePositionX(),(float) esat::MousePositionY()};

		//W = Mouse - A
		xemath::Vector2 vecW = {mouse.x - circle[i].x, mouse.y - circle[i].y};

		//Sacar el dot product de un vector normalizado y de otro que no está dot(n1,w)
		n1 = xemath::Vec2Normalize(n1);
		float dotProduct = (n1.x * vecW.x) + (n1.y * vecW.y);

		if(esat::MouseButtonDown(0) ){
			// i++;
			printf("\nNormalizado-> X[%f] Y[%f]\n",n1.x,n1.y);
			printf("Dot Product [%f]\n",dotProduct);
		}
		
		if(dotProduct < 0)colision=false;
	}

	// if(colision)printf("COLISION!\n");
	

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


void DrawCircle(esat::Mat3 m){

	esat::Vec2 tr_circle[360];
	for (int i = 0; i < kNPoints; i++){
		esat::Vec3 temp = esat::Mat3TransformVec3(m,circle[i]);
		tr_circle[i] = {temp.x,temp.y}; 
	}

	esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&tr_circle[0].x,kNPoints);
	


}



int esat::main(int argc, char **argv) {
	srand(time(NULL));

	esat::WindowInit(900, 900);
	WindowSetMouseVisibility(true);
	InitCircle();


  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

		esat::DrawBegin();
		esat::DrawEnd();
		esat::Mat3 base = UpdateBaseFigure();
		DrawCircle(base);
		CheckColision(base);

		//Control FPS
		do {
			current_time = esat::Time();
		} while ((current_time - last_time) <= 1000.0 / fps);

		esat::WindowFrame();
	}

	esat::WindowDestroy();

	return 0;
}
