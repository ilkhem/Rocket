/*
* First RF sketch using nRF24L01+ radios and Arduino (Uno or Micro)
*/
#include <SPI.h>    // Serial Peripheral Interface bus library
#include "RF24.h"   // Library for nRF24L01s

// Pins
int leftServoPin = 9;
int rightServopin = 10;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus pins and pins 7 & 8 */
//RF24 radio(7,8);  // For Arduino UNO
RF24 radio(2,3);  // For Arduino Micro

/* Create a binary address for read/write pipes */
byte addresses[][6] = {"1Node","2Node"};

void setup() {
  Serial.begin(115200);
  delay(100);
  radio.begin(); 
  radio.setChannel(113); 
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate( RF24_250KBPS ) ; 
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
}

void loop() {
  unsigned long response = 10;
  unsigned long instruction;    
  if( radio.available()) {                                        // Variable for the received timestamp
    while (radio.available()) {                                   // While there is data ready
      radio.read( &instruction, sizeof(unsigned long) );             // Get the payload
    }   
    Serial.print(F("Got instruction "));
    Serial.println(instruction);
 }
}

