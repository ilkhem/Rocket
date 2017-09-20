
#include <SPI.h>    // Serial Peripheral Interface bus library
#include "RF24.h"   // Library for nRF24L01s

RF24 radio(7,8);  // For Arduino UNO
byte addresses[][6] = {"1Node","2Node"};

unsigned long instruction = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  radio.begin();  
  radio.setChannel(113); 
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate( RF24_250KBPS ) ; 
  radio.openWritingPipe( addresses[0]);
  delay(100);
}

void loop() {
/*
 * Instructions:
 *  0: do nothing
 *  1: move forward
 *  2: move backward
 *  4: turn right
 *  3: turn left
 */
  radio.write(&instruction, sizeof(unsigned long));
  Serial.print("Sent instruction: ");
  Serial.println(instruction);
  if ( Serial.available() ){
    char c = toupper(Serial.read());
    if ( c == 'W') {      
      instruction = 1;
    } else if ( c == 'S') {
      instruction = 2;
    } else if ( c == 'A') {
      instruction = 3;
    } else if ( c == 'D') {
      instruction = 4;
    } else if ( c == 'Z') {
      instruction = 5;
    }
  }
  delay(100);
} 


