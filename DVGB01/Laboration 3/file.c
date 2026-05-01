#include "file.h"

trace loadTraces(char* filename) {
    FILE *openedFile;
	openedFile = fopen(filename, "r");
	if(openedFile == NULL) { // file doesn't exist i guess. . .
		printf("That trace file doesn't exist.\n");
		exit(1);
	}

    int lines = 1;
    while (EOF != (fscanf(openedFile, "%*[^\n]"), fscanf(openedFile, "%*c")))
        lines++;
    rewind(openedFile);

    trace traces;
    traces.address = (int*)malloc(lines * sizeof(int));
    traces.length = lines;
	for(int i = 0; i < traces.length; i++) // we're assuming that we never save names that contain comma
        fscanf(openedFile, "%x\n", &traces.address[i]);
	fclose(openedFile);

    return traces;
}
