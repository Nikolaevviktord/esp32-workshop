#include <Arduino.h>

const auto ledPin = 26, butPin = 14;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(butPin, INPUT_PULLUP);
}

void loop() {
    bool button_state = digitalRead(butPin);
    digitalWrite(ledPin, button_state);

    delay(100);
}
