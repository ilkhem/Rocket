
#include <SPI.h>    // Serial Peripheral Interface bus library
#include "RF24.h"   // Library for nRF24L01s
#include <Servo.h>

// Pins and sensors
int leftServoPin = 9;
int rightServoPin = 10;


// Servos
Servo leftServo;  // create servo object to control the left servo
Servo rightServo;  // create servo object to control the right servo
const int idleSpeed = 1500;
int leftSpeed=450;
int rightSpeed=500;

int leftServoPos = 0;
int rightServoPos = 0;

int Max = 800;

RF24 radio(2,3);  // For Arduino Micro
byte addresses[][6] = {"1Node","2Node"};

void setup() {
  Serial.begin(115200);
  delay(100);
  // Setup radio
  radio.begin(); 
  radio.setChannel(113); 
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate( RF24_250KBPS ) ; 
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
  // Setup servos
  leftServo.attach(leftServoPin);  
  rightServo.attach(rightServoPin);
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
    if (instruction == 1) {
      leftServo.writeMicroseconds(idleSpeed - leftSpeed);
      rightServo.writeMicroseconds(idleSpeed + rightSpeed);
    } else if (instruction == 2) {
      leftServo.writeMicroseconds(idleSpeed + leftSpeed);
      rightServo.writeMicroseconds(idleSpeed - rightSpeed);
      //beepWithDelay();
    } else if (instruction == 3) {
      leftServo.writeMicroseconds(idleSpeed - leftSpeed);
      rightServo.writeMicroseconds(idleSpeed - rightSpeed);
    }  else if (instruction == 4) {
      leftServo.writeMicroseconds(idleSpeed + leftSpeed);
      rightServo.writeMicroseconds(idleSpeed + rightSpeed);
    } else if (instruction == 5) {
      leftServo.writeMicroseconds(idleSpeed);
      rightServo.writeMicroseconds(idleSpeed);
    } else if (instruction == 0) {
      leftServo.writeMicroseconds(idleSpeed);
      rightServo.writeMicroseconds(idleSpeed);
    }
 }
}

