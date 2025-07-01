# Мигание встроенным светодиодм на плате ESP32

Программа мигания встроенным светодиодом - простейший код для микроконтроллера. Он использует базовые команды `digitalWrite` и `delay`, знакомые вам по программированию плат Arduino (если вы не умеете программировать Arduino, перед прохождением курса посмотрите [курс на канале "Заметки Ардуинщика"](https://www.youtube.com/playlist?list=PLgAbBhxTglwmVxDDC5TSYUI91oZ0LZQMw)

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

> **Подать напряжение на пин**:
> ```cpp
> digitalWrite(
>     uint8_t pin, // GPIO
>     bool state   // Состояние*
> ) -> void
> ```

*Состояния:*
- `HIGH`: Высокое напряжение (~3.3В)
- `LOW`: Низкое напряжение (~0.1В)

---

Встроенный светодиод (если он есть) на многих платах ESP32 привязан ко второму пину. Вот код для мигания встроенным светодиодом:

```cpp
const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}
```

Данный код будет работать и на Arduino, и на ESP. Но на ESP мы имеем возможность также узнать, какой сигнал в данный момент подаётся на выход. Так что код можно упростить:

```cpp
const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, not digitalRead(ledPin);
  delay(500);
}
```
