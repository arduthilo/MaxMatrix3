
#include <MaxMatrix3.h>

const byte dataIn = 3;
const byte load = 4;
const byte clock = 5;
const byte maxInUse = 4; //number of adressed displays, Anzahl der adressierten Displays

MaxMatrix3 m(dataIn, load, clock, maxInUse);


void setup()
{
  m.init();
  m.autoReload=0;
  for(int i=0;i<maxInUse;i++)
    for(int j=1;j<7;j++)
      for(int k=3;k<5;k++)
      {
        m.setDot(i*8+j,k,1);  //grosse Pluszeichen malen
        m.setDot(i*8+k,j,1);
      }
  m.autoReload=1;
  m.reload();
}

void loop()
{
  for(int i=0;i<maxInUse*8;i++)
  {
    m.shiftLeft(1);    //nach links schieben
    delay(50);
  }
  delay(1000);
  for(int i=0;i<maxInUse*8;i++)
  {
    m.shiftRight(1);    //nach rechts schieben
    delay(50);
  }
  delay(1000);
  for(int i=0;i<maxInUse*8;i++)
  {
    m.shiftUp(1);    //nach oben schieben
    delay(50);
  }
  delay(1000);
  for(int i=0;i<maxInUse*8;i++)
  {
    m.shiftDown(1);    //nach unten schieben
    delay(50);
  }
  delay(1000);
  for(int i=0;i<maxInUse*8;i++)
  {
    m.shiftLeft();    //nach links schieben, den alten Inhalt nicht wieder einblenden
    delay(50);
  }
  delay(1000);
}


