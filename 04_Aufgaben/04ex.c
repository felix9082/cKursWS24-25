/*
Willkommen zum vierten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es darum, ein komplizierteres Problem wiederholt in Teilprobleme zu zerlegen.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 04ex_test.c 04ex_helpers.c -o 04ex_test.o -lm && ./04ex_test.o
*/

#include "04_canvas.h"
#include "04ex_helpers.h"
#include <stdio.h>

/*
Aufgabe 1a:
In diesem Aufgabenblatt schreiben wir eine Funktion, um auf der Canvas gefüllte Kreise zu zeichnen. Kreise sind konzeptionell einfach:
Haben wir einen Mittelpunkt und einen Radius, können wir alle Punkte schwarz färben, deren Distanz zum
Mittelpunkt kleiner oder gleich des Radius ist.

Für diese Aufgabe, implementieren Sie eine Funktion die genau das tut. Gegeben sind die Koordinaten `x` und `y` des
Mittelpixels und ein Radius. Nun sollen alle Pixel, die innerhalb der Distanz um diesen Mittelpixel liegen schwarz
gefärbt werden. Durch diese Methode entstehen immer Kreise mit ungeradem Durchmesser, da wir mit diskreten Pixeln arbeiten.
Der Mittelpixel hat eine Distanz von 0 zu sich selbst, und daher muss er immer schwarz gefärbt werden, selbst bei Radius 0.
Nutzen Sie für die Distanzbestimmung die `distance` Funktion aus `04ex_helpers.h`.
Headerfile und die zugehörige Implementierung sind bereits eingebunden, die Funktion kann
also einfach verwendet werden.
*/
Canvas draw_odd_circle(Canvas c, int x, int y, int radius_from_middle) {

    int b = 0;                                                          // Definition und initialisierung einer Breiten
    int h = 0;                                                          // und höhenvariable

    while (b < canvas_width(c))                                         // Durchlauf aller Breitenpixel
    {
        while (h < canvas_height(c))                                    // Durchlauf aller Höhenlixel
        {
            if (distance(x, y, b, h) <= radius_from_middle)             // Implementioerung der "odd_circle-Bedingung"
            {
                canvas_set_black(c, b, h);                              // Einfärbung des entsprechechenden Pixels
            }
                        
            h++;                                                        // Inkrementierung des "Höhentrackers"
        }
        h = 0;                                                          // Zurücksetzten des "Höhentrackers"
        b++;                                                            // Inkrementierung des "Breitentrackers"
    }    

    return c;
}

/*
Aufgabe 1b:
Implementieren Sie nun selbst eine Funktion, welche die abgerundete Distanz zwischen zwei Punkten (`x0`, `y0`)
und (`x1`, `y1`) berechnet.
Sei `a := x1 - x0` und `b := y1 - y0`. Dann liefert uns der Satz des Pythagoras die Distanz zwischen den Punkten als
`c := quadratwurzel(a^2 + b^2)`.
Die Datei `04ex_helpers.h` mit den Hilsfunktionen enthält eine Funktion `squareroot`. Nutzen Sie diese Funktion, um die
Distanz zu berechnen.
*/
int my_distance(int x0, int y0, int x1, int y1) {
    
    int a = x1 - x0;                                        // Diese Funktion Führt die in der aufgabenstellung beschriebenen
    int b = y1 - y0;                                        // Operationen exakt und in gegebener Reihnfolge algorithmisch aus

    a = a * a;
    b = b * b;

    int distance = squareroot(a + b); 

    return distance;
}

/*
Aufgabe 1c:
Implementieren Sie nun selbst die Berechnung der abgerundeten Quadratwurzel von `n`.
Tipp: Finden Sie die größte natürliche Zahl, deren Quadrat kleiner oder gleich `n` ist. Es muss nicht effizient sein, wir
testen nur mit relativ kleinen Zahlen.
*/
int my_squareroot(int n) {

    int x = 0;                     // Definition und initialisierung der gesuchten Wurtzel

    while (x * x < n)              // Suche nach der Wurtzel
    {
        x++;                
    }

    if (x * x > n)                 // Da nach der abgerundeteten Wutzzel gesucht wird muss geprüft werden ob x nicht zu weit "Über das ziel hinausgeschossen ist"
    {
        x--;
    }
    
    return x;                      // Rückgabe der gesuchten Wurtzel
}

