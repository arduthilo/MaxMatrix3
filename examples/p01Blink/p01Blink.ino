
#include <MaxMatrix3.h>

const byte dataIn = 3;
const byte load = 4;
const byte clock = 5;
const byte maxInUse = 4; //number of adressed displays, Anzahl der adressierten Displays

MaxMatrix3 m(dataIn, load, clock, maxInUse);


void setup()
{
	m.init();
        m.flipOrderDisplays=0;
	m.flipXOrientation=0;
	m.flipYOrientation=0;
	m.flipAxis=0;
        m.autoReload=1;

}

void loop()
{
  for(int x=0;x<8*maxInUse;x++) //counts rows, Zaehler fuer die Zeilen
  {
      m.setDot(x,0,1);  //switch point on, Punkt einschalten
      delay(50);	//short delay, kurz warten
      m.setDot(x,0,0);	//switch it off again, wieder ausschalten
  }
}
