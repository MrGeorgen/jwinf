#include <stdio.h>
#include <acl/file.h>
#include <string.h>
#include <stddef.h>
#include <acl/array.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#define wordCount 3 // Anzahl der Wörter des Passworts
#define randomInt_len (2 * wordCount)
#define wordsForPass_len randomInt_len / 2
void pointerCheck(void *pointer) {
	if(pointer == NULL) {
		perror("Error: ");
		exit(-1);
	}
}

int main() {
	bool sucess;
	char *woerterText = acl_ReadTextFile("wörter.txt", &sucess);
	if(!sucess) perror("Error: ");
	unsigned len = strlen(woerterText);
	uintptr_t dest = (uintptr_t)woerterText + len;
	char **woerter = acl_arraylist_create(1, sizeof *woerter);
	pointerCheck(woerter);
	woerter[0] = woerterText;
	for(char *i = woerterText; (uintptr_t)i < dest; ++i) {
		if(*i == '\n') {
			char *nextWord = i + 1;
			woerter = acl_arraylist_append(woerter, &nextWord);
			pointerCheck(woerter);
			*i = '\0';
		}
	}
	FILE *randomFile = fopen("/dev/random", "rb");
	uint32_t randomInt[randomInt_len];
	fread(randomInt, sizeof *randomInt, randomInt_len, randomFile);
	size_t passLen = wordsForPass_len + 1; // weil Ziffern im Passwort gleich oft vorkommen wie Wörter. + 1 für ein Satzzeichen am Ende
	char *wordsForPass[wordsForPass_len];
	for(uint32_t i = 0; i < wordsForPass_len; ++i) {
		wordsForPass[i] = woerter[randomInt[i] % acl_arraylist_len(woerter)];
		passLen += strlen(wordsForPass[i]);
	}
	char *password = malloc(passLen + 1);
	password[0] = '\0';
	uint32_t j = 0;
	for(uint32_t i = wordsForPass_len; i < randomInt_len; ++i, ++j) {
		char buf[2];
		buf[1] = '\0';
		sprintf(buf, "%" PRIu32, randomInt[i] % 10);
		strcat(password, buf);
		strcat(password, wordsForPass[j]);
	}
	const char specialCharacter[] = {'?', '.', ',', '!', ';'};
	char randomSpecialCharacter[] = {specialCharacter[randomInt[randomInt_len - 1] % (sizeof specialCharacter - 1)], '\0'};
	printf("%s", strcat(password, randomSpecialCharacter));
}
