#include <stdio.h>
#include <raylib.h>

#define DEBUG_ENABLE 1

typedef unsigned char      n8;
typedef unsigned short int n16;
typedef unsigned long int  n64;

typedef signed char      i8;
typedef signed short int i16;
typedef signed long int  i64;

/* 4x3  800x600  400x300  200x150 */
const n16 WINDOW_WIDTH = 800;
const n16 WINDOW_HEIGHT = 600;

Color COLOR_FOREGROUND = {  238, 119, 119, 255 };
Color COLOR_BACKGROUND = {   30,  30,  30, 255 };
Color COLOR_DEBUG      = {   42,  42,  42, 255 };

#define TICK_STRING_LEN (21)

char tick_string[TICK_STRING_LEN] = {0};

void tick_string_update(char* string, n64 tick) {
	i8 i;

	for(i = TICK_STRING_LEN - 2; i >= 0; --i) {
		if(tick == 0) {
			string[i] = '-';
			continue;
		}

		{
			n8 rest = tick % 10;
			string[i] = '0' + rest;
			tick -= rest;
		}

		if(tick != 0) tick /= 10;
	}
}

int main(void) {
	n64 tick = 0;

	InitWindow(600, 300, "Hello world MF!");
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(COLOR_BACKGROUND);

		tick_string_update(tick_string, tick);
		DrawText(tick_string, 30, 30, 20, COLOR_DEBUG);
		DrawText("AAAAAA", 30, 50, 20, RED);

		tick++;
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
