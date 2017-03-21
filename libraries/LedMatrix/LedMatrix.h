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
 *
 * TODO:
 * 1. define hex for shapes like these | \ / - _
 * 2. define constants for letters and digits based on the formation of these shapes
 * 3. have the whole alphabet and digits available in this library.
 *
 * Author: William Madruga
 */
#ifndef LedMatrix_h

  #define LedMatrix_h
  #include "Arduino.h"

  const byte w[8] = {0xC3, 0xC3, 0xC3, 0xDB, 0xDB, 0xDB, 0xFF, 0xFF};
  const byte i[8] = {0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18};
  const byte l[8] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x7E};

  const byte smile[8] = {0xFF, 0x81, 0xA5, 0x81, 0xA5, 0xBD, 0x81, 0xFF};

  class LedMatrix {

    int _data;
    int _clock;
    int _latch;
    void sendByte(unsigned int address, byte data);

    public:

    LedMatrix(unsigned int dataPin, unsigned int ClockPin, unsigned int LatchPin);

    void initialize();
    void print(byte shape[]);
    void clear();
    void setIntensity(unsigned int code);

  };

#endif
