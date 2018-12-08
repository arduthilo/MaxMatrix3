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


#ifndef _MaxMatrix3_H_
#define _MaxMatrix3_H_

#include "Arduino.h"

#define max7219_reg_noop        0x00
#define max7219_reg_digit0      0x01
#define max7219_reg_digit1      0x02
#define max7219_reg_digit2      0x03
#define max7219_reg_digit3      0x04
#define max7219_reg_digit4      0x05
#define max7219_reg_digit5      0x06
#define max7219_reg_digit6      0x07
#define max7219_reg_digit7      0x08
#define max7219_reg_decodeMode  0x09
#define max7219_reg_intensity   0x0a
#define max7219_reg_scanLimit   0x0b
#define max7219_reg_shutdown    0x0c
#define max7219_reg_displayTest 0x0f

class MaxMatrix3
{
  private:
    byte data;
    byte load;
    byte clock;
    byte num;
    byte buffer[80];
    
    void setCommand(byte command, byte value);
	
  public:
    MaxMatrix3(byte data, byte load, byte clock, byte num);
    
    void init();
    void clear();
    void reload();
    void setIntensity(byte intensity);
    void setColumn(byte col, byte pattern);
    void setDot(byte col, byte row, byte value);  
    void shiftLeft(bool rotate = false);
    void shiftRight(bool rotate = false);
    void shiftUp(bool rotate = false);
    void shiftDown(bool rotate = false);
    bool flipOrderDisplays;
    bool flipXOrientation;
    bool flipYOrientation;
    bool flipAxis;
    bool autoReload;
};

#endif
