## Отправка
В данной библиотеке, в отличие от многих других, отправка запроса на сервер Telegram идёт не через *query string*, а в теле запроса типа *application/json*. Это означает, что отправляемый текст не должен быть *urlencoded* и не имеет прочих ограничений, и может отправляться в неизменном виде - это сильно экономит время и ресурс контроллера. Также это избавляет от проблем с отправкой сообщений в стилях `HTML` и `Markdown`.

### ID чата
В большинстве команд отправки нужен id чата - уникальный номер чата или группы в Telegram. Это число выходит за рамки типа данных `long`, поэтому в библиотеке используется тип данных `fb::ID`. Он принимает как числа, так и строки:

```cpp
fb::ID id;
id = "1234567898765";
id = 1234567898765;
id = u.message().from().id();
```

При разборе обновлений id чата является типом `Text`, который в свою очередь может конвертироваться в `int64_t`:

```cpp
int64_t chat_id;

void update(fb::Update& u) {
    u.message().from().id() == 12345678ll;  // сравнение
    chat_id = u.message().from().id();      // сохранение в переменную
}
```

Для отправки можно использовать id в любом виде.

### Отправка сообщений
FastBot2 удобно оборачивает почти весь API по отправке сообщения в класс `fb::Message`. Типичный сценарий использования:
- Создать `fb::Message`
- Заполнить обязательные параметры - `text` и `chatID`
- По желанию заполнить другие параметры
- Отправить в `sendMessage`

```cpp
fb::Message msg;
msg.text = "some text";
msg.chatID = 123456677889;  // или в виде "строки"
bot.sendMessage(msg);
```

Возможна укороченная запись, `Message` имеет конструктор с минимальными обязательными параметрами:

```cpp
bot.sendMessage(fb::Message("hello!", "12312424353"));
```

### Асинхронность и ID сообщения
ID отправленного ботом сообщения можно получить из `lastBotMessage()`. Нужно понимать, что у каждого чата свой счётчик ID сообщений. Библиотека получает ID отправленного сообщения из ответа сервера, поэтому есть несколько важных моментов.

Сообщение может быть отправлено двумя способами:
- **Синхронно** (по умолчанию) - библиотека ждёт и обрабатывает ответ сервера внутри отправки сообщения, поэтому сразу после вызова `sendMessage` функция `lastBotMessage()` возвращает актуальный ID отправленного сообщения
- **Асинхронно** - библиотека не ждёт ответа от сервера и получит его в следующем `tick()`, т.е. `lastBotMessage()` *не выдаст* достоверный ID сразу после отправки

> При отправке нескольких асинхронных сообщений подряд библиотека принудительно будет ждать ответ сервера для каждого предыдущего сообщения, т.е. сделает их синхронными, чтобы избежать переподключения к серверу

```cpp
fb::Message msg("hello", 1234567);
bot.sendMessage(msg, false);            // асинхронно
Serial.println(bot.lastBotMessage());   // ID может быть некорректным

bot.sendMessage(msg);                   // синхронно
// библиотека дождётся ответа от предыдущего сообщения перед отправкой нового
Serial.println(bot.lastBotMessage());   // реальный ID
```

### Редактирование сообщений
Для редактирования текста сообщений используется следующая конструкция:
```cpp
fb::TextEdit et;
et.text = "edited text";
et.chatID = 123423234;
et.messageID = 234;
bot.editText(et);
```

Вот так например бот будет удалять сообщения юзера и вместо этого менять текст своего последнего сообщения на текст сообщения юзера:

```cpp
// удалить сообщение юзера
bot.deleteMessage(u.message().chat().id(), u.message().id());

// редактировать
if (bot.lastBotMessage()) {
    fb::TextEdit et;
    et.text = u.message().text().toString();
    et.chatID = u.message().chat().id();
    et.messageID = bot.lastBotMessage();
    bot.editText(et);
} else {
    // отправить сообщение, если бот не знает id своего последнего сообщения
    bot.sendMessage(fb::Message(u.message().text(), u.message().chat().id()));
}
```

Отдельно можно редактировать меню сообщения через `MenuEdit`, см. следующую страницу документации.

