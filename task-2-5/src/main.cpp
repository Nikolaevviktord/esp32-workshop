#include <Arduino.h>

const auto pin_led = 26, pin_touch = 14;
const auto threshold = 30;

volatile bool led_state = false;

// Обработчик прерывания сенсора
void IRAM_ATTR touch_handler() {
    static decltype(millis()) last = 0;
    const auto debounce_delay = 300;  // Увеличенный таймаут для сенсора
    
    auto now = millis();
    if (now - last <= debounce_delay) { return; }
    last = now;
    
    led_state = not led_state;
    digitalWrite(pin_led, led_state);
}

void setup() {
    pinMode(pin_led, OUTPUT);
    // Регистрация прерывания сенсора
    touchAttachInterrupt(pin_touch, touch_handler, threshold);
}

void loop() {}
