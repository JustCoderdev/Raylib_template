#include "hotdraw.h"

#include <stdio.h>
#include <raylib.h>


Color COLOR_FOREGROUND = {  238, 119, 119, 255 };
Color COLOR_BACKGROUND = {   30,  30,  30, 255 };
Color COLOR_DEBUG      = {   62,  62,  62, 255 };

#define TICK_STR_LEN (21)
#define FPS_STR_LEN (3)

char tick_string[TICK_STR_LEN] = {0};
char fps_string[FPS_STR_LEN] = {0};
void ntos(char* string, const n64 len, n64 tick) {
	n64 i;

	for(i = 0; i < len; ++i) {
		if(tick == 0) {
			string[len - i - 1] = '-';
			continue;
		}

		{
			n8 rest = tick % 10;
			string[len - i - 1] = '0' + rest;
			tick -= rest;
		}

		if(tick != 0) tick /= 10;
	}
}

void init_fn(HGL_State* state) {
	printf("Loaded module!");
	state->tick = 0;
}

void tick_fn(HGL_State* state) {
/* DEBUG HOT */
	char* chars = "|/-\\";
	/* char* chars = "aAbBcC"; */

	printf("\r%c", chars[(state->tick)++ % 4]);
	fflush(stdout);
/* DEBUG HOT */


	BeginDrawing();
	ClearBackground(COLOR_BACKGROUND);

#if DEBUG_ENABLE
	ntos(fps_string, FPS_STR_LEN, (n64)GetFPS());
	DrawText(fps_string, 10, 10, 16, COLOR_DEBUG);

	ntos(tick_string, TICK_STR_LEN, state->tick);
	DrawText(tick_string, 10, 20, 16, COLOR_DEBUG);
	state->tick++;
#endif

	DrawText("AABAA", 30, 50, 20, RED);

	EndDrawing();
}

void stop_fn(HGL_State* state) {

}
