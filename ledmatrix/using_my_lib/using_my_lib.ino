#include "LedMatrix.h"

/*
 * Practicing with LED matrix (max7219) and creating libraries :)
 *
 * author: William Madruga
 * Date: 2017-03-17
 */

#define BAUD_RATE 9600

LedMatrix matrix (2, 3, 4);

void setup() {
 Serial.begin(BAUD_RATE);
 matrix.initialize();
 matrix.print(smile);
 delay(1000);
 matrix.clear();
}

void loop() {
  matrix.setIntensity(0);
  matrix.print(w);
  matrix.setIntensity(5);
  matrix.print(i);
  matrix.setIntensity(10);
  matrix.print(l);
  matrix.setIntensity(15);
  matrix.print(l);
  matrix.clear();
}
