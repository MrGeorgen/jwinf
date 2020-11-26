#include <stdio.h>
#include <acl/file.h>
#include <acl/array.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


char *substitutedWord;

void pointerCheck(void *pointer) {
	if(pointer == NULL) {
		perror("Error: ");
		exit(-1);
	}
}

bool tryFillWord(char *einsetzbaresWort, char *lueke) {
	char *j = lueke;
//	printf("len %lu\n", strlen(einsetzbaresWort));
	//printf("wort: %sb baum: %c%c%c\n", einsetzbaresWort, lueke[0], lueke[1], lueke[2]);
	for(char *i = einsetzbaresWort; *i != '\0'; ++i, ++j) {
		if(!(*j == '_' || *j == *i)) {
			if(*i == '\0') printf("null\n");
	//		printf("wwwort%cbaum%cb\n", *i, *j);
			return false;
		}
	}
	int w = *j;
	if(*j != ' ' && *j != ',' && *j != '\n' && *j != '.' && *j != ';' && *j != ':' && *j != '\0' && *j != '?' && *j != '!') return false;
	substitutedWord = lueke;
	//printf("wort geöst\n");
	return true;
}

int main(int argc, char *argv[]) {
	if(argc != 2) printf("file argument required");
	bool sucess;
	FILE *fp = fopen(argv[1], "rb");
	char *input = acl_ReadTextFile(fp, &sucess);
	fclose(fp);
	pointerCheck(input);
	if(input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = '\0';
/* ein Weg um den Beginn der zweiten Zeile zu finden.
 * Man Könnte auch die Datei im Textmodus öffnen, da bei zwei Zeilen der Geschwindigkeitsverlust nicht groß wäre, aber man es für beliebig große Lückentexte machen wollte, bräuchte man wieder zwei memory allocations.
 * Dadurch wäre der Code auch nicht wirklich einfacher.*/
	char *words = input;
	printf("%s\n", input);
	while(*words != '\n') ++words;
	*words = '\0';
	++words;
	// Alle Wörter, die in den Lückentext eingesetzt werden, werden einem array hinzugefügt.
	char **availableWords = acl_arraylist_create(1, sizeof *availableWords);
	availableWords[0] = words;
	for(char *i = words; *i != '\0'; ++i) {
		if(*i == ' ') {
			printf("2\n");
			*i = '\0';
			char *nextWord = i + 1;
			availableWords = acl_arraylist_append(availableWords, &nextWord);
			pointerCheck(availableWords);
		}
	}
	while(acl_arraylist_len(availableWords)) { // Wenn die Länge vom array 0 ist, haben wir alle Wörter eingesetzt.
		for(uint32_t i = 0; i < acl_arraylist_len(availableWords); ++i) {
			uint32_t matchCounter = 0;
			matchCounter += tryFillWord(availableWords[i], input);
			for(char *k = input; *k != '\0'; ++k) {
				if(*k == ' ') matchCounter += tryFillWord(availableWords[i], k + 1);
			}
			if(matchCounter != 1) continue;
			//availableWords = acl_arraylist_remove(availableWords, i);
			memcpy(substitutedWord, availableWords[i], strlen(availableWords[i]));
		}
		printf("%s\n", input);
	}
	printf("%s", input);
	free(input);
	acl_arraylist_free(availableWords);
}
