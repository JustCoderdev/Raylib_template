#define RL_BOOL_TYPE
#define DEBUG_ENABLE 1

typedef unsigned char      n8;
typedef unsigned short int n16;
typedef unsigned long int  n64;

typedef signed char      i8;
typedef signed short int i16;
typedef signed long int  i64;

typedef enum bool {
	true = (1 == 1),
	false = (1 != 1)
} bool;

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#include <raylib.h>

/* 4x3  200 800x600  80 320x240  50 200x150 */
/* 3x2  200 600x400  80 360x240  50 150x100 */
const n16 WINDOW_WIDTH = 320;
const n16 WINDOW_HEIGHT = 240;

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

#define DL_FILE ("libhotreload.so")
void* dl_handle = NULL;
void (*setupFunc)(void) = NULL;
void (*loopFunc)(void) = NULL;
void loadDL(void) {
	char* error = NULL;

	dl_handle = dlopen(DL_FILE, RTLD_NOW);
	if(dl_handle == NULL) {
		printf("\033[35mFailed to load dl\033[0m: %s\n", dlerror());
		exit(1);
	}

	setupFunc = dlsym(dl_handle, "setup");
	if((error = dlerror())) {
		printf("\033[35mFailed to load symbol setup\033[0m: %s\n", error);
		exit(1);
	}

	loopFunc = dlsym(dl_handle, "loop");
	if((error = dlerror())) {
		printf("\033[35mFailed to load symbol setup\033[0m: %s\n", error);
		exit(1);
	}

	printf("\033[34mLoaded DL successfully\033[0m\n");
}
void unloadDL(void) {
	setupFunc = NULL;
	loopFunc = NULL;
	if(dlclose(dl_handle)) {
		printf("\033[35mFailed to unload DL\033[0m: %s\n", dlerror());
		exit(1);
	}

	dl_handle = NULL;

	printf("\033[36mUnloaded DL Successfully\033[0m\n");
}

int main(void) {
	n64 tick = 0;

	loadDL();

	SetTargetFPS(20);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world MF!");
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(COLOR_BACKGROUND);

		if(IsKeyPressed(KEY_R)) {
			unloadDL();
			loadDL();
			if(setupFunc != NULL) setupFunc();
		}
		if(loopFunc != NULL) loopFunc();

#if DEBUG_ENABLE
		/* DrawLine( 80, 0,  80, WINDOW_HEIGHT, COLOR_DEBUG); */
		/* DrawLine(160, 0, 160, WINDOW_HEIGHT, COLOR_DEBUG); */
		/* DrawLine(240, 0, 240, WINDOW_HEIGHT, COLOR_DEBUG); */

		/* DrawLine(0,  80, WINDOW_WIDTH,  80, COLOR_DEBUG); */
		/* DrawLine(0, 160, WINDOW_WIDTH, 160, COLOR_DEBUG); */

		ntos(fps_string, FPS_STR_LEN, (n64)GetFPS());
		DrawText(fps_string, 10, 10, 16, COLOR_DEBUG);

		ntos(tick_string, TICK_STR_LEN, tick);
		DrawText(tick_string, 10, 20, 16, COLOR_DEBUG);
		tick++;
#endif

		DrawText("AAAAAA", 30, 50, 20, RED);

		EndDrawing();
	}

	if(dl_handle != NULL)(void)dlclose(dl_handle);
	CloseWindow();
	return 0;
}
