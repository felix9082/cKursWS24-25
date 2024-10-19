/*
Willkommen zum fünften Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Rekursion.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o
*/

#include "05_canvas.h"
#include <stdio.h>
#include <math.h>

/*
Aufgabe 1a:
Zeichnen Sie eine horizontale Linie der Länge `width`, deren am weitesten links liegender Pixel bei `(x, y)` ist.

_Benutzen Sie keine Schleifen - Die Aufgabe soll über Rekursion gelöst werden!_

*/
Canvas recursive_line(Canvas c, int x, int y, int width) {
    
    if (width == 0)                                             // Definieren und Prüfen ob Abbruchbedingung erfüllt
    {
        return c;                                               // Wenn Rekursionsanker greift: Canvasrückgabe
    }

    if (x >= 0 && x < canvas_width(c))                          // Validitäts-/Existensprüfung des aktuellen Pixels
    {
        canvas_set_black(c, x, y);                              // Einfärbung des Aktuellen Pixels
    }
    
    return recursive_line(c, x + 1, y, width - 1);              // Rekursiver Aufruf
}

/*
Aufgabe 1b:
Zeichnen Sie ein Rechteck mit der Breite `width` und der Höhe `height`. Der Pixel der linken unteren Ecke liegt bei `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas recursive_rectangle(Canvas c, int x, int y, int width, int height) {

    if (height == 0)                                            // Definition und Prüfung der Abbruchbedingung
    {
        return c;                                               // Wenn Rekursionsanker greift: Canvasrückgabe
    }

    if (y >= 0 && y < canvas_height(c))                         // Validitäts-/Existensprüfung der aktuellen Höhenkoordinate
    {
        recursive_line(c, x, y, width);                         // Bei valider Prüfung wird pro Pixelreihe (Höhenkoordinate) 
    }                                                           // die Funktion "recursive_line" mit entsprechenden Parametern ausgeführt

    return recursive_rectangle(c, x, y + 1, width, height-1);   // Rekursiver Aufruf

}

/*
Aufgabe 2:
Die Fibonaccizahlen sind wie folgt definiert:

- die nullte Fibonaccizahl ist 1,
- die erste Fibonaccizahl ist ebenfalls 1, und
- jede weitere Fibonaccizahl ist die Summe der zwei vorigen Fibonaccizahlen.

Berechne die `n`-te Fibonaccizahl.
*/
int fibonacci(int n) {

    if (n == 0)                                         // Rekursionsanker greift bei "nullter Fibonacci Zahl"
    {
        return 1;
    }
    else if (n == 1)                                    // Rekursiver Anker greift bei "erster Fibonacci Zahl"
    {
        return 1;
    }
    
    return fibonacci(n - 1) + fibonacci(n - 2);         // Rekursiver Aufruf, Definition der Fibonacci Zahl

}

/*
Aufgabe 3:
Implementieren Sie einen schwarzen Fülleimer. Gegeben eine Koordinate `(x, y)` auf einer (bereits bemalten) Canvas, soll die komplette
zusammenhängende Fläche aller Pixel der selben Farbe (schwarz oder weiß) schwarz gefärbt werden.
Zwei Pixel sind Teil der selben Fläche wenn sie die selbe Farbe haben und direkt benachbart sind. Jeder Pixel hat bis
zu vier direkte Nachbarn - die Diagonalen zählen nicht.

Funktionen, um die Farbe eines Pixels auf der Canvas zu bestimmen, sind im Headerfile der Canvas dokumentiert.
*/

Canvas bucket_fill(Canvas c, int x, int y) {

    if (x >= 0 && x < canvas_width(c) && y >= 0 && y < canvas_height(c))            // Existens-/Validitätsprüfung des aktuellen Pixels
    {
        if (pixel_is_white(c , x, y) == 1)                                          // Wenn Pixel schwarz (Rekursionsanker)
        {
            canvas_set_black(c, x, y);                                              // Einfärben des Aktuellen Pixels

            bucket_fill(c, x + 1, y);                                               // Rekursiver Aufruf für den rechten Nachbarpixel
            bucket_fill(c, x - 1, y);                                               // Rekursiver Aufruf für den linken Nachbarpixel
            bucket_fill(c, x, y - 1);                                               // Rekursiver Aufruf für den oberen Nachbarpixel
            bucket_fill(c, x, y + 1);                                               // Rekursiver Aufruf für den unteren Nachbarpixel
                        
        }
        
    }

    return c;                                                                       // Canvasrückgabe
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
