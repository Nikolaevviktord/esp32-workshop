const auto pin_led = 26, pin_touch = 14;
const auto threshold = 30;  // Порог срабатывания
  
void setup() {
    pinMode(pin_led, OUTPUT);
}

void loop() {
    // Чтение значения ёмкостного датчика
    auto value = touchRead(pin_touch);
    bool touched = value < threshold;
    
    digitalWrite(pin_led, touched);  // Управление светодиодом
    delay(100);
}
