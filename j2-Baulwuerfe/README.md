# Verwendung

Als Argument nimmt das Programm beliebig viele Dateipfade mit Maulwurfkarten an.<br>
z. B. `./j2 beispieldaten/karte0.txt beispieldaten/karte1.txt`<br>
Als Ausgabe erhält man:
```
beispieldaten/karte0.txt: 3 
beispieldaten/karte1.txt: 37 
```

# Funktionsweise

Mein Programm verwendet eine for-Schleife, die über Zeilen iteriert.<br>
`		for(char *i = textRest; (uintptr_t)i <= (uintptr_t)textRest + ((height - 4) * (width + 1)); i += width + 1) {`<br>
Für das Iterieren über die einzelen Zeichen verwende ich wieder eine for-Schleife.<br>
`			for(char *j = i; (uintptr_t)j < (uintptr_t)i + width - 1; ++j) {`<br>
Um zu überprüfen, ob die vierer Zeilen eines Baulwurfhügel existieren habe ich eine Funktion geschrieben.
```
bool checkRow(char *row) {
	for(uint8_t i = 0; i < 4; ++i) {
		if(row[i * (width + 1)] == keinBaulwurfhuegel) return false;
	}
	return true;
}
```
Diese Funktion wird zweimal aufgerufen.<br>
`checkRow(j) && checkRow(j + 2)`<br>
Außerdem wird überprüft, ob in der Mitte oben und unten Maulwurfshügel vorhanden sind.<br>
`j[1] == baulwurfhuegel && j[1 + 3 * (width + 1)] == baulwurfhuegel && j[1 + 2 * (width +1)] == keinBaulwurfhuegel && j[1 + (width + 1)] == keinBaulwurfhuegel;`<br>
Wenn die Maulwurfshügelfomration vorhanden ist, dann wird ein Counter um eins erhöht.
Nachdem die for-Schleifen fertig gelaufen sind wird die Anzahl der Baulwurfhügel ausgegeben.

# Beispiel

Als Beispiel schauen wir uns mal `karte0.txt` an.
An der ersten Position oben links wird gleich ein Baulwurfshügel erkannt und gezählt.
Danach wird Zeichen für Zeichen und Zeile für Zeile auf Baulwurfshügel überprüft.
Es wird erst wieder in Zeile 2, Zeichen 12 ein Baulwurfshügel gezählt sowie in Zeile 3, Zeichen 14.
Schließlich wird das Ergebnis ausgegeben.<br>
`beispieldaten/karte0.txt: 3`
