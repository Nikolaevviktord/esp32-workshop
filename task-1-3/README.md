# Мигание внешним светодиодом

Цель: Научиться работатьс внешними модулями на ESP32.

Задача: Помигать внешним светодиодом.

## Теория:

> При подключении светодиода стоит учесть, что напряжение питания ESP32 отличается от напряжения платы привычной многим Arduino. Так что может понадобиться другой резистор (а не как на Arduino 220 Ом). Здесь, конечно, подойдёт резистор 220 Ом, но на всякий случай приведу формулу вычисления сопротивления резистора:
> 
> $$R = \frac{V_п - V_с}{I_с}$$
> 
> где 
> + $R$ - сопротивление резистора,
> + $V_п$ - напряжение питания платы,
> + $V_с$ - напряжение работы светодиода,
> + $I_с$ - ток, потребляемый светодиодом

## Итоговый код:

```cpp
const int ledPin = 2; // пин светолиода

void setup() {
  pinMode(ledPin, OUTPUT); // объявляем пин светодиода как выход
}

void loop() {
  // мигаем светодиодом
  digitalWrite(ledPin, not digitalRead(ledPin));
  delay(500);
}
```
