# Allgemeine Informationen

Die Grundidee für meinen Passwortgenerator ist das Passwort aus richtigen Wörtern zu bilden.
Als erstes Argument muss man einen Dateipfad zu der Textdatei mit einer Liste von Wörtern, die von einem Zeilenumbruch getrennt sind, verwenden.
Unter wörter.txt ist ein Beispiel dafür ([Quelle](https://www.netzmafia.de/software/wordlists/deutsch.txt)).
Das Passwort wird zu stdout ausgegeben.

# Regeln für das generierte Passwort

1. Zufällige Wörter werden aus der Wörterliste ausgewählt.
2. Am Anfang des Passworts und zwischen den Wörtern steht eine Ziffer.
3. Am Ende steht ein Satzzeichen.

# Funktionsweise

Als erstes wird die angebene Textdatei mit der Wörterliste ausgelesen.
Alle Zeilenumbrüche werden durch \0 ersetzt und Pointer zu jedem Wort in einem Array gespeichert.
```
for(char *i = woerterText; (uintptr_t)i < dest; ++i) {
	if(*i == '\n') {
		char *nextWord = i + 1;
		woerter = acl_arraylist_append(woerter, &nextWord);
		pointerCheck(woerter);
		*i = '\0';
	}
}
```
Danach werden Bytes mit zufälligen Werten von `/dev/random` ausgelesen.<br>
`	fread(randomInt, sizeof *randomInt, randomInt_len, randomFile);`<br>
Dafür habe ich mich entschieden, da dieser ein krypografisch sicherer Zufallszahlengenerator ist.
Passwörter, die mit Pseudozufallszahlengeneratoren generiert werden, sind einfach zu knacken, da bei diesen jede Zufallszahl von der vorherigen abhängt.
Oft wird als Startwert auch noch die aktuelle Zeit benutzt, was das Ganze noch unsicherer macht.
Auf Basis der Zufahlszahlen wird dann das Passwort aus Wörtern und Ziffern zusammengesetzt.
```
for(uint32_t i = wordsForPass_len; i < randomInt_len; ++i, ++j) {
	char buf[2];
	buf[1] = '\0';
	sprintf(buf, "%" PRIu32, randomInt[i] % 10);
	strcat(password, buf);
	strcat(password, wordsForPass[j]);
}
```
Zum Schluss wird noch ein zufälliges Satzzeichen angehängt.
```
const char specialCharacter[] = {'?', '.', ',', '!', ';'};
char randomSpecialCharacter[] = {specialCharacter[randomInt[randomInt_len - 1]
% (sizeof specialCharacter - 1)], '\0'};
```
Dann wird das Passwort wird schließlich ausgegeben.

# Beispiel

Beipielausgabe: `0zaehneknirschend8verraeterischem6veranstaltet,`<br>
Die Textdatei in diesem Fall wörter.txt wurde ausgelesen, \\n durch \0 ersetzt um das Ende vom String zu markieren.
Danach wurden Pointer zu jedem Wort der Textdatei erstellt.
Anschließend wurden die Wörter zaehneknischend, verraeterischem, veranstaltet, die Ziffern 0, 8, 6 ausgewählt und zusammengesetzt.
Ein Komma wurde angehängt und das Passwort schließlich ausgegeben.
