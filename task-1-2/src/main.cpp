#include <Arduino.h>

void setup() {
  Serial.begin(115200); // инициализируем Serial-порт с частотой 115200 бод

  Serial.printf("Hello, World!\n"); // выводим "Hello, World!"
}

void loop() {}
