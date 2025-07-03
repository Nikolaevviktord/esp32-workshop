#include <Arduino.h>

const auto ledPin = 26, butPin = 14; // пины светодиода и кнопки

void setup() {
    pinMode(ledPin, OUTPUT); // объявляем пин светодиода как выход
    pinMode(butPin, INPUT_PULLUP); // объявляем пин кнопки как вход с подтяжкой к 3V3
}

void loop() {
    bool button_state = digitalRead(butPin); // считываем состояние кнопки
    digitalWrite(ledPin, button_state); // включаем/выключаем светодиод

    delay(100);
}
