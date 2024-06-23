#include <stdio.h>

void setup(void) {
	printf("Loaded moduleA\n");
}

void loop(void) {
	static int state = 0;
	/* char* chars = "|/-\\"; */
	char* chars = "aAbBcC";
	printf("\r%c", chars[state++ % 4]);
	fflush(stdout);
}
