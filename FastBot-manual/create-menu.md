## Работа с меню
В телеграм есть два типа меню:
- Большая клавиатура в самом низу чата - нажатие на кнопку отправляет в чат текст с этой кнопки, он приходит боту как обычное сообщение
- Инлайн-клавиатура - клавиатура, прикреплённая к сообщению. Кнопка может выполнять множество действий ([документация](https://core.telegram.org/bots/api#inlinekeyboardbutton)), они все доступны при ручной сборке пакета. В FastBot2 удобно реализованы только ссылки и callback data

### Клавиатура
Вызов клавиатуры является отправкой сообщения, т.е. прикрепляется к обычному сообщению `Message`. **Текст сообщения должен быть указан обязательно**, иначе Телеграм проигнорирует сообщение.

Вручную:
```cpp
fb::Message msg("Show menu!", "id чата");

fb::Menu menu;
// задаётся в CSV: горизонтальный разделитель ; вертикальный - \n
menu.text = "kek 1 ; kek 2 ; kek 3 \n kek 4 ; kek 5";
menu.resize = 1;
menu.placeholder = "Fancy placeholder";
msg.setMenu(menu);  // подключить меню

// отправить
bot.sendMessage(msg);
```

Билдер:
```cpp
fb::Message msg("Show menu!", "id чата");

fb::Menu menu;
// newRow переносит "строку" кнопок
menu.addButton("kek 1").addButton("kek 2").newRow();
menu.addButton("kek 3");
msg.setMenu(menu);  // подключить меню

// отправить
bot.sendMessage(msg);
```

#### Скрыть клавиатуру
Скрытие также прикрепляется к сообщению:
```cpp
fb::Message msg("Hide menu!", "id чата");
msg.removeMenu();

bot.sendMessage(msg);
```

> Редактировать клавиатуру нельзя, можно отправить новую

### Инлайн клавиатура
- При указании `data` как текста, который начинается с `http://`/`https://`/`tg://`, кнопка будет преобразована в кнопку-ссылку
- При указании текста `data` он становится callback data и придёт в обновление
- Если не указывать `data` - callback data будет соответствовать тексту на кнопке

Вручную:
```cpp
fb::Message msg("Show menu!", "id чата");

fb::InlineMenu menu("kek 1 ; kek 2 ; kek 3 \n kek 4 ; kek 5", "test;pest;lol;https://www.google.ru/;https://www.yandex.ru/");
msg.setInlineMenu(menu);  // подключить меню

// отправить
bot.sendMessage(msg);
```

Билдер:
```cpp
fb::Message msg("Show menu!", "id чата");

fb::InlineMenu menu;
menu.addButton("BUTTON 1");  // если data не указана - она становится текстом на кнопке
menu.addButton("BUTTON 2", "data_2");  // callback data
menu.newRow();
menu.addButton("BUTTON 3", "https://www.google.ru/");   // кнопка-ссылка
msg.setInlineMenu(menu);  // подключить меню

// отправить
bot.sendMessage(msg);
```

#### Ответ на query
Если нажать на кнопку с callback data - телеграм отправит query update. На кнопке будет анимация загрузки, пока бот не ответит на запрос. Для ответа на запрос нужно передать query id из апдейта в `answerCallbackQuery`. 

> Если не ответить на query - библиотека ответит сама, пустым ответом

```cpp
void update(fb::Update& u) {
    if (u.isQuery()) {
        Serial.println(u.query().data());   // вывести data

        // быстрое "сравнение" строк и поиск нужной даты
        switch (u.query().data().hash()) {
            case SH("data1"):
                // ...
                break;
            case SH("data2"):
                // ...
                break;
            case SH("data3"):
                // ...
                break;
        }

        // ответ на query
        // bot.answerCallbackQuery(u.query().id());                 // пустой
        // bot.answerCallbackQuery(u.query().id(), "hello!");       // с текстом
        bot.answerCallbackQuery(u.query().id(), "hello!", true);    // со всплывающим окошком
    }
}
```

#### Изменение клавиатуры
```cpp
fb::MenuEdit edit;
edit.messageID = 1234;
edit.chatID = 253453234;

fb::InlineMenu menu;
// ...
edit.setInlineMenu(menu);

bot.editMenu(edit);
```

Короткая запись
```cpp
fb::InlineMenu menu;
// ...

bot.editMenu(fb::MenuEdit(124, "chat id", menu));
```

Пример изменения сообщения с меню по query коллбэку, меняется текст и меню. Тут можно добавить или убрать меню:
```cpp
fb::TextEdit t;
t.text = "New message + new menu";
t.chatID = u.query().message().chat().id();
t.messageID = u.query().message().id();
fb::InlineMenu menu("kek 1;kek 2;kek 3", "1;2;3");
t.setInlineMenu(menu);
bot.editText(t);
```

Пример изменения сообщения с меню по query коллбэку, меняется только меню:
```cpp
fb::MenuEdit m;
m.chatID = u.query().message().chat().id();
m.messageID = u.query().message().id();
fb::InlineMenu menu("pepe 1;pepe 2;pepe 3", "11;22;33");
m.setInlineMenu(menu);
bot.editMenu(m);
```
