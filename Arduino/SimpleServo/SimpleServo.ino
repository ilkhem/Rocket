#include <Servo.h>

Servo servo;
void setup() {
  servo.attach(9);

}

void loop() {
  servo.writeMicroseconds(2500);
}
