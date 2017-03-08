#include <Keyboard.h>

void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:
  pinMode(2, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  while (digitalRead(2) == HIGH) {
    // do nothing until pin 2 goes low
    delay(500);
  }
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F2);
  delay(1000);

  Keyboard.releaseAll();
  Keyboard.write("xfce4-terminal");
  Keyboard.write(KEY_RETURN);

  // do nothing:
  while (true);
}








