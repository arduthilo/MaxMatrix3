
#include <MaxMatrix3.h>

const byte dataIn = 3;
const byte load = 4;
const byte clock = 5;
const byte maxInUse = 4; //number of adressed displays, Anzahl der adressierten Displays

MaxMatrix3 m(dataIn, load, clock, maxInUse);


void setup()
{
  m.init();
}

void loop()
{
  for(int y=0;y<8;y++) //counts rows, Zaehler fuer die Zeilen
    for(int x=0;x<8*maxInUse;x++)
    {
      m.setDot(x,y,1);  //switch point on, Punkt einschalten
      delay(50);	//short delay, kurz warten
    }
  for(int y=0;y<8;y++) //counts rows, Zaehler fuer die Zeilen
    for(int x=0;x<8*maxInUse;x++)
    {
      m.setDot(x,y,0);  //switch point off, Punkt ausschalten
      delay(50);	//short delay, kurz warten
    }
}

