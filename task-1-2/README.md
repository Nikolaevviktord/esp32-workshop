# Работа с Serial Monitor - вывод "Hello, World!"

Цель: научиться работать с Serial-портом на ESP32

Задача: вывести в Serial Monitor текст "Hello, World!"

## Теория

> Serial Monitor - способ вывода информации с микроконтроллера в консоль на компьютере.

---

> **Инициализация Serial**
>
> ```cpp
> Serial.begin(
>     uint32_t baudrate // скорость порта
> )
> ```
>
> Для ESP32 обычно используют бодрейт 115200.

---

> **Вывод текста**
>
> Осуществляется командами `Serial.print()` (выводит значение), `Serial.println` (выводит значение с переводом на новую строку), `Serial.printf()` (имеет такой же синтаксис, как в `C`).

## Итоговый код:

```cpp
void setup() {
  Serial.begin(115200); // инициализируем Serial-порт с частотой 115200 бод

  Serial.printf("Hello, World!\n"); // выводим "Hello, World!"
}

void loop() {}
```
