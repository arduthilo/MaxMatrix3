Deutsche Uebersetzung siehe unten.

The MaxMatrix3 library enables the control of an LED matrix via the commonly used MAX7219 chip.

Connect the display to the Arduino. In my example programs the following pin assignment is selected, which can be changed at any time:
DIN Pin3
CS Pin4
CLK Pin5

GND GND
VCC 5V



The library MaxMatrix3 offers the possibility of compensating for different mounting positions and orientations by setting parameters.

The following procedure is recommended:
1. Load the example program Blink and change the value of the variable maxInUse to the number of 8x8 fields you have installed.
2. Load the program on the Arduino. Now, in the top line, a bright dot should run across the display from left to right.
3. If the run starts vertically, change the value behind m.flipAxis to 1.
4. If the run does not start with the left display, change the value after m.flipOrderDisplays to 1.
5. If the run does not start at the top, change the value after m.flipYOrientation to 1.
6. If the run does not start at the left margin, change the value after m.flipXOrientation to 1.




The library contains the following commands:

init ()
Starts the hardware.

clear ()
Turn off all points.

setDot (x.y.state)
Depending on the value of state, switches the point with the coordinates x and y on or off.

SetColumn (x, pattern)
Sets a pattern placed under pattern to the column of number x.

reload ()
This command brings the pattern stored in the Arduino to the display. As long as the variable autoReload is set, this happens automatically. When major changes are made to a pattern, it makes sense to set autoReload to 0 and, in turn, invoke reload () once all changes have been completed. See examples with text.

shift left (rotate)
shift right (rotate)
shiftup (rotate)
shift down (rotate)
Moves the content of the display one pixel in the specified direction. If the variable rotate is set, the content, which is pushed out of the display on one side, is inserted again on the other side.




Examples under File, Examples, Maxmatrix3
p01Blink A point passes through in the top line from left to right.
p02Fill Fills the display line by line and empties it again.
p03Rotate Creates a pattern on the display and moves it.
p04Counter Displays a number on the display and counts it up.
p05Text Places a text on the display.
p06TextWithScroll Places a text on the display that scrolls.
p07Trainer Simple trainer for multiplication.





﻿Die Library MaxMatrix3 ermöglicht die Ansteuerung einer LED-Matrix über den üblicherweise verbauten Chip MAX7219.

Verbinden Sie das Display mit dem Arduino. In meinen Beispielprogrammen ist folgende Pinbelegung gewählt, die sich aber jederzeit ändern lässt:
DIN	Pin3
CS	Pin4
CLK	Pin5

GND	GND
VCC	5V



Die Library MaxMatrix3 bietet die Möglichkeit, unterschiedliche Einbaulagen und Orientierungen durch das Setzen von Parametern auszugleichen.

Folgendes Vorgehen wird empfohlen:
1. Lade Sie das Beispielprogramm Blink und ändere den Wert der Variable maxInUse auf die Anzahl der bei Dir verbauten 8x8-Felder.
2. Lade das Programm auf den Arduino. Jetzt sollte in der obersten Zeile ein heller Punkt von links nach rechts über das Display laufen.
3. Falls der Lauf senkrecht startet, ändere den Wert hinter m.flipAxis auf 1.
4. Falls der Lauf nicht mit dem linken Display beginnt, ändere den Wert hinter m.flipOrderDisplays auf 1.
5. Falls der Lauf nicht am oberen Rand beginnt, ändere den Wert hinter m.flipYOrientation auf 1.
6. Falls der Lauf nicht am linken Rand beginnt, ändere den Wert hinter m.flipXOrientation auf 1.




Die Library enthält folgende Befehle:

init()
Startet die Hardware.

clear()
Schaltet alle Punkte aus.

setDot(x.y.state)
Schaltet je nach Wert von state den Punkt mit den Koordinaten x und y ein bzw. aus.

setColumn(x,pattern)
Setzt ein Muster, das unter pattern abgelegt ist, auf die Spalte der Nummer x.

reload()
Dieser Befehl bringt das im Arduino abgespeicherte Muster auf das Display. Solange die Variable autoReload gesetzt ist, passiert das automatisch. Werden größere Änderungen an einem Muster vorgenommen, ist es sinnvoll, autoReload auf 0 zu setzten und im Gegenzug reload() aufzurufen, sobald alle Änderungen abgeschlossen sind. Siehe Beispiele mit Text.

shiftLeft(rotate)
shiftRight(rotate)
shiftUp(rotate)
shiftDown(rotate)
Verschiebt den Inhalt des Displays um einen Pixel in die angegebene Richtung. Ist die Variable rotate gesetzt, wird der Inhalt, der auf der einen Seite aus dem Display geschoben wird, auf der anderen Seite wieder eingefügt.




Beispiele unter Datei, Beispiele, Maxmatrix3
p01Blink	Ein Punkt läuft in der obersten Zeile von links nach rechts durch.
p02Fill	Füllt das Display zeilenweise und leert es wieder.
p03Rotate	Erzeugt ein Muster auf dem Display und verschiebt es.
p04Counter	Zeigt eine Zahl auf dem Display an und zählt diese hoch.
p05Text	Setzt einen Text auf das Display
p06TextWithScroll	Setzt einen Text auf das Display, der scrollt.
p07Trainer	Einfacher Kopfrechentrainer
