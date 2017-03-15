/*
 * Practicing with LED matrix (max7219)
 *
 * author: William Madruga
 * Date: 2017-03-06
 */

#define SHIFT_DATA  2
#define SHIFT_CLK   3
#define SHIFT_LATCH 4

#define NO_OP     0x00
#define DECODE    0x09
#define INTENSITY 0x0A
#define SCAN_LIM  0x0B
#define SHUTDOWN  0x0C
#define TEST_MODE 0x0F

// the data
byte w_[8] = {B11000011,B11000011,B11000011,B11011011,B11011011,B11011011,B11111111,B11111111};
byte i_[8] = {B00011000,B00011000,B00000000,B00011000,B00011000,B00011000,B00011000,B00011000};
byte l_[8] = {B01100000,B01100000,B01100000,B01100000,B01100000,B01100000,B01111110,B01111110};

void setup() {

  pinMode(SHIFT_DATA,  OUTPUT);
  pinMode(SHIFT_CLK,   OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);

  // starts with low intensity - ranges from 0x00 (min) to 0x0F (max)
  sendByte(INTENSITY, 0x00);
 
  // setting decode mode to Code B all digits.
  // only the first nibble of data (digit registers D0-D3) will be used.
  // sendByte(DECODE, 0x0F);

  // scan limit - all pins.
  sendByte(SCAN_LIM, 0x07);

  // max7219 powers up in shutdown mode. This is turning it off, setting up normal mode.
  sendByte(SHUTDOWN, 0x01);

  // blink screen ones in test mode.
  sendByte(TEST_MODE, 0x01);
  delay(500);
  sendByte(TEST_MODE, 0x00);

  clearContent();

}
 
void loop() {
  blinkLetters();
  clearContent();
  animatedLetters();
}

void blinkLetters() {
  sendLetter(w_);
  sendLetter(i_);
  sendLetter(l_);
  delay(100);
  sendLetter(l_);
}
void animatedLetters() {
  sendAnimatedLetter(w_);
  sendAnimatedLetter(i_);
  sendAnimatedLetter(l_);
  sendAnimatedLetter(l_);
}

void sendLetter(byte data[]) {
  for(int i=0; i<8; i++) {
    sendByte(i+1, data[i]);
  }
  delay(1000);    
  clearContent();
}

void sendAnimatedLetter(byte data[]) {  
  for(int i=0; i<8; i++) {
    sendByte(i+1, data[i]);
    delay(200);
  }
  delay(500);    
  clearContent();
}

void clearContent() {
  for(int i = 1; i <= 8; i++) {
    sendByte(i, 0);
  }
}

void sendByte(int address, byte data) {
	
  // matrix configuration
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);

  // send data
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, data);
  
  // flush it out to led matrix
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);

}
