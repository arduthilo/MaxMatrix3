/* MaxMatrix3
 * Version 0.1 DEZ 2018
 * Copyright 2018 Thilo Wuenscher
 * based upon MaxMatrix by Oscar Kin-Chung Au
 *
 * This file is part of MaxMatrix3
 *
 * MaxMatrix3 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MaxMatrix3 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MaxMatrix2.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "Arduino.h"
#include "MaxMatrix3.h"

MaxMatrix3::MaxMatrix3(byte _data, byte _load, byte _clock, byte _num) 
{
	data = _data;
	load = _load;
	clock = _clock;
	num = _num;
	for (int i=0; i<80; i++)
		buffer[i] = 0;
        flipOrderDisplays=0;
	flipXOrientation=0;
	flipYOrientation=0;
	flipAxis=0;
	autoReload=1;
}

void MaxMatrix3::init()
{
	pinMode(data,  OUTPUT);
	pinMode(clock, OUTPUT);
	pinMode(load,  OUTPUT);
	digitalWrite(clock, HIGH); 

	setCommand(max7219_reg_scanLimit, 0x07);      
	setCommand(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
	setCommand(max7219_reg_shutdown, 0x01);    // not in shutdown mode
	setCommand(max7219_reg_displayTest, 0x00); // no display test
	
	// empty registers, turn all LEDs off
	clear();
	
	setIntensity(0x0f);    // the first 0x0f is the value you can set
}

void MaxMatrix3::setIntensity(byte intensity)
{
	setCommand(max7219_reg_intensity, intensity);
}

void MaxMatrix3::clear()
{
	for (int i=0; i<80; i++)
		buffer[i] = 0;
	if(autoReload)reload();
}

void MaxMatrix3::setCommand(byte command, byte value)
{
	digitalWrite(load, LOW);    
	for (int i=0; i<num; i++) 
	{
		shiftOut(data, clock, MSBFIRST, command);
		shiftOut(data, clock, MSBFIRST, value);
	}
	digitalWrite(load, LOW);
	digitalWrite(load, HIGH);
}


void MaxMatrix3::setColumn(byte col, byte pattern)
{
	buffer[col]=pattern;
	if(autoReload)reload();	
}


void MaxMatrix3::setDot(byte col, byte row, byte value)
{
    bitWrite(buffer[col], row, value);
    if(autoReload)reload();
}

/*void MaxMatrix3::reload()//Alles zusammen für mein Display passend
{
	for (int i=0; i<8; i++) //i=Nummer der Zeile innerhalb des Achterblocks
	{
		digitalWrite(load, LOW);    
		for (int j=0; j<num; j++) //j=Nummer des Achterblocks
		{
                        byte zahl=0; //Muster der Zeile innerhalb des Achterblocks
                        for(int k=0;k<8;k++)  //k=Nummer der Spalte innerhalb des Achterblocks
                               zahl+=bitRead(buffer[(flipXOrientation?7-k:k)+8*(flipOrderDisplays?j:(num-j-1))],flipYOrientation?i:7-i)<<k;
			shiftOut(data, clock, MSBFIRST, i + 1);
			shiftOut(data, clock, MSBFIRST, zahl);
		}
		digitalWrite(load, LOW);
		digitalWrite(load, HIGH);
	}
}*/

void MaxMatrix3::reload()  //Alles zusammen
{
	if(flipAxis)
	{
		for (int i=0; i<8; i++)//Nummer der Spalte innerhalb des Displays
		{
			digitalWrite(load, LOW);    
			for (int j=0; j<num; j++) //Nummer des Displays
			{
				shiftOut(data, clock, MSBFIRST, i + 1);
				byte value;
				if(flipYOrientation)
				{
					value=0;
					for(int k=0;k<8;k++)
						if(bitRead(buffer[(flipOrderDisplays?j:num-j-1)*8+(flipXOrientation?7-i:i)],k))bitSet(value,7-k);
				}
				else
				{
					value=buffer[(flipOrderDisplays?j:num-j-1)*8+(flipXOrientation?7-i:i)];
				}
				shiftOut(data, clock, MSBFIRST, value);
			}
			digitalWrite(load, LOW);
			digitalWrite(load, HIGH);
		}
	}
	else
	{
		for (int i=0; i<8; i++) //i=Nummer der Zeile innerhalb des Achterblocks
		{
			digitalWrite(load, LOW);    
			for (int j=0; j<num; j++) //j=Nummer des Achterblocks
			{
        	                byte zahl=0; //Muster der Zeile innerhalb des Achterblocks
        	                for(int k=0;k<8;k++)  //k=Nummer der Spalte innerhalb des Achterblocks
        	                       zahl+=bitRead(buffer[(flipXOrientation?7-k:k)+8*(flipOrderDisplays?j:(num-j-1))],flipYOrientation?i:7-i)<<k;
				shiftOut(data, clock, MSBFIRST, i + 1);
				shiftOut(data, clock, MSBFIRST, zahl);
			}
			digitalWrite(load, LOW);
			digitalWrite(load, HIGH);
		}
	}
}

/*void MaxMatrix3::reload()  //Für vertauschte Achsen
{
	for (int i=0; i<8; i++)//Nummer der Spalte innerhalb des Displays
	{
		digitalWrite(load, LOW);    
		for (int j=0; j<num; j++) //Nummer des Displays
		{
			shiftOut(data, clock, MSBFIRST, i + 1);
			byte value;
			if(flipYOrientation)
			{
				value=0;
				for(int k=0;k<8;k++)
					if(bitRead(buffer[(flipOrderDisplays?j:num-j-1)*8+(flipXOrientation?7-i:i)],k))bitSet(value,7-k);
			}
			else
			{
				value=buffer[(flipOrderDisplays?j:num-j-1)*8+(flipXOrientation?7-i:i)];
			}
			shiftOut(data, clock, MSBFIRST, value);
		}
		digitalWrite(load, LOW);
		digitalWrite(load, HIGH);
	}
}*/

void MaxMatrix3::shiftLeft(bool rotate)
{
	byte old = buffer[0];
	for (int i=0; i<8*num-1; i++)
		buffer[i] = buffer[i+1];
	buffer[8*num-1]=rotate?old:0;
	if(autoReload)reload();
}

void MaxMatrix3::shiftRight(bool rotate)
{
	byte old = buffer[8*num-1];
	for (int i=8*num-1; i>0; i--)
		buffer[i] = buffer[i-1];
	buffer[0]=rotate?old:0;
	if(autoReload)reload();
}

void MaxMatrix3::shiftUp(bool rotate)
{
	for (int i=0; i<num*8; i++)
	{
		bool b = buffer[i] & 1;
		buffer[i] >>= 1;
		if (rotate) bitWrite(buffer[i], 7, b);
	}
	if(autoReload)reload();
}

void MaxMatrix3::shiftDown(bool rotate)
{
	for (int i=0; i<num*8; i++)
	{
		bool b = buffer[i] & 128;
		buffer[i] <<= 1;
		if (rotate) bitWrite(buffer[i], 0, b);
	}
	if(autoReload)reload();
}


