/*
Willkommen zum achten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Pointer und Arrays.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "turtlecanvas.h"

/*
Aufgabe 1a:
Lesen Sie das Headerfile `turtlecanvas.h`. Diese Funktion soll die Turtle `d` Schritte vorwärts machen lassen.
*/
void turtle_advance_by(TurtleCanvas *c, uint32_t d) {

    for (int32_t i = 0; i < d; i++)                                 // Laufe solange wie "d" ist
    {
        turtle_advance(c);
    }
    
    return;
}

/*
Aufgabe 1b:
Füllen Sie die Turtlecanvas mit horizontalen, abwechselnd schwarzen und weißen Linien (die unterste Zeile soll
schwarz gefärbt werden). Die Turtle ist anfangs an Position (0, 0), ist nach rechts orientiert, und zeichnet schwarz.
*/
void turtle_stripes(TurtleCanvas *c) {

    for (int32_t i = 0; i <= turtle_canvas_height(c); i++)          // Solange die höhe der Canvas nicht erreicht wurde
    {
        turtle_advance_by(c, turtle_canvas_width(c));               // Laufe die länge der canvas lang
        turtle_rotate_left(c);                                      // dreh um
        turtle_rotate_left(c);
        turtle_advance_by(c, turtle_canvas_width(c));               // Laufe zurück
        turtle_rotate_right(c);                                     // Laufe einen schritt nach oben
        turtle_toggle_color(c);                                     // und färbe den zwischenpixel nicht ein
        turtle_advance(c);
        turtle_advance(c);
        turtle_toggle_color(c);                                     // Färbe den Nächsten Pixel wieder ein
        turtle_rotate_right(c);                                     // Gehe wieder zurück in die startposition
    }

    return;
}

/*
Aufgabe 1c:
Lesen Sie die Implementierungen der Turtlecanvas-Funktionen weiter unten in der "turtlecanvas.h".
Der Quellcode sollte vollständig verständlich und unüberraschend sein.
Hinweis: Diese Aufgabe wird nicht bewertet.
*/

/*
Aufgabe 2a:
Geben Sie einen Pointer auf das erste Vorkommen der größten Zahl im Eingabearray zurück.
*/
uint16_t *find_maximal_number(uint16_t numbers[], size_t numbers_len) {

    if (numbers_len == 0)                                           // Prüfen ob das Array Leer ist, falls der Fall wird NULL zurückgegeben
    {                                                               // problem kann zu segmentation fault (ungültiger speicherzugriffsfehler) führen
        //return NULL;                   // Auskommentiert wegen warning
    }

    uint16_t *arrayFirstMaxValue = &numbers[0];                     // Deklaration eines Pointers der die Adresse des ersten Arrayelements (an Stelle 0) speichert

    for (int i = 0; i < numbers_len; i++)                           // Durchlauf aller Arrayelemente (Strikt kleiner als weil Array-Stellen mit null beginnen)
    {
        if (numbers[i] > *arrayFirstMaxValue)                       // Prüfen ob das aktuell zu prüfende Element (an stelle i) Strikt größer ist (um _das erste_ größte element zu finden)
        {                                                           // als das Element aus das der Pointer "arrayFirstMax" zeigt
            arrayFirstMaxValue = &numbers[i];                       // Speichere im Pointer "arrayFirstMax" _die Adresse_ des numbers Element an Stelle i
        }
        
    }

    return arrayFirstMaxValue;                                      // Gib den Pointer zurück
}

/*
Aufgabe 2b:
Geben Sie (einen Pointer auf) das Teilarray zurück, welches ab dem ersten Vorkommen der größten Zahl im Eingabearray beginnt.
*/
uint16_t *find_subarray_starting_at_maximal_number(uint16_t numbers[], size_t numbers_len) {

    if (numbers_len == 0)                                                   // Prüfen ob das Array Leer ist, falls der Fall wird NULL zurückgegeben
    {                                                                       // problem kann zu segmentation fault (ungültiger speicherzugriffsfehler) führen
        //return NULL;                 // Auskommentiert wegen warning
    }

    uint16_t *arrayFromMaxNum = find_maximal_number(numbers, numbers_len);  // Erstelle einen Pointer und speichere in ihm die die Adresse des größten Werts im Array

    return arrayFromMaxNum;                                                 // Gebe die Adresse die in arrayFromMaxNum gespeichert ist zurück
}

