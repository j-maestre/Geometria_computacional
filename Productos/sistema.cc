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




int esat::main(int argc, char **argv) {
	srand(time(NULL));

	esat::WindowInit(900, 900);
	WindowSetMouseVisibility(true);
	xemath::Mat3 mat1 = {2,-4,6};
	xemath::Mat3 mat2 = {3,-6,9};

	xemath::Mat3 solved = xemath::Mat32x2Solver(mat1,mat2);


  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

		esat::DrawBegin();
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
