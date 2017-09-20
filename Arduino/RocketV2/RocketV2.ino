#include <Servo.h>


Servo leftServo;  // create servo object to control the left servo
Servo rightServo;  // create servo object to control the right servo

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  leftServo.attach(9);  
  rightServo.attach(10);
}

int pos = 0;
int actualPos = 0;
int goFull = 90;
int goHalf = 45;



void goRight() {
  leftServo.attach(9);
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      leftServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(17);  
  }
  leftServo.detach();          
}

void goLeft() {
  rightServo.attach(10);
  for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      rightServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(16);  
  }
  rightServo.detach();          
}


void loop() {
  Serial.println(actualPos);
  if (Serial.available()){
    char c = toupper(Serial.read());
    if ( c == 'A') {      
      goLeft();
    } else if ( c == 'D') {      
      goRight();
    }
  }
}
