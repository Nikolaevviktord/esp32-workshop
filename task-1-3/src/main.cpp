const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, not digitalRead(ledPin));
  delay(500);
}
