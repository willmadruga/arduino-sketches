/**
 * Library to work with led matrix max7219.
 * 
 * How to use:
 * 1. include LedMatrix.h in your sketch
 * 2. instantiate an object passing data, clock and latch pins
 * LedMatrix matrix (2, 3, 4);
 * 3. initialize the matrix in the setup() block
 * matrix.initialize();
 * 4. print alphanumeric values to the matrix
 * matrix.print(w); // w is already defined in the library.
 *
 * Author: William Madruga
 */
#ifndef LedMatrix_h

  #define LedMatrix_h
  #include "Arduino.h"

	// TODO: define all letters and numbers

  // Character definitions:
  //B11000011,B11000011,B11000011,B11011011,B11011011,B11011011,B11111111,B11111111
  const byte w[8] = {0xC3, 0xC3, 0xC3, 0xDB, 0xDB, 0xDB, 0xFF, 0xFF};
  //B00011000,B00011000,B00000000,B00011000,B00011000,B00011000,B00011000,B00011000
  const byte i[8] = {0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18};
  //B01100000,B01100000,B01100000,B01100000,B01100000,B01100000,B01111110,B01111110
  const byte l[8] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x7E};
  
  class LedMatrix {
    
      int _data;
      int _clock;
      int _latch;
      
      void sendByte(int address, byte data);
      
    public:
  
      LedMatrix(int dataPin, int ClockPin, int LatchPin);
      
      void initialize();
      void print(byte shape[]);
      void clear();
      void setIntensity(int code);
    
  };
  
#endif
