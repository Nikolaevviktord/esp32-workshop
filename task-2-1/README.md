# Базовое управление кнопкой

Цель: Научиться читать состояние кнопки и управлять светодиодом.

## Теория:

> **Настроить режим работы GPIO-пина**:
> ```cpp
> pinMode(
>    uint8_t pin, // GPIO
>    uint8_t mode // Режим*
> ) -> void
> ```

*Режимы:*

- `INPUT`: Вход без подтяжки
- `INPUT_PULLUP`: Вход с подтяжкой к `VCC`
- `INPUT_PULLDOWN`: Вход с подтяжкой к `GND` (доступно не для всех пинов)
- `OUTPUT`: Цифровой выход

---

> **Считать текущее логическое состояние пина**:
> ```cpp
> digitalRead(uint8_t pin) -> int
> ```

*Интерпретация возвращаемого значения:*

- `HIGH` (`1`): Напряжение > 2.5V
- `LOW` (`0`): Напряжение < 1.0V

---

Итоговый код:

```cpp
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
```
