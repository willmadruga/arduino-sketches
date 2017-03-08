
/**
 * Studying how to shift data out with IC 74HC595.
 * Code based on Bean Eater's youtube video: 
 * https://www.youtube.com/watch?v=K88pgWhEb1M
 * 
 * author: Ben Eater
 * modified by: William Madruga
 * 
 * 2017-03-07
 */

#define SHIFT_DATA   2
#define SHIFT_CLK    3
#define SHIFT_LATCH  4

void setup() {
  
  pinMode(SHIFT_DATA,  OUTPUT);
  pinMode(SHIFT_CLK,   OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);

}

void loop() {

  for (int i =0; i < 256; i++) {
    sendData(i);
    delay(500);
  }

}

/*
 * Shift out data and flush it to output.
 */
void sendData(int data) {

  // shift out 8 bits of data.
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, data);

  // flush it out from storage register to output.
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  
}

