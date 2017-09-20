#include <Servo.h>


// Pins and sensors
// int leftOutputPin = 3;
// int rightOutputPin = 4;
int soundPin = 3;
int leftSensorPin = A4;
int rightSensorPin = A3;
int leftSensorValue = 0;
int rightSensorValue = 0;
int leftServoPin = 9;
int rightServoPin = 10;
int backSensorPin = A2;
int backSensorValue = 0;


// Servos
Servo leftServo;  // create servo object to control the left servo
Servo rightServo;  // create servo object to control the right servo
const int idleSpeed = 1500;
int leftSpeed=450;
int rightSpeed=500;

int leftServoPos = 0;
int rightServoPos = 0;

void setup() {
  pinMode(soundPin, OUTPUT);
  Serial.begin(9600);
  leftServo.attach(leftServoPin);  
  rightServo.attach(rightServoPin);
}

void beepWithDelay(){
  digitalWrite(soundPin, HIGH);
  delay(500);
  digitalWrite(soundPin, LOW);
  delay(200);
}

void loop() {
  leftSensorValue = analogRead(leftSensorPin);
  rightSensorValue = analogRead(rightSensorPin);
  backSensorValue = analogRead(backSensorPin);
  leftServoPos = leftServo.read();
  rightServoPos = rightServo.read();
  if (rightSensorValue - leftSensorValue > 100) { // turn right
    leftServo.writeMicroseconds(idleSpeed - leftSpeed);
    rightServo.writeMicroseconds(idleSpeed - rightSpeed);
    //digitalWrite(soundPin, HIGH);
  }
  else if (leftSensorValue - rightSensorValue > 100) { // turn left
    leftServo.writeMicroseconds(idleSpeed + leftSpeed);
    rightServo.writeMicroseconds(idleSpeed + rightSpeed);
    //digitalWrite(soundPin, HIGH);
  }
  else { // Move forward
    leftServo.writeMicroseconds(idleSpeed - leftSpeed);
    rightServo.writeMicroseconds(idleSpeed + rightSpeed);
    //digitalWrite(soundPin, LOW);
  }
  if (backSensorValue >970) { // move backward
    leftServo.writeMicroseconds(idleSpeed + leftSpeed);
    rightServo.writeMicroseconds(idleSpeed - rightSpeed);
    beepWithDelay();
  }
  Serial.print("backSensorValue");
  Serial.println(backSensorValue);
}