/*
Aufgabe 1d:
Die Kreisfunktion aus Aufgabe 1a erstellt immer nur Kreise mit ungeradem Durchmesser. Kreise mit einem
geraden Durchmesser haben keinen einzelnen Mittelpixel, demnach benötigen wir eine flexiblere Kreis-Zeichnungs Funktion
mit anderen Parametern, um diese Kreise zeichnen zu können.
`x` ist die x-Koordinate der linkesten Pixel des Kreises, `y` ist die y-koordinate der untersten Pixel des Kreises,
`diameter` ist der Durchmesser. Dadurch ist `(x,y)` die Koordinate der unteren linken Ecke des kleinsten Quadrats (der
Länge und Breite `diameter`) welches den erwünschten Kreis vollständig enthält.

Um Kreise mit _ungeradem_ Durchmesser zu erstellen, können Sie einfach Ihre `draw_odd_circle` Funktion ein mal aufrufen.
Für Kreise mit _geradem_ Durchmesser rufen Sie Ihre `draw_odd_circle` vier mal auf: Einmal für jeden der vier Pixel
welche den exakten Mittelpunkt des erwünschten Kreises umgeben.
*/
Canvas draw_circle(Canvas c, int x, int y, int diameter) {

    int xMid = x + (diameter / 2);                              // Berechnung des Mittelpunkt des Kreises (x-Koordinate)
    int yMid = y + (diameter / 2);                              // Berechnung des Mittelpunkt des Kreises (y-Koordinate)

    int radius = diameter / 2;                                  // Berechnung des Kreisradiusses

    if (diameter % 2 != 0)                                      // Abfrage nach geradem oder ungeradem Durchmesser
    {
        draw_odd_circle(c, xMid, yMid, radius);                 // Bei ungeradem Durchmesser wird "draw_odd_circle" aufgerufen
    }
    else
    {
        
        draw_odd_circle(c, xMid, yMid, radius-1);               // Durch das minimieren des Kreisradius um 1 wird der Kreisradius
        draw_odd_circle(c, xMid-1, yMid, radius-1);             // ungerade und kann mit der "draw_odd_circle" Funktion vier mal
        draw_odd_circle(c, xMid, yMid -1, radius-1);            // überlappend gezeichnet werden und so einen Kreis mit geradem
        draw_odd_circle(c, xMid-1, yMid-1, radius-1);           // Durchmesser auf das Cancas zeichen
        
    }

    return c;
}

