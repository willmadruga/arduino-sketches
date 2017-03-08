#include <LedControl.h>

/**
 * Playing with LED matrix using LedControl library.
 * 2017-03-07
 * 
 * author: William Madruga
 */
LedControl lc=LedControl(12,11,10,1);
unsigned long delaytime=100;

void setup() {
  
  lc.shutdown(0,false);  
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

}

void loop() {

  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
  delay(delaytime);
  lc.clearDisplay(0);

}
