/*
Willkommen zum dritten Aufgabenblatt vom Programmierkurs. Auf diesem Aufgabenblatt geht es um folgende neue Konzepte:

- Aufrufen von Funktionen
- Definieren von Funktionen

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 03ex_test.c -o 03ex_test.o -lm && ./03ex_test.o
*/

/* Die folgenden Zeilen enthalten einige C-Notwendigkeiten die Sie momentan ignorieren können. */
#include "03_canvas.h"
#include <stdio.h> 
/* Hier enden die Dinge, die Sie ignorieren können */

/*
Der folgende Code ist ein Beispiel für eine Funktionsdefinition. Die Funktion gibt `1` zurück falls `n` ein
ganzzahliges Vielfaches von `k` ist, und `0` falls nicht.
Innerhalb dieses Aufgabenblattes können Sie diese Funktion frei verwenden. Ein Funktionsaufruf könnte zum Beispiel
`is_multiple_of(n, 2)` sein. Dieser gäbe `1` zurück wenn `n` gerade ist, und `0` wenn `n` ungerade ist.

Für dieses und alle weiteren Aufgabenblätter animieren wir Sie, selbstständig Funktionen zu schreiben um Teilprobleme zu lösen.
Sie können zum Beispiel `is_multiple_of` in mehreren Aufgaben auf diesem Blatt verwenden. Wenn wir die nicht vordefiniert hätten, 
hätte es sich für Sie gelohnt, sie selbst zu definieren.
Teilprobleme zu identifizieren und losgelöst vom ursprünglichen Kontext als Hilfsfunktion zu implementierem ist
ein großer Teil von kompetentem Programmieren.
*/
int is_multiple_of(int n, int k) {
    int remainder = n % k;
    return remainder == 0;
}

/*
Aufgabe 1a:

Geben Sie in dieser Funktion die Summe der ersten `n` natürlichen Zahlen (exklusive der Null) zurück, die durch `m` teilbar sind.
*/
int sum_of_divisibles(int n, int m) {

    int sod = 0;                                        // deklariere Variable Sum Of Divisibles (wird zurückgegebebn)
    int z = 1;                                          // die aktuell zu prüfende Zahl (beginnt bei 1 "exklusive der null")
    int i = 0;                                          // speichert die Menge an bereits gefundenen addierten Zahlen

    while(i < n)                                        // Bedingung: Wurden schon 'n' Zahlen gefunden?
    {
        if (z % m == 0)                                 // Prüfung ob teilbar
        {
            sod = sod + z;                              // Addition "Sum of divisibles"
            i++;                                        // Inkrementierung der Variable die die ersten n gefundenen Zahlen trackt
        }
        z++;                                            // Inkrementierung der zu prüfenden Zahl
    }
    
    return sod;                                         // Rückgabe des Wertes
}

/*
Aufgabe 1b:

Geben Sie in dieser Funktion die Summe der ersten `n` natürlichen Zahlen (exklusive der Null) zurück, die durch `l` und durch `m` teilbar sind.
*/

int sum_of_doubly_divisibles(int n, int l, int m) {

    int summeN = 0;                                     // Summe der ersten n Zahlen...
    int bgz = 0;                                        // Menge an bereits gefundenen Zahlen
    int zpz = 1;                                        // Momentan zu prüfende Zahl

    while (bgz < n)                                     // Solange noch nicht n zahlen gefunden wurden
    {
        if (zpz % l == 0)                               // Prüfe ob die zu prüfende Zashl durch l teilbar ist
        {
            if (zpz % m == 0)                           // Prüfe ob die zu prüfende Zashl durch m teilbar ist
            {
                summeN = summeN + zpz;                  // Wenn beide bedingungen erfüllt: Addiere die geprüfte Zahl zur Summe der ersten n Zahlen...
                bgz++;                                  // und inkrementiere die Menge der Bereits gefundenen Zahlen um 1
            }
            
        }
        zpz++;                                          // inkrementiere die zu prüfende Zahl um 1 (schaue nach der Nächsten Zahl
    }   

    return summeN; 
}