/*
Aufgabe 2c:
Geben Sie die größtmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die größte Distanz die zwischen 1 und 7, und beträgt damit `6`.
*/

int16_t find_smallest_number(uint16_t numbers[], size_t numbers_len) {          // Definition einer Hilfsfunktion die die kleinste Zahl aus einem Array zurüch gibt

    if (numbers_len == 0)                                                       // Prüfen ob das Array Leer ist, falls der Fall wird NULL zurückgegeben
    {                                                                           // problem kann zu segmentation fault (ungültiger speicherzugriffsfehler) führen
        //return NULL;                   // Auskommentiert wegen warning
    }

    int16_t arrayMinValue = numbers[0];                                         // Nimmt an die kleinste Zahl innerhalb des Arrays sei die Zahl an der stelle 0

    for (int i = 0; i < numbers_len; i++)                                       // Geht das gesamte Array durch und sucht nach der kleinsten Zahl
    {
        if (numbers[i] < arrayMinValue)                                         // Indem die Zahl die bis jetzt am kleinsten ist mit der aktuellen Zahl im array verglchen wird
        {                                                                      
            arrayMinValue = numbers[i];                                        
        }
        
    }

    return arrayMinValue;                                                       // Gibt die kleinste Zahl aus dem Array zurück
}

int16_t find_largest_number(uint16_t numbers[], size_t numbers_len) {           // Definition einer Hilfsfunktion die die kleinste Zahl aus einem Array zurüch gibt

    if (numbers_len == 0)                                                       // Prüfen ob das Array Leer ist, falls der Fall wird NULL zurückgegeben
    {                                                                           // problem kann zu segmentation fault (ungültiger speicherzugriffsfehler) führen
        //return NULL;                   // Auskommentiert wegen warning
    }

    int16_t arrayMaxValue = numbers[0];                                         // Nimmt an die größte Zahl im Array ist die an der stelle 0

    for (int i = 0; i < numbers_len; i++)                                       // Get das gesamte Array durch und sucht nach der größten Zahl
    {
        if (numbers[i] > arrayMaxValue)                                         // Indem die Zhal die bis jetzt am Größten ist mt der aktuellen Zahl verglichen wird
        {                                                                      
            arrayMaxValue = numbers[i];                                        
        }
        
    }

    return arrayMaxValue;                                                       // Gibt die kleinste Zahl aus dem Array zurück
}


uint16_t find_maximum_distance(uint16_t numbers[], size_t numbers_len) {

    if (numbers_len == 0)                                                       // Prüfen ob das Array Leer ist, falls der Fall wird NULL zurückgegeben
    {                                                                           // problem kann zu segmentation fault (ungültiger speicherzugriffsfehler) führen
        //return NULL;                   // Auskommentiert wegen warning
    }

    return find_largest_number(numbers, numbers_len) - find_smallest_number(numbers, numbers_len);
    
}

/*
Aufgabe 2d:
Geben Sie die kleinstmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die kleinste Distanz die zwischen 3 und 4, und beträgt damit `1`.
*/
uint16_t find_minimum_distance(uint16_t numbers[], size_t numbers_len) {
    
    if (numbers_len == 0)                                                       // Prüfen ob das Array Leer ist, falls der Fall wird NULL zurückgegeben
    {                                                                           // problem kann zu segmentation fault (ungültiger speicherzugriffsfehler) führen
        //return NULL;                   // Auskommentiert wegen warning
    }

    uint16_t grossteZahl = find_largest_number(numbers, numbers_len);
    uint16_t minimumDistance = grossteZahl;

    for (size_t i = 0; i < numbers_len; i++)                                    // Vergleiche jeden Wert
    {
        for (size_t j = i + 1; j < numbers_len; j++)                            // Mit jedem Wert
        {
            if (numbers[i] == numbers[j])                                       // wenn zwei Werte gleich sind
            {
                return 0;                                                       // Gebe 0 aus (da der Abstand 0 ist)
            }

            uint16_t abstandIJ;                                                 // Zwischenspeichervariable für den Abstand von I ind J

            if (numbers[i] > numbers[j])                                        // Jeh nach dem welche Zahl größer ist wird der Abstand ermittelt
            {                                                                   // dies vermeidet negative Abstände als kleinste Abstände
                abstandIJ = numbers[i] - numbers[j];
            } else
            {
                abstandIJ = numbers[j] - numbers[i];
            }

            if (abstandIJ < minimumDistance) {                                  // Falls der momentan ermittelte Abstand (abstandIJ) kleiner ist als der bisher ermittelte kleinste Abstand

                minimumDistance = abstandIJ;                                    // wird der kleinste Abstand neu gespeichert
            }
                        
        }
    }

    return minimumDistance;                                                     // Rückgabe des kleinsten Abstands
}

