# Задание 2.7: ШИМ через analogWrite

Цель: Освоить базовое управление ШИМ на ESP32.

Задача: Плавно изменять яркость светодиода.

## Теория:

> **Устанавливает значение ШИМ на пине**
> ```cpp
> analogWrite(
>     uint8_t pin,    // GPIO
>     uint32_t value  // Значение заполнения
> ) -> void
> ```

---

> **Устанавливает разрешение ШИМ**
> ```cpp
> analogWriteResolution(
>     uint8_t bits // (8..16 бит)
> ) -> void
> ```

---

> **Устанавливает частоту ШИМ**
> ```cpp
> analogWriteFrequency(
>     uint32_t freq // в Гц
> ) -> void
> ```

## Итоговый код:

```cpp
const auto pin_led = 26;

const auto pwm_resolution = 10;  // Разрешение ШИМ (10 бит = 0-1023)

void setup() {
    pinMode(pin_led, OUTPUT);
    
    // Настройка параметров ШИМ
    analogWriteResolution(pwm_resolution);
    analogWriteFrequency(10000);  // Частота 10 КГц
}

void loop() {
    const auto max_value = (1 << pwm_resolution) - 1;  // Максимальное значение
    
    // Плавное изменение яркости по треугольной функции
    for (int i = -max_value; i < max_value; i++) {
        auto pwm_value = max_value - abs(i);  // Треугольная функция
        analogWrite(pin_led, pwm_value);
        delay(1000 / max_value);  // Плавное изменение
    }
}
```
