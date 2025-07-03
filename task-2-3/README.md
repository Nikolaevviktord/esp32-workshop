# Управление двумя кнопками

Цель: Научиться обрабатывать несколько кнопок с передачей контекста.

## Теория:

> **Регистрация обработчика прерывания для GPIO-пина**
> 
> ```cpp
> attachInterruptArg(
>     uint8_t pin,            // GPIO
>     void(*handler)(void *), // Функция вида (void *) -> void
>     void *arg,              // Безымянный указатель на передаваемый аргумент
>     int mode                // Режим*
> ) → void
> ```

- Функция-обработчик должна быть объявлена с `IRAM_ATTR` - атрибут указывающий компилятору размещать функцию в `RAM`


- Тип события:
    - `RISING`: Переход `HIGH` -> `LOW`
    - `FALLING`: Переход `HIGH` -> `LOW`
    - `CHANGE`: Любое изменение


- Работа с контекстом
    - Техника передачи дополнительных данных в обработчик через указатель


- Антидребезг
    - Программная фильтрация ложных срабатываний контактов кнопки

 ## Итоговый код:

 ```cpp
auto pin_led_1 = 26, pin_led_2 = 25;
const auto pin_button_1 = 14, pin_button_2 = 13;

// Обработчик прерывания с защитой от дребезга
void IRAM_ATTR button_handler(void *arg) {
  static decltype(millis()) last = 0;
  const auto debounce_delay = 100;  // Защита от дребезга (мс)
  
  // защита от дребезга контактов
  auto now = millis();
  if (now - last <= debounce_delay) { return; }
  last = now;
  
  // Получение контекста
  const auto pin_led = *static_cast<uint8_t *>(arg);
  
  // Инвертирование состояния
  bool led_state = not digitalRead(pin_led);
  digitalWrite(pin_led, led_state);
}

void setup() {
  // Инициализация пинов
  pinMode(pin_led_1, OUTPUT);
  pinMode(pin_led_2, OUTPUT);
  pinMode(pin_button_1, INPUT_PULLUP);
  pinMode(pin_button_2, INPUT_PULLDOWN);
  
  // Регистрация прерываний с передачей контекста
  attachInterruptArg(pin_button_1, button_handler, &pin_led_1, FALLING);
  attachInterruptArg(pin_button_2, button_handler, &pin_led_2, RISING);
}

void loop() {}  // Основная логика в прерывании
```
