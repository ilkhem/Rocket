int outputPin = 3;
int sensorPin = A4;
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(1);
  if (sensorValue > 80) {
    digitalWrite(outputPin, HIGH);
  }
  else {
    digitalWrite(outputPin, LOW);
  }
}
