#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <acl/file.h>

enum baulwurfhuegel{baulwurfhuegel = 'X', keinBaulwurfhuegel = ' '};

int width, height;

void pointerCheck(void *pointer) {
	if(pointer == NULL) {
		perror("Error: ");
		exit(-1);
	}
}

bool checkRow(char *row) {
	for(uint8_t i = 0; i < 4; ++i) {
		if(row[i * (width + 1)] == keinBaulwurfhuegel) return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	if(argc != 2) printf("file argument required");
	bool sucess;
	FILE *fp = fopen(argv[1], "rb");
	char *input = acl_ReadTextFile(fp, &sucess);
	fclose(fp);
	pointerCheck(input);
	char *heightText;
	char *textRest;
	width = strtol(input, &heightText, 10);
	++heightText; // height points does not point to \n anymore
	height = strtol(heightText, &textRest, 10);
	++textRest;
	printf("height: %d width: %d\n", height, width);
	unsigned baulwurfhuegelCounter = 0;
	for(char *i = textRest; (uintptr_t)i <= (uintptr_t)textRest + ((height - 4) * (width + 1)); i += width + 1) {
		for(char *j = i; (uintptr_t)j < (uintptr_t)i + width - 1; ++j) {
			baulwurfhuegelCounter += checkRow(j) && checkRow(j + 2) && j[1] == baulwurfhuegel && j[1 + 3 * (width + 1)];
		}
	}
	free(input);
	printf("Baulwurfhuegel: %u", baulwurfhuegelCounter);
}
