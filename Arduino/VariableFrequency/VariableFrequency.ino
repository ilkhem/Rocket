

// Variables
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;
int f = 45; // frequency

int outputPin = 12;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over an d over again forever
void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(1);
  f = sensorValue;
  digitalWrite(outputPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay((int)10000. / (2 * f));                   // wait for a second
  digitalWrite(outputPin, LOW);    // turn the LED off by making the voltage LOW
  delay((int)10000
  . / (2 * f));                   // wait for a second
}