### Отправка нескольким ID
Если ID хранятся в текстовом виде в виде CSV списка, то можно использовать парсер `Text`:
```cpp
fb::Message msg;
msg.text = "hello!";

su::TextParser ids("546343285;1234853;8796453678;38347567", ';');
while (ids.parse()) {
    msg.chatID = ids;
    bot.sendMessage(msg);
}
```

Если id - это массив `int64_t` - то всё проще:

```cpp
int64_t ids[..];    // массив id
int ids_len;        // фактическая длина

// ...
fb::Message msg;
msg.text = "hello!";

for (int i = 0; i < ids_len; i++) {
    msg.chatID = ids[i];
    bot.sendMessage(msg);
}
```

### Форматирование
Режимы форматирования текста HTML и Markdown поддерживают только конкретные теги, см. API Telegram:
- [HTML](https://core.telegram.org/bots/api#html-style)
- [Markdown](https://core.telegram.org/bots/api#markdownv2-style)

Для настройки режима нужно просто указать его:

```cpp
fb::Message msg;
msg.mode = fb::Message::Mode::MarkdownV2;
msg.text...
```

#### Markdown
Для режима Markdown нужно соблюдать [некоторые правила](https://core.telegram.org/bots/api#markdownv2-style):
- Любой символ может быть экранирован с помощью `\`, чтобы выводиться **просто символом**, а не разметкой MD. Например `"test\\_"` выведет `test_`, без экранирования будет ошибка отправки
- Внутри блоков кода символы `` ` `` и `\` должны быть экранированы с помошью `\`
- Внутри блока ссылки в (круглых скобках) все `)` и `\` должны быть экранированы с помошью `\`
- Во всех остальных случаях символы `_`, `*`, `[`, `]`, `(`, `)`, `~`, `` ` ``, `>`, `#`, `+`, `-`, `=`, `|`, `{`, `}`, `.`, `!` должны быть экранированы с помошью `\` (чтобы выводиться как символы, а не как форматирование)

> FastBot2 не экранирует символы! Это нужно делать самостоятельно
> Например для вывода **текста** `[hello] - world!` нужно писать `"\\[hello\\] \\- world\\!"`

## Отправка отдельным клиентом
FatsBot2 использует один TCP клиент для максимальной скорости работы (минимальное количество подключений и переподключений к серверу). В многопоточных системах можно использовать отдельный экземпляр бота для отправки сообщений вне обработчика апдейта, т.е. первый объект занимается опросом апдейтов, а второй можно использовать для отправки сообщений из любого места в программе:

```cpp
FastBot2 botUpd;

void loop() {
    botUpd.tick();
}

void sendMsg() {
    FastBot2 bot(token...);
    bot.sendMessage...
}
```

## Отправка вручную
Библиотека поддерживает самостоятельную сборку пакетов для отправки на сервер согласно API Telegram. Для сборки используется линейный сборщик json строк `gson::Str` - вот [документация](https://github.com/GyverLibs/GSON). Создание и отправка пакета выглядит так:
- Начать пакет с указанием [команды](https://core.telegram.org/bots/api#available-methods)
- Собрать пакет, указав нужные данные
- Отправить пакет

Отправка сообщения в чат:

```cpp
// Все команды API Telegram доступны в tg_cmd
fb::Packet p = bot.beginPacket(tg_cmd::sendMessage);

// все ключи объектов API Telegram доступны в tg_api
p[tg_api::text] = "message text";
p[tg_api::chat_id] = 12312341231;
bot.sendPacket(p);
```

Установка команд бота, способ 1 (с элементом json строки):

```cpp
fb::Packet p = bot.beginPacket(tg_cmd::setMyCommands);
p[tg_api::commands]('[');
p.concat(R"(
{"command":"help","description":"Помощь по командам"},
{"command":"info","description":"Информация о настройках"})");
p(']');
```

Установка команд бота, способ 2 (полностью нативная сборка):

```cpp
fb::Packet p = bot.beginPacket(tg_cmd::setMyCommands);
p[tg_api::commands]('[');
if (p('{')) {
    p[tg_api::command] = "help";
    p[tg_api::description] = "Помощь по командам";
    p('}');
}
if (p('{')) {
    p[tg_api::command] = "info";
    p[tg_api::description] = "Информация о настройках";
    p('}');
}
p(']');
bot.sendPacket(p);
```

### Второй способ
Подходит для json пакетов, собранных отдельно. Использует больше памяти, чем `beginPacket`-`sendPacket` (дублирует пакет перед отправкой). Отправлять можно как json объект вида `{"key":"value"...}`, так и список значений без фигурных скобок (библиотека добавит их сама): `"key":"value"...`. Например:

```cpp
// свой пакет
bot.sendCommand(tg_cmd::sendMessage, "{\"chat_id\":1234567864,\"text\":\"hello text\"}");

// сборка в gson::Str
gson::Str g;
g[tg_api::chat_id] = 1234567864;
g[tg_api::text] = "hello text";
bot.sendCommand(tg_cmd::sendMessage, g);
```

### Дополнение стандартных типов
Во всех стандартных типах библиотеки (Message, Location и проч.) есть поле `json`, в которое можно добавлять данные, не предусмотренные библиотекой, но предусмотренные Telegram API. Например:

```cpp
fb::Message msg("version 3", CHAT_ID);
msg.json[tg_api::business_connection_id] = "12345";
msg.json[tg_api::message_effect_id] = "asdadawdwd";
bot.sendMessage(msg);
```

> Важный момент - нельзя добавлять данные, которые добавляются библиотекой, например поля `text` и `chat_id` - телеграм не примет такой запрос с дублирующимися ключами!

## Разбор ответа сервера
Все методы отправки запросов возвращают результат типа `fb::Result` - если запрос был синхронный (по умолчанию), то в результате будет распарсенный ответ сервера. Это позволяет отправлять запросы и получать результат на следующей же строчке кода. Например запрос `getMe`:

```cpp
fb::Result res = bot.sendCommand(tg_cmd::getMe);
Serial.println(res[tg_apih::first_name]);  // имя бота
Serial.println(res[tg_apih::username]);    // ник бота
// res.stringify(Serial);                 // вывести весь пакет
// Serial.println(res.getRaw());          // вывести ответ сервера текстом как он есть
```

### Разбор ошибок
`Result` имеет три типа результата: данные получены, ошибка Телеграм, пустой результат. Наиболее компактно определить тип можно так:

```cpp
fb::Result res = bot.sendCommand...

if (res) {                           // корректный результат
    Serial.println(res);             // stringify в порт
} else if (res.isError()) {          // ошибка
    Serial.println(res.getError());  // вывод текста ошибки
} else {                             // пустой результат
    Serial.println("empty!");        // пусто
}
```

или так:

```cpp
switch (res.type()) {
    case fb::Result::Type::OK:
        Serial.println(res);
        break;
        
    case fb::Result::Type::Error:
        Serial.println(res.getError());
        break;

    case fb::Result::Type::Empty:
        Serial.println("Empty");
        break;
}
```

> Пустой результат будет получен также в случае асинхронной отправки

### Асинхронно
Для получения результата от асинхронной команды нужно подключить обработчик:

```cpp
bot.onResult([](fb::Result& res) {
    if (res) Serial.println(res);
    else Serial.println(res.getError());
});
```

### Оптимизация
Для уменьшения использования оперативной памяти рекомендуется оборачивать все запросы с разбором результата в блоки кода `{}`, чтобы результат освобождал память после использования:

```cpp
{
    fb::Result res = bot.sendCommand(tg_cmd::getMe);
    Serial.println(res[tg_apih::first_name]);
}
{
    gson::Str g;
    g[tg_api::chat_id] = 1234567864;
    fb::Result res = bot.sendCommand(tg_cmd::getChat, g);
    Serial.println(res[tg_apih::title]);
}
{
    fb::Result res = bot.sendMessage(fb::Message("hello!", "12312424353"));
    res.stringify(Serial);
}
```

Также освободить память можно, вызвав `reset()`:

```cpp
fb::Result res1 = bot.sendCommand(tg_cmd::getMe);
Serial.println(res1[tg_apih::first_name]);
res1.reset();

gson::Str g;
g[tg_api::chat_id] = 1234567864;
fb::Result res2 = bot.sendCommand(tg_cmd::getChat, g);
Serial.println(res2[tg_apih::title]);
res2.reset();

fb::Result res3 = bot.sendMessage(fb::Message("hello!", "12312424353"));
res3.stringify(Serial);
res3.reset();
```