/*
Aufgabe 1e:
Dadurch, dass Sie das Problem in kleinere Subprobleme geteilt haben, haben Sie gerade eine vollständige Funktion zum
Kreisezeichnen implementiert. Das ist ziemlich cool!
Geben Sie zur Feier `5` zurück.
*/
int high_five() {

    /*        
                                                    :::!~!!!!!:.
                                                .xUHWH!! !!?M88WHX:.
                                                .X*#M@$!!  !X!M$$$$$$WWx:.
                                            :!!!!!!?H! :!$!$$$$$$$$$$8X:
                                            !!~  ~:~!! :~!$!#$$$$$$$$$$8X:
                                            :!~::!H!<   ~.U$X!?R$$$$$$$$MM!
                                            ~!~!!!!~~ .:XW$$$U!!?$$$$$$RMM!
                                            !:~~~ .:!M"T#$$$$WX??#MRRMMM!
                                            ~?WuxiW*`   `"#$$$$8!!!!??!!!
                                            :X- M$$$$       `"T#$T~!8$WUXU~
                                            :%`  ~#$$$m:        ~!~ ?$$$$$$
                                        :!`.-   ~T$$$$8xx.  .xWW- ~""##*"
                                .....   -~~:<` !    ~?T#$$@@W@*?$$      /`
                                W$@@M!!! .!~~ !!     .:XUW$W!~ `"~:    :
                                #"~~`.:x%`!!  !H:   !WM$$$$Ti.: .!WUn+!`
                                :::~:!!`:X~ .: ?H.!u "$$$B$$$!W:U!T$$M~
                                .~~   :X@!.-~   ?@WTWo("*$$$W$TH$! `
                                Wi.~!X$?!-~    : ?$$$B$Wu("**$RM!
                                $R@i.~~ !     :   ~$$$$$B$$en:``
                                ?MXT@Wx.~    :     ~"##*$$$$M~

        ▄█    █▄     ▄█     ▄██████▄     ▄█    █▄            ▄████████  ▄█   ▄█    █▄     ▄████████ 
        ███    ███   ███    ███    ███   ███    ███          ███    ███ ███  ███    ███   ███    ███ 
        ███    ███   ███▌   ███    █▀    ███    ███          ███    █▀  ███▌ ███    ███   ███    █▀  
       ▄███▄▄▄▄███▄▄ ███▌  ▄███         ▄███▄▄▄▄███▄▄       ▄███▄▄▄     ███▌ ███    ███  ▄███▄▄▄     
      ▀▀███▀▀▀▀███▀  ███▌ ▀▀███ ████▄  ▀▀███▀▀▀▀███▀       ▀▀███▀▀▀     ███▌ ███    ███ ▀▀███▀▀▀     
        ███    ███   ███    ███    ███   ███    ███          ███        ███  ███    ███   ███    █▄  
        ███    ███   ███    ███    ███   ███    ███          ███        ███  ███    ███   ███    ███ 
        ███    █▀    █▀     ████████▀    ███    █▀           ███        █▀    ▀██████▀    ██████████ 
    */

    return 5;
}

/*
Aufgabe 2a:
Gegeben sei eine natürliche Zahl `n`. Falls sie gerade ist, teilen Sie sie durch zwei, ansonsten multiplizieren Sie sie
mit drei und addieren eins. Wiederholen Sie dies bis Sie als Ergebnis die Zahl `1` erreichen. Die Anzahl Wiederholungen
die Sie dafür benötigen ist die _Hailstone-Zahl von `n`_.
Zum Beispiel `hailstone(1) == 0`, `hailstone(4) == 2` (4 -> 2 -> 1), und `hailstone(5) == 5` (5 -> 16 -> 8 -> 4 -> 2 -> 1).
Berechnen Sie die Hailstone-Zahl vom Parameter `n`.
*/
int hailstone(int n) {

    int hailstone = 0;              // Hailstone Trackervariable
    int i = n;                      // Die zu prüfende Zahl (mit ihr wird gerechnet, könnte wahrscheinlich auch mit n gemacht werden)

    while (i != 1)                  // Schleife die die Hailstonezahl bis zum erreichen der 1 berechnet
    {
        if (i % 2 == 0)             // Falls i gerae:
        {
            i = i / 2;              // Teile durch zwei
            hailstone++;            // und inkrementiere den Hailstone-Counter
        }
        else                        
        {
            i = i * 3;              // sont multipliziere i um 1,
            i++;                    // addiere 1
            hailstone++;            // und inkrementiere den Hailstone-Counter
        }

    }
    
    // Diese Funktion wurde mit verschiedenen werten getestet und mit einem Hailstone Calculator abgeglichen
    // https://goodcalculators.com/collatz-conjecture-calculator/ Letzter Zugriff: FR 18/Okt/2024 13:09 Uhr

    return hailstone;

}


/*
Aufgabe 2b:
Unser Testrunner hat keine Tests für Aufgabe 2a. Falls Sie Ihre Lösung selber testen wollen, erstellen Sie am besten
eine separate C-Datei wo Sie Ihre Lösung hineinkopieren und gegen einige Beispielwerte testen.
Falls Sie keine Beispielwerte von Hand berechnen wollen, schauen Sie am besten hier nach:  https://oeis.org/A006577

Für die _Bewertung_ von diesem Aufgabenblatt lassen wir Tests für Aufgabe 2a laufen, zum Debuggen müssen Sie
allerdings Ihre eigenen Tests schreiben.
Lassen Sie `99` von dieser Funktion zurückgeben um zu zeigen, dass Sie das verstanden haben.
*/
int bring_your_own_tests() {
    return 99;
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
