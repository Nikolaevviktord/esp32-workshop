#include <Arduino.h>

const int ledPin = 2; // пин светолиода

void setup() {
  pinMode(ledPin, OUTPUT); // объявляем пин светодиода как выход
}

void loop() {
  // мигаем светодиодом
  digitalWrite(ledPin, not digitalRead(ledPin));
  delay(500);
}
