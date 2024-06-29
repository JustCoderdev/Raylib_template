#include <stdlib.h>
#include <stdio.h>

#include "core.h"
#include "hotdraw.h"

#define DEBUG_ENABLE 1
#include <raylib.h>

/* 4x3  200 800x600  80 320x240  50 200x150 */
/* 3x2  200 600x400  80 360x240  50 150x100 */
const n16 WINDOW_WIDTH = 320;
const n16 WINDOW_HEIGHT = 240;


int main(void) {
	HGL_State state = {0};
	n64 tick = 0;

#define DL_PATH ("libhotfile.so")
	HGL_load(DL_PATH);

	SetTargetFPS(20);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world MF!");

	HGL_init_fn(&state);
	while(!WindowShouldClose()) {

		if(IsKeyPressed(KEY_R))
			HGL_reload();

		HGL_tick_fn(&state);
	}

	HGL_stop_fn(&state);
	HGL_unload();

	CloseWindow();
	return 0;
}
