#include <Servo.h>

/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/


Servo myservo_l;  // create servo object to control a servo
Servo myservo_r;  // create servo object to control a servo
int speed_l=935;
int speed_r=900;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo_l.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo_r.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  //pos += 1;

  myservo_l.writeMicroseconds(1500-speed_l);
  myservo_r.writeMicroseconds(1500+speed_r);

}

