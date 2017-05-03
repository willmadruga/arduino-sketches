/**
 * This is the main board and it has the following components:
 * Arduino Nano
 * nRF24L01P radio
 * CDS-55 photoresistor + 10k ohm resistor
 * LED + 220 ohm resistor
 * 
 * How it works:
 * Board starts with LED turned ON and radio in receiving mode. 
 * When photo sensor is activated, radio changes to transmitting mode
 * and sends data to other radio, upon data received it should turn LED OFF
 * and switch back to receiving mode.
 * Once it receives data, it turns LED ON again.
 *
 * Author: William Madruga
 */

#include <SPI.h>
#include "RF24.h"
#include <RBD_LightSensor.h>

#define RADIO_CE_PIN 7 // chip enable pin
#define RADIO_CS_PIN 8 // chip select pin
#define LED_PIN 10     // LED
#define SENSOR_PIN A0  // Photosensor analog pin  // http://robotsbigdata.com/docs-arduino-light-sensor.html 

// gimme instances baby :)
RF24 radio(RADIO_CE_PIN,RADIO_CS_PIN);
RBD::LightSensor light_sensor(SENSOR_PIN);

byte addresses[][6] = {"1Node","2Node"};

void setup() {

  Serial.begin(115200);
  
  digitalWrite(LED_PIN, HIGH);

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
  
  // Setup light sensitivity threshold
  // light_sensor.setFloor(10);
  // light_sensor.setCeiling(999);
}

void loop() {
  
  radio.startListening();
  
  Serial.println(light_sensor.getValue()); // Will debug and watch the values for a bit so I can code a nice interval :)
  
  if (light_sensor.getValue() >= 1024 )  { // set to 1024 so it disables this if -- value actually ranges between 0 and 1023
    
    radio.stopListening();
    Serial.println(F("Now sending"));

    unsigned long start_time = micros();
    if (!radio.write( &start_time, sizeof(unsigned long) )) {
      Serial.println(F("failed"));
    }
		
    radio.startListening();
    
    unsigned long started_waiting_at = micros();
    boolean timeout = false;
    
    while ( !radio.available() ) {
      if (micros() - started_waiting_at > 200000 ) {
          timeout = true;
          break;
      }      
    }
        
    if ( timeout ) {
        Serial.println(F("Failed, response timed out."));
    } else {

      digitalWrite(LED_PIN, LOW);

    }

    // Try again 1s later
    delay(1000);
  }
  
  /* *******************************************************
   * Wait for data to come back and turn the LED ON again.
   ******************************************************* */
   if( radio.available()){
      digitalWrite(LED_PIN, HIGH);
   }

} // Loop