/*
Aufgabe 2a:
Die folgenden Aufgaben (und auch weitere Aufgaben auf den kommenden Aufgabenblättern) erlauben es Ihnen,
einfache Grafiken zu erstellen.
In dieser Funktion starten wir mit einer komplett weißen "Canvas" (deutsch: "Leinwand") `c` und färben bestimmte Pixel schwarz.
Die Canvas ist ein zweidimensionales Raster aus Pixeln, ein einfaches, mit Code bearbeitbares Bild.
Dank der bereitgestellten Funktionen brauchen Sie nicht verstehen, wie der Computer Bilder repräsentiert. Sie müssen nur wissen,
wie Sie die Funktion `canvas_set_black` aufrufen, um die Canvas zu manipulieren.
*/
Canvas first_canvas_exercise(Canvas c) {
    /*
    Die `canvas_set_black` Funktion bekommt drei Parameter. Eine Canvas, sowie eine
    x-Koordinate und eine y-Koordinate innerhalb dieser Canvas.
    Die linke untere Ecke der Canvas ist der Koordinatenursprung, dort sind die x- und die y-Koordinate jeweils `0`.
    Nach rechts steigen die x-Koordinaten, nach oben die y-Koordinaten.
    */
    c = canvas_set_black(c, 1, 5);
    c = canvas_set_black(c, 2, 1);
    c = canvas_set_black(c, 13, 4);

    /*
    Diese drei Funktionsaufrufe hier drüber färben drei unterschiedliche Pixel der Canvas schwarz.
    Versuchen Sie sich vorzustellen, wo diese drei Pixel gemäß unseres Koordinatensystems sein sollten.

    Führen Sie jetzt den Test für diese Aufgabe aus, indem Sie diesen Befehl nutzen:
    clang -std=c11 -g -Wall 03ex_test.c -o 03ex_test.o -lm && ./03ex_test.o first_canvas_exercise

    Der Test wird fehlschlagen, da wir drei leicht andere Pixel-Positionen schwarz gefärbt haben wollen. Schauen Sie sich
    die Test-Ausgabe an. Diese sollte Sie darüber informieren, dass ein Bild in einem "Feedback" Verzeichnis (im aktuellen Verzeichnis)
    gespeichert wurde, welches Ihnen die Abweichung darstellt.
    Öffnen Sie das Bild (eventuell müssen Sie etwas hineinzoomen, es ist recht klein).
    Das Bild ist in drei Segmente unterteilt. Zuerst das Bild welches Sie erstellt haben,
    dann das erwartete Bild, und als drittes eine Visualisierung
    welche Pixel in ihrer Farbe vom erwarteten Bild abweichen.

    Nutzen Sie diese Visualisierung, um die drei Funktionsaufrufe oben so zu verändern, dass Ihr Bild und das erwartete
    Bild übereinstimmen. Sie können den Test beliebig oft ausführen, um neue Feedback-Bilder zu erzeugen.

    Desweiteren existiert die `canvas_save_debug(Canvas c)` Funktion. Dieser können Sie jederzeit eine Canvas übergeben,
    um sie als Bild abzuspeichern. Die Bilder erscheinen im "Debug" Ordner und sind
    aufsteigend nummeriert, falls Sie für eine Canvas die Funktion mehrfach aufrufen. Probieren Sie die Funktion doch
    ein paar mal mit dem Canvas in dieser Aufgabe aus, zum Beispiel jedes mal nachdem ein Pixel gesetzt wurde!

    Sobald der Test erfolgreich ist, verschwindet das Feedback. Anstelle dessen können sie Ihre erfolgreiche Lösung
    im "Success" Ordner bestaunen :). Dies gilt genauso für alle weiteren Canvas-Aufgaben!
    */

    return c;
}

/*
Aufgabe 2b:
In dieser Aufgabe sollen Sie die vier Ecken der Canvas schwarz färben.
Dafür benötigen sie die Höhe und Breite einer gegebenen Canvas.
Um die Höhe und Breite herauszufinden können (und müssen) sie die `canvas_width` und `canvas_height` Funktionen nutzen. Diesen
Funktionen übergeben Sie eine Canvas (so: `canvas_width(c)` und `canvas_height(c)`) und bekommen dann jeweils
die Breite und Höhe zurückgegeben.
Hinweis: Koordinaten beginnen bei `0`, nicht bei `1`.
*/
Canvas color_corners(Canvas c) {

    canvas_set_black(c, 0, 0);                                      // unten links
    canvas_set_black(c, 0, canvas_height(c)-1);                     // oben links
    canvas_set_black(c, canvas_width(c)-1, 0);                      // unten rechts
    canvas_set_black(c, canvas_width(c)-1, canvas_height(c)-1);     // oben rechts

    return c;
}

