#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define FILE_PATH ("./file.c")

long int lastrebuild = 0;
char shouldRecompile(void) {
	struct stat sb;

	if(stat(FILE_PATH, &sb) < 0) {
		printf("ERROR:%s:%d: Cannot get file stat %s",
				__FILE__, __LINE__, strerror(errno));

		exit(1);
		return 1;
	}

    /* Access shows the time of last data access (e.g. read). */
    /* Modify shows the time of last data modification. */
    /* Change shows the time the file status last changed. */
	printf("File accessed %lu", sb.st_atime);
	printf("File modified %lu", sb.st_mtime);
	printf("File lchanged %lu", sb.st_ctime);

	return sb.st_mtime > lastrebuild;
	return 0;
}

char compile(void) {
	return 1;
}

int main(void) {
	while(1) {
		if(shouldRecompile()) {
			printf("Compiling...  ");

			if(compile()) {
				printf("\033[31mError\033[0m\n");
			} else {
				printf("Done");
			}
		}

		printf("Waiting... \n");
		sleep(5);
	}
}
