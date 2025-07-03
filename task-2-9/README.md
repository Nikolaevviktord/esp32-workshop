# Задание 2.9: Комбинированное управление

Цель: Создать комплексную систему управления с использованием всех изученных компонентов.

## Теория:

> **Ограничивает значение заданным диапазоном**
> 
> ```cpp
> #define constrain(value, min, max)
> ```

---

> **Преобразует значение из одного диапазона в другой**
> 
> ```cpp
> map(long value, long fromLow, long fromHigh, long toLow, long toHigh) -> long
> ```

## Итоговый код:

```cpp
const auto pin_led = 26, pin_potentiometer = 33, pin_button = 14, pin_touch = 32;

const auto pwm_resolution = 10;  // Разрешение ШИМ
const auto max_pwm = (1 << pwm_resolution) - 1;
const auto step = max_pwm / 10;

volatile auto brightness = max_pwm / 2;  // Начальная яркость 50%

struct Context {
    const int step;                     // Шаг изменения
    const int debounce;                 // Длительность дребезга
    volatile decltype(millis()) last;   // Момент прошлого вызова
};

// Обработчик нажатия
void IRAM_ATTR clickHandler(void *arg) {
    auto context = static_cast<Context *>(arg);
    
    auto now = millis();
    if (now - context->last < context->debounce) { return; }
    context->last = now;
    
    // Изменение и проверка
    brightness += context->step;
    brightness = constrain(brightness, 0, max_pwm);
}

void setup() {
    pinMode(pin_led, OUTPUT);
    pinMode(pin_button, INPUT_PULLUP);
    analogWriteResolution(pwm_resolution);  // Настройка ШИМ
    
    // Создание контекстов
    static Context button_context = {.step = step, .debounce=100, .last = 0};
    static Context touch_context = {.step = -step, .debounce=300, .last = 0};
    
    // Регистрация обработчиков
    attachInterruptArg(pin_button, clickHandler, &button_context, FALLING);
    touchAttachInterruptArg(pin_touch, clickHandler, &touch_context, 30);
}

void loop() {
    // Чтение потенциометра для управления частотой мигания
    auto pot_value = analogRead(pin_potentiometer);
    auto period = map(pot_value, 0, 1023, 50, 500);  // Преобразование диапазона
    
    // Мигание светодиодом
    analogWrite(pin_led, brightness);
    delay(period);
    analogWrite(pin_led, 0);
    delay(period);
}
```
