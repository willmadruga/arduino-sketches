/*
 * Practicing with LED matrix (max7219)
 *
 * author: William Madruga
 * Date: 2017-03-06
 */

#define SHIFT_DATA  2
#define SHIFT_CLK   3
#define SHIFT_LATCH 4

#define NO_OP 		0x00
#define DECODE 		0x09
#define INTENSITY 0x0A
#define SCAN_LIM  0x0B
#define SHUTDOWN  0x0C
#define TEST_MODE 0x0F



void setup() {

  pinMode(SHIFT_DATA,  OUTPUT);
  pinMode(SHIFT_CLK,   OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);

	// starts with low intensity - ranges from 0x00 (min) to 0x0F (max)
	sendData(INTENSITY, 0x00);
 
  // setting decode mode to Code B all digits.
  // only the first nibble of data (digit registers D0-D3) will be used.
  // sendData(DECODE, 0x0F);

  // scan limit - all pins.
  sendData(SCAN_LIM, 0x07);

  // max7219 powers up in shutdown mode. This is turning it off, setting up normal mode.
  sendData(SHUTDOWN, 0x01);

  // blink screen ones in test mode.
  sendData(TEST_MODE, 0x01);
  delay(500);
  sendData(TEST_MODE, 0x00);

}
 
void loop() {

  // Need to figure out how to show proper data in the LED...
  for (int i = 1; i <= 8; i++) {
    sendData(i, 0x01+i);
    delay(500);
  }

}

void sendData(int address, int data) {
	
	// matrix configuration
	shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);

  // send data
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, data);
  
  // flush it out to led matrix
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);

}