/*
Aufgabe 2e:
Schreiben Sie die ersten `numbers_len` Quadratzahlen aufsteigend in das gegebene Array `numbers`.
Hinweis: Wir starten bei `1`. Sollte numbers_len also `5` sein, sind die ersten 5 Quadratzahlen bis
einschließlich die von 5 gemeint: 1, 4, 9, 16, 25.
*/
int quadratVon (int x) {                                                    // Ja, unnötig aber Hilfsfunktion die das Quadrat von x ausrechet
    x = x * x;
    return x;
}


void square_ascending(uint16_t numbers[], size_t numbers_len) {

    for (int i = 0; i < numbers_len; i++)                                   // rechnet für jede stelle des Arrays
    {
        numbers[i] = quadratVon(i+1);                                       // eine neue Quadratzahl aus
    }
    
    return;
}

/*
Aufgabe 2f:
Füllen Sie das Array `out` mit den aufsteigend sortierten Zahlen aus dem `in` Array. Beide Arrays haben die Länge `len`.
Beispiel: Ist `in` {1, 4, 3, 7, 4}, so soll `out` am Ende {1, 3, 4, 4, 7} sein.
*/

void swapElements(uint16_t *x, uint16_t *y) {                           // Definition einer Hilfsfunktion die Elemente Eines Arrays Tauscht

    uint16_t temp = *x;                                                 // Nimmt das eine Element und speichert es in einer Zwischenvariable
    *x = *y;                                                            // Tauscht die Elemente
    *y = temp;                                                          // aus der Zwischenvariable

}                                                                       // Gibt keinen Wert zurück (void) da die Funktion mit Adressen arbeitet


void sort_ascending(uint16_t in[], uint16_t out[], size_t len) {

    for (size_t i = 0; i < len - 1; i++) {                              // Für die Länge des Arraya, bzw. für jedes Arrayelement

        for (size_t bubble = 0; bubble < len - 1 - i; bubble++) {       // Gehe für jedes Element des Arrays davon aus das es die Nächste Bubble ist

            if (in[bubble] > in[bubble + 1]) {                          // Da das Array aufsteigend sortiert werden soll muss geprüft werden ob das aktuelle Element            
                                                                        // weiter als bubble aufsteigen soll oder das nächste Element im Array als bubble weiter aufsteigt
                swapElements(&in[bubble], &in[bubble + 1]);             // Falls dies der Fall wird Die Hiflfsfunktion swap Elements aufgerufen
            }
        }
    }

    for (size_t i = 0; i < len; i++)                                    // Für alle Elemente des Arrays  
    {
        out[i] = in[i];                                                 // Tausche die Elemente des ersten Arrays mit den Elementen des zweiten Arrays
    }

}






/*

                ,'\   |\
               / /.:  ;;
              / :'|| //
             (| | ||;'
             / ||,;'-.._
            : ,;,`';:.--`
            |:|'`-(\\
            ::: \-'\`'
             \\\ \,-`.
              `'\ `.,-`-._      ,-._
       ,-.       \  `.,-' `-.  / ,..`.
      / ,.`.      `.  \ _.-' \',: ``\ \
     / / :..`-'''``-)  `.   _.:''  ''\ \
    : :  '' `-..''`/    |-''  |''  '' \ \
    | |  ''   ''  :     |__..-;''  ''  : :
    | |  ''   ''  |     ;    / ''  ''  | |
    | |  ''   ''  ;    /--../_ ''_ '' _| |
    | |  ''  _;:_/    :._  /-.'',-.'',-. |
    : :  '',;'`;/     |_ ,(   `'   `'   \|
     \ \  \(   /\     :,'  \
      \ \.'/  : /    ,)    /
       \ ':   ':    / \   :
        `.\    :   :\  \  |
                \  | `. \ |..-_
                 ) |.  `/___-.-`
               ,'  -.'.  `. `'        _,)
               \'\(`.\ `._ `-..___..-','
           FLX    `'      ``-..___..-'


*/
