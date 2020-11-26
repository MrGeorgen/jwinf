#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <acl/file.h>

enum baulwurfhuegel{baulwurfhuegel = 'X', keinBaulwurfhuegel = ' '}; // enums um die Lesbarkeit zu verbessern.

int width, height;

void pointerCheck(void *pointer) {// Funktion um auf NULL Pointer zu checken und den Fehler auszugeben.
	if(pointer == NULL) {
		perror("Error: ");
		exit(-1);
	}
}

// Funktion die überprüft ob relativ zur angegebenen Position eine Spalte mit 4 Maulwurfhügel ist.
bool checkRow(char *row) {
	for(uint8_t i = 0; i < 4; ++i) {
		if(row[i * (width + 1)] == keinBaulwurfhuegel) return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	if(argc == 1) { // das Programm wird beendet wenn die Anzahl der Argumente falsch ist.
		fprintf(stderr, "file argument required\n");
		exit(-1);
	}
	for(int filePath = 1; filePath < argc; ++filePath) {
		bool sucess;
		FILE *fp = fopen(argv[filePath], "rb"); // Datei wird im binären Modus geöffent, um die Geschwindigkeit zu verbessern.
		char *input = acl_ReadTextFile(fp, &sucess);
		fclose(fp);
		pointerCheck(input);
		char *heightText;
		char *textRest;
		width = strtol(input, &heightText, 10);
		++heightText; // Das nächste Zeichen nach der Breite ist \n. Danach das Zeichen ist erst die Höhe.
		height = strtol(heightText, &textRest, 10); // Der Rest der Textdatei ist die Karte mit den Maulwurfhügeln.
		++textRest; // wieder damit der Pointer auf \n zeigt
		unsigned baulwurfhuegelCounter = 0;
		for(char *i = textRest; (uintptr_t)i <= (uintptr_t)textRest + ((height - 4) * (width + 1)); i += width + 1) { // iteriert über die Zeilen der Karte.
			for(char *j = i; (uintptr_t)j < (uintptr_t)i + width - 1; ++j) { // iteriert immer ein Schritt nach rechts.
				baulwurfhuegelCounter += checkRow(j) && checkRow(j + 2) /* überprüft ob sich die beiden 4er Zeilen der Baulwurfhügelformation stimmen */ && j[1] == baulwurfhuegel && j[1 + 3 * (width + 1)] == baulwurfhuegel /* überprüft die Maulwurfhügel oben und unten in der Mitte da sind */ && j[1 + 2 * (width +1)] == keinBaulwurfhuegel && j[1 + (width + 1)] == keinBaulwurfhuegel; // überprüft ob in der Mitte keine Maulwurfhügel sind
			}
		}
		free(input);
		printf("%s: %u\n", argv[filePath], baulwurfhuegelCounter); // gibt den Dateipfad und die Anzahl der Baulwürfe aus
	}
}
