/**
* Sending serial data to the board.
* Press '1' turns the LED on
* Press '2' turns the LED off
* 
* From the book Arduino, 2nd edition
* modified by: William Madruga
* 2017-03-16
*/

#define LED  13
#define RATE 9600 //standard baud rate

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(RATE);  
}

void loop() {
  if(Serial.available() > 0) {
    int command = Serial.read();
    if (command == '1') {
      digitalWrite(LED, HIGH);
      Serial.println("LED ON");
    } else if (command == '2') {
      digitalWrite(LED, LOW);
      Serial.println("LED OFF");
    } else {
      Serial.println("Invalid command");
      Serial.println(command);
    }
  }
}
