/**
 * This is the other board and it has the following components:
 * Arduino Nano
 * nRF24L01P radio
 * LED + 220 ohm resistor
 * 
 * How it works:
 * LED starts OFF.
 * This radio listens for data and once data is received
 * it turns the LED ON, wait a second, and sends the same
 * back while turning the LED OFF again.
 *
 * TODO: I think a nice thing to add later is the "Score" :)
 * I can add a led matrix to this board and increment the
 * score number each time I get data :)
 *
 * Radio code based off RF24 library examples :)
 * Author: William Madruga
 */

#include <SPI.h>
#include "RF24.h"

#define RADIO_CE_PIN 7 // chip enable pin
#define RADIO_CS_PIN 8 // chip select pin
#define LED_PIN 10

RF24 radio(RADIO_CE_PIN,RADIO_CS_PIN);
byte addresses[][6] = {"1Node","2Node"};

void setup() {

  Serial.begin(115200);
  
  digitalWrite(LED_PIN, LOW);

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  
}

void loop() {
  
  radio.startListening();
    
  if ( radio.available() ) {
    Serial.println(F("Received data..."));
    digitalWrite(LED_PIN, HIGH);
    delay(1000);

    radio.stopListening();
    Serial.println(F("Now sending"));

    unsigned long start_time = micros();
    if (!radio.write( &start_time, sizeof(unsigned long) )) {
      Serial.println(F("failed"));
    }
    digitalWrite(LED_PIN, LOW);
  }

} // Loop
