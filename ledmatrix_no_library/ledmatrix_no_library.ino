/*
 * Practicing with LED matrix.
 * component: max7219
 *
 * author: William Madruga
 * Date: 2017-03-06
 */

/**
 * Arduino PINS
 */
int PIN_DATA = 12; // sends data to led matrix
int PIN_CLK  = 11; // clock
int PIN_CS   = 10; // chip selection - determines which LED to send data to.

int data[16]; // Serial data format 16 bits.

void setup() {

  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK,  OUTPUT);
  pinMode(PIN_CS,   OUTPUT);
  
}
 
void loop() {


}


