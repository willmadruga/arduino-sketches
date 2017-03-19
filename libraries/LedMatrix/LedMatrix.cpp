/**
 * Library to work with led matrix max7219.
 *
 * Author: William Madruga
 */
#include "LedMatrix.h"
#include "Arduino.h"

#define NO_OP     0x00
#define DECODE    0x09
#define INTENSITY 0x0A
#define SCAN_LIM  0x0B
#define SHUTDOWN  0x0C
#define TEST_MODE 0x0F

LedMatrix::LedMatrix(int dataPin, int clockPin, int latchPin) {

  pinMode(dataPin,  OUTPUT);
  pinMode(clockPin,  OUTPUT);
  pinMode(latchPin, OUTPUT);
  
  _data  = dataPin;
  _clock = clockPin;
  _latch = latchPin;

	// I wanted the initialize() block to run here
	// but it's not happening... I need to understand why, later...
  
}

void LedMatrix::initialize() {

  // starts with low intensity - ranges from 0x00 (min) to 0x0F (max)
  sendByte(INTENSITY, 0x00);
 
  // setting decode mode to Code B all digits.
  // only the first nibble of data (digit registers D0-D3) will be used.
  // sendByte(DECODE, 0x0F);

  // scan limit - all pins.
  sendByte(SCAN_LIM, 0x07);

  // max7219 powers up in shutdown mode. This is turning it off, setting up normal mode.
  sendByte(SHUTDOWN, 0x01);

  // blink screen in test mode.
  sendByte(TEST_MODE, 0x01);
  delay(500);
  sendByte(TEST_MODE, 0x00);

  clear();

}

void LedMatrix::print(byte shape[]) {
  for(int i=0; i<8; i++) {
    sendByte(i+1, shape[i]);
  }
  delay(500);
}

void LedMatrix::clear() {
  for(int i = 1; i <= 8; i++) {
    sendByte(i, 0);
  }
}

void LedMatrix::setIntensity(int code) {
  if(code >= 0 && code <= 15) {
    // TODO:
    // convert from DEC to HEX
    // sendByte(INTENSITY, code);
  }
}

void LedMatrix::sendByte(int address, byte data) {
  
  // matrix configuration
  shiftOut(_data, _clock, MSBFIRST, address);

  // send data
  shiftOut(_data, _clock, MSBFIRST, data);
  
  // flush it out to led matrix
  digitalWrite(_latch, LOW);
  digitalWrite(_latch, HIGH);
  digitalWrite(_latch, LOW);

}

