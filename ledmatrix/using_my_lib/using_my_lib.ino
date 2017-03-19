#include "LedMatrix.h"

/*
 * Practicing with LED matrix (max7219) and creating libraries :)
 *
 * author: William Madruga
 * Date: 2017-03-17
 */

LedMatrix matrix (2, 3, 4);

void setup() {
 matrix.initialize();
}
 
void loop() {
  matrix.print(w);
  matrix.print(i);
  matrix.print(l);
  matrix.print(l);
  matrix.clear();
}
