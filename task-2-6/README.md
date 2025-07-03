# Две сенсорные кнопки

Цель: Обработка нескольких сенсорных кнопок с передачей контекста.

Задача: Повторите задачу 2-3, используя технологию сенсорной кнопки.

## Теория:

> **Зарегистрировать обработчик для сенсорного ввода с передачей аргумента**
> 
> ```cpp
> touchAttachInterruptArg(
>     uint8_t pin,        // GPIO 
>     void(*handler)(),   // Обработчик как у тактовой кнопки
>     void *arg,          // Безымянный указатель на пользовательские данные
>     uint16_t threshold  // пороговое значение
> ) -> void
> ```

---

> **Особенности:**
> 
> - Более длинный антидребезг из-за природы сенсора
> - В качестве контекста передаём несколько параметров через структуру

---

> **Калибровка порога**
> 
> - Экспериментальное определение порогового значения для конкретного сенсора

## Итоговый код:

```cpp
const auto pin_led_1 = 26, pin_touch_1 = 14;
const auto pin_led_2 = 25, pin_touch_2 = 13;

// Определяем структуру для передачи нескольких параметров
struct Context {
    const int pin_led;                  // Пин светодиода
    volatile decltype(millis()) last;   // Момент последнего вызова
};

// Обработчик прерывания сенсора
void IRAM_ATTR touchHandler(void *arg) {
    const auto debounce_delay = 300;  // Увеличенный таймаут для сенсора
    
    // Получаем контекст
    auto context = static_cast<Context *>(arg);
    
    auto now = millis();
    if (now - context->last <= debounce_delay) { return; }
    context->last = now;
    
    bool led_state = not digitalRead(context->pin_led);
    digitalWrite(context->pin_led, led_state);
}

void setup() {
    const auto threshold = 30;
    
    pinMode(pin_led_1, OUTPUT);
    pinMode(pin_led_2, OUTPUT);
    
    // Создаём контексты
    static Context context_1 = {
        .pin_led = pin_led_1,
        .last = 0
    };
    
    static Context context_2 = {pin_led_2, 0};
    
    // Регистрация обработчиков с передачей контекста
    touchAttachInterruptArg(pin_touch_1, touchHandler, &context_1, threshold);
    touchAttachInterruptArg(pin_touch_2, touchHandler, &context_2, threshold);
}

void loop() {}
```