/*
Aufgabe 2c:
Färben Sie alle Pixel der Canvas schwarz.
*/
Canvas paint_it_black(Canvas c) {

    for (int y = 0; y < canvas_height(c); y++)                      // durchlaufe alle existierenden y Koordinaten
    {
        for (int x = 0; x < canvas_width(c); x++)                   // durchlaufe alle existierenden x Koordinaten
        {
            canvas_set_black(c, x, y);                              // Färbe den Aktuellen Pixel schwarz ein
        }
        
    }
    

    return c;
}

/*
Aufgabe 2d:
Färben Sie den ersten Pixel der ersten Reihe von oben schwarz, dann die ersten beiden Pixel der zweiten Reihe, die
ersten drei der dritten Reihe und so weiter (falls das unklar war, führen Sie einfach den Test aus
und schauen sich das erwartete Ergebnis an).
Falls eine Reihe nicht breit genug ist, färben Sie alle Pixel dieser Reihe schwarz.
*/
Canvas descending_diagonal(Canvas c) {
    
    for (int y = canvas_height(c)-1; y >= 0; y--)                           // Durchläuft alle vertikalen Pixel
    {
        for (int x = 0; x < canvas_height(c)-y; x++)                        // Durchläuft alle horizontalen Pixel
        {
            if (x <= canvas_width(c)-1 && y <= canvas_height(c)-1)          // Überprüfung ob einzufärbender Pixel "Legal" ist
            {
                canvas_set_black(c, x, y);                                  // Einfärbung des aktuellen Pixeld (falls "Legal")
            }
            
        }
        
    }
    
    return c;
}

/*
Aufgabe 3a:
Diese Funktion soll ein gefülltes schwarzes Rechteck auf die Canvas zeichnen. Die obere linke Ecke des Rechtecks hat die
Koordinaten `(x, y)`. Die Breite des Rechtecks ist `width`, und die Höhe ist `height`. Falls das Rechteck nicht
auf die Canvas passt, sollen einfach die Teile ignoriert werden welche außerhalb liegen würden.
*/
Canvas draw_rectangle(Canvas c, int x, int y, int width, int height) {

    for (int yKoordinate = y; yKoordinate > 0 + y - height; yKoordinate--)          // Definition der einzufärbenden y Koordinate; Abbruchbedingung: Unterste Koordinate des Rechtecks erreicht              
    {
        for (int xKoordinate = x; xKoordinate < 0 + x + width; xKoordinate++)       // Definition der einzufärbenden x Koordinate; Abbruchbedingung; "Rechteste" Koordinate erreicht 
        {
            //Validitätsprüfung des einzufärbenden Pixels
            if (xKoordinate <= canvas_width(c)-1 && yKoordinate <= canvas_height(c)-1 && xKoordinate >= 0 && yKoordinate >= 0)
            {
            canvas_set_black(c, xKoordinate, yKoordinate);                          // Einfärbung der Koordinate unter legalitäts-(/existens)bedingung
            }

        }

    }    

    return c;
}

/*
Aufgabe 3b:
Diese Funktion soll ein gefülltes schwarzes Rechteck auf die Canvas zeichnen. Die obere linke Koordinate des Rechtecks
ist `(x0, y0)` und die untere rechte Koordinate ist `(x1, y1)`, und es gilt immer `x1 >= x0` und `y1 <= y0`.
Falls das Rechteck nicht auf die Canvas passt, sollen einfach die Teile ignoriert werden welche außerhalb liegen würden.

Tipp: Ob Sie diese Funktion von Grund auf implementieren oder `draw_rectangle` von Aufgabe 3a nutzen ist Ihnen überlassen.
Wir empfehlen beides auszuprobieren und selbst zu entscheiden welche Lösung Sie eleganter finden.
*/
Canvas draw_rectangle_via_corners(Canvas c, int x0, int y0, int x1, int y1) {
    
    int width = 0 - x0 + x1;                                                    // Berechnung der Rechtecksbreite mithilde neuer Parameter
    int height = 0 - y1 + y0;                                                   // Berechnung der Rechteckshöhe mithilfe neuer Parameter

    draw_rectangle(c, x0, y0, width + 1, height + 1);                           // Funktionsaufruf mit berechneten height- und width-parametern
    
    return c;
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
