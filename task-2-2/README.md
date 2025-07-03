# Обработка кнопки через прерывание

Цель: Освоить использование прерываний для обработки нажатий кнопки.

## Теория:

---

> **Регистрация обработчика прерывания для GPIO-пина**
> 
> ```cpp
> attachInterrupt(
>     uint8_t pin, // Номер GPIO
>     void(*handler)(), // Указатель на функцию вида: () -> void
>     int mode // Тип события
> ) -> void
> ```

- Функция-обработчик должна быть объявлена с `IRAM_ATTR` - атрибут указывающий компилятору размещать функцию в `RAM`


- Тип события:
    - `RISING`: Переход `HIGH` -> `LOW`
    - `FALLING`: Переход `HIGH` -> `LOW`
    - `CHANGE`: Любое изменение


- Антидребезг
    - Программная фильтрация ложных срабатываний контактов кнопки

---

## Итоговый код:

 ```cpp
const auto pin_led = 26, pin_button = 14;

volatile bool led_state = false;  // Состояние светодиода (изменяется в прерывании)

// Обработчик прерывания с защитой от дребезга
void IRAM_ATTR button_handler() {
    static decltype(millis()) last = 0;
    const auto debounce_delay = 100;  // Защита от дребезга (мс)
    
    // защита от дребезга контактов
    auto now = millis();
    if (now - last <= debounce_delay) { return; }
    last = now;
    
    led_state = not led_state;  // Инвертирование состояния
    digitalWrite(pin_led, led_state);
}

void setup() {
    pinMode(pin_led, OUTPUT);
    pinMode(pin_button, INPUT_PULLUP);
    
    // Регистрация прерывания на FALLING фронт
    attachInterrupt(pin_button, button_handler, FALLING);
}

void loop() {}  // Основная логика в прерывании
```
