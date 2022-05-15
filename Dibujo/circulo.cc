#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



unsigned char fps = 60;
double current_time, last_time;
const double dPI = 3.141592653589793238462643383279502884197169;




int esat::main(int argc, char **argv) {
	srand(time(NULL));

	esat::WindowInit(400, 600);
	WindowSetMouseVisibility(true);


	while(esat::WindowIsOpened() &&

		esat::DrawBegin();
		DrawCircle();
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
