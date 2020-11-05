#include <stdio.h>

void pointerCheck(void *pointer) {
	if(pointer == NULL) {
		perror("Error: ");
		exit(-1);
	}
}

int main(int argc, char *argv[]) {
	if(argc != 2) printf("file argument required");
	bool sucess;
	FILE *fp = fopen(argv[1], "rb");
	char *input = acl_ReadTextFile(fp, &sucess);
