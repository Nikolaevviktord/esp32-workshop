## Документация FastBot2
Библиотека может показаться сложной в использовании, как минимум гораздо сложнее FastBot первой версии =) Но это не просто так: FastBot2 позволяет использовать все возможности Телеграм и написать бота почти любой сложности, а также имеет очень удобные инструменты для обработки текстовых данных от юзеров. Для разработки рекомендуется использовать "взрослую" среду разработки типа VS Code (+Platformio), подсказки методов классов практически полностью заменят вам данную документацию.

На этой странице находится полный перечень всех классов и их методов.

### Настройки компиляции
Объявляются перед подключением библиотеки
```cpp
#define FB_NO_FILE          // убрать поддержку работы с файлами
#define FB_USE_LOG Serial   // выводить логи ошибок
```

### Указатель на текущий объект
Внутри подключаемых обработчиков можно использовать `fb::thisBot` - указатель на текущий объект бота, который вызвал обработчик

### Класс бота
<details>
<summary>FastBot2Client</summary>

Виртуальный класс без связи. Остальные классы бота наследуют его!
```cpp
// установить proxy
void setProxy(const char* host, uint16_t port);

// установить proxy
void setProxy(const IPAddress& ip, uint16_t port);

// удалить proxy
void clearProxy();

// ============================== SYSTEM ==============================
// разрешение и запрет типов обновлений
Updates updates;

// установить таймаут ожидания ответа сервера (умолч. 2000 мс)
void setTimeout(uint16_t timeout);

// ============================== SYSTEM ==============================

// автоматически декодировать юникод в тексте (умолч. true)
void decodeUCN(bool decode);

// установить токен
void setToken(const String& token);

// получить токен
const String& getToken();

// установить лимит памяти на ответ сервера (библиотека начнёт пропускать сообщения), умолч. 20000
void setMemLimit(size_t limit);

// установить лимит - кол-во сообщений в одном обновлении (умолч. 3)
void setLimit(uint8_t limit = 3);

// установить режим и период опроса (умолч. Poll::Sync и 4000 мс)
void setPollMode(Poll mode = Poll::Sync, uint16_t period = 4000);

// получить режим опроса
Poll getPollMode();

// пропустить непрочитанные сообщения, отрицательное число, соответствует количеству пропусков. Вызывать однократно
//  https://core.telegram.org/bots/api#getupdates
void skipUpdates(int32_t offset = -1);

// пропустить следующее сообщение (сдвинуть оффсет на 1)
void skipNextMessage();

// id последнего отправленного сообщения от бота
uint32_t lastBotMessage();

// авто-инкремент update offset (умолч. true). Если отключен - нужно вызывать skipNextMessage() в update
void autoIncrement(bool incr);

// автоматически отвечать на query, если юзер не ответил в update (умолч. true)
void autoQuery(bool query);

// покинуть цикл разбора updates, вызывать в обработичке update
void exitUpdates();

// запустить (по умолчанию уже запущен)
void begin();

// остановить
void end();

// указать наличие подключения к Интернет (true). При отключенном апдейты не будут запрашиваться
void setOnline(bool online);

// ============================== ATTACH ==============================

// подключить обработчик обновлений вида void cb(Update& u) {}
void onUpdate(CallbackUpdate callback);

// отключить обработчик обновлений
void detachUpdate();

// подключить обработчик результата вида void cb(gson::Entry& r) {}
void onResult(CallbackResult callback);

// отключить обработчик результата
void detachResult();

// подключить обработчик сырого ответа сервера void cb(Text response) {}
void onRaw(CallbackRaw callback);

// отключить обработчик ответа сервера
void detachRaw();

// подключить обработчик ошибки сервера void cb(Text error) {}
void onError(CallbackError callback);

// отключить обработчик ошибки
void detachError();
// ============================== TICK ==============================

// тикер, вызывать в loop. Вернёт true, если был обработан Update
bool tick();

// проверить обновления вручную (принудительно синхронно), вызовется обработчик
bool tickManual();

// система ждёт ответа с обновлениями
bool isPolling();

// отправить запрос на обновление
Result getUpdates(bool wait, bool allowLongPool = true);

// запросить перезагрузку устройства
void reboot();

// можно перезагрузить устройство
bool canReboot();

// ============================== SEND ==============================

// ответить на callback. Можно указать текст и вызвать alert
fb::Result answerCallbackQuery(const Text& id, Text text = Text(), bool show_alert = false, bool wait = true);

// переслать сообщение
fb::Result forwardMessage(const fb::MessageForward& m, bool wait = true);

// отправить сообщение
fb::Result sendMessage(const fb::Message& m, bool wait = true);

// отправить геолокацию
fb::Result sendLocation(const fb::Location& m, bool wait = true);

// ============================== FILE ==============================
// отправить файл, тип указывается в fb::File
fb::Result sendFile(const fb::File& m, bool wait = true);

// редактировать файл
fb::Result editFile(const fb::FileEdit& m, bool wait = true);

// получить прямую ссылку на файл
String getFileLink(Text fileID);

// получить путь к файлу относительно корня api
String getFilePath(Text fileID);

// обновить прошивку из файла, указать id юзера для отправки уведомления
void updateFlash(fb::DocumentRead document, Text user_id = "");

// обновить FS из файла, указать id юзера для отправки уведомления
void updateFS(fb::DocumentRead document, Text user_id = "");

// скачать файл по id
fb::Fetcher downloadFile(const Text& fileID);

// скачать файл
fb::Fetcher downloadFile(fb::DocumentRead document);

// ============================== SET ==============================

// отправить статус "набирает сообщение" на 5 секунд
fb::Result setTyping(Value chatID, bool wait = true);

// установить заголовок чата
fb::Result setChatTitle(Value chatID, Text title, bool wait = true);

// установить описание чата
fb::Result setChatDescription(Value chatID, Text description, bool wait = true);

// установить подсказки команд бота
fb::Result setMyCommands(const fb::MyCommands& commands, bool wait = true);

// удалить подсказки команд бота
fb::Result deleteMyCommands(bool wait = true);

// установить имя бота
fb::Result setMyName(const Text& name, bool wait = true);

// установить описание бота
fb::Result setMyDescription(const Text& description, bool wait = true);

// ============================== PIN ==============================

// закрепить сообщение
fb::Result pinChatMessage(Value chatID, Value messageID, bool notify = true, bool wait = true);

// открепить сообщение
fb::Result unpinChatMessage(Value chatID, Value messageID, bool wait = true);

// открепить все сообщения
fb::Result unpinAllChatMessages(Value chatID, bool wait = true);

// ============================== EDIT ==============================

// редактировать текст
// https://core.telegram.org/bots/api#editmessagetext
fb::Result editText(const fb::TextEdit& m, bool wait = true);

// редактировать заголовок (у сообщений с медиафайлом)
// https://core.telegram.org/bots/api#editmessagecaption
fb::Result editCaption(const fb::CaptionEdit& m, bool wait = true);

// редактировать меню
// https://core.telegram.org/bots/api#editmessagereplymarkup
fb::Result editMenu(const fb::MenuEdit& m, bool wait = true);

// редактировать геолокацию
fb::Result editLocation(const fb::LocationEdit& m, bool wait = true);

// остановить геолокацию
fb::Result stopLocation(const fb::LocationStop& m, bool wait = true);

// ============================== DELETE ==============================

// удалить сообщение
fb::Result deleteMessage(Value chatID, Value messageID, bool wait = true);

// удалить сообщения
fb::Result deleteMessages(Value chatID, uint32_t* messageIDs, uint16_t amount, bool wait = true);

// ============================== MANUAL ==============================

// отправить команду вручную
Result sendCommand(const __FlashStringHelper* cmd, const String& json, bool wait = true);

// отправить команду вручную без параметров
Result sendCommand(const __FlashStringHelper* cmd, bool wait = true);

// начать пакет для ручной отправки в API
Packet beginPacket(const __FlashStringHelper* cmd);

// отправить пакет
Result sendPacket(Packet& packet, bool wait = true, bool* sent = nullptr);
```
</details>
<details>
<summary>FastBot2</summary>

Версия для esp8266/esp32. Наследует `FastBot2Client` и `FastBot2Client`
```cpp
FastBot2();
```
</details>

### Чтение
<details>
<summary>fb::Update</summary>

```cpp
// fb::Update::Type
Message
EditedMessage
ChannelPost
EditedChannelPost
BusinessConnection
BusinessMessage
EditedBusinessMessage
DeletedBusinessMessages
MessageReaction
MessageReactionCount
InlineQuery
ChosenInlineResult
CallbackQuery
ShippingQuery
PreCheckoutQuery
Poll
PollAnswer
MyChatMember
ChatMember
ChatJoinRequest
ChatBoost
RemovedChatBoost
```
```cpp
// тип апдейта
Type type();

// id апдейта
uint32_t id();

// ================ QUERY ================

// это query
bool isQuery();

// query
QueryRead query();

// ================ MESSAGE ================

// сообщение
MessageRead message();

// это сообщение
bool isMessage();

// это пост в канале
bool isPost();

// это отредактированное сообщение или отредактированный пост
bool isEdited();
```
</details>
<details>
<summary>fb::MessageRead</summary>

```cpp
// ================ INFO ================

// текст сообщения
Text text();

// подпись файла
Text caption();

// id сообщения в этом чате
Text id();

// id темы в группе
Text threadID();

// сообщение отправлено в топик форума
bool isTopic();

// дата отправки или пересылки сообщения
Text date();

// дата изменения сообщения
Text editDate();

// ================ SENDER ================

// отправитель сообщения
UserRead from();

// бот, через которого пришло это сообщение
UserRead viaBot();

// чат, которому принадлежит это сообщение
ChatRead chat();

// чат, если сообщение отправлено от имени чата
ChatRead senderChat();

// ================ REPLY ================

// сообщение является ответом на сообщение
bool isReply();

// сообщение, на которое отвечает это сообщение
MessageRead reply();

// ================ FORWARD ================

// сообщение переслано из другого чата
bool isForward();

// данные о пересланном сообщении
MessageOriginRead forward();

// ================ LOCATION ================

// сообщение содержит геолокацию
bool hasLocation();

// геолокация
LocationRead location();

// ================ DOCUMENT ================

// сообщение содержит документ
bool hasDocument();

// документ
DocumentRead document();
```
</details>
<details>
<summary>fb::MessageOriginRead</summary>

```cpp
// fb::MessageOriginRead::Type
user
hiddenUser
chat
channel
```
```cpp
// тип отправителя: user, hidden_user, chat, channel
Type type();

// дата оригинального сообщения
Text date();

// отправитель type == user
UserRead senderUser();

// отправитель type == chat
ChatRead senderChat();

// отправитель type == channel
ChatRead chat();
```
</details>
<details>
<summary>fb::Result</summary>

```cpp
// наследует gson::Entry

enum class Type {
    Empty,
    OK,
    Error,
};

// освободить память
void reset();

// получить ридер
StreamReader& getReader();

// получить скачанный json пакет как Text
Text getRaw();

// тип результата
Type type();

// результат - ошибка
bool isError();

// результат пуст
bool isEmpty();

// получить текст ошибки
Text getError();

// получить код ошибки
Text getErrorCode();
```
</details>
<details>
<summary>fb::Fetcher</summary>

```cpp
// напечатать в принт
template <typename T>
bool writeTo(T& p);

// обновить прошивку (ESP)
bool updateFlash();

// обновить файловую систему (ESP)
bool updateFS();

// есть данные для чтения
int available();

// есть данные для чтения
operator bool();

Stream* stream;
```
</details>
<details>
<summary>fb::ChatRead</summary>

```cpp
// fb::ChatRead::Type
privateChat
group
supergroup
channel
```
```cpp
// id чата
Text id();

// тип чата: private_chat, group, supergroup, channel
Type type();

// название чата (для supergroups, channels, group chats)
Text title();

// имя чата (для private chats, supergroups, channels)
Text username();

// имя (для private chat)
Text firstName();

// фамилия (для private chat)
Text lastName();

// описание чата
Text description();

// в supergroup включены темы
bool isForum();
```
</details>
<details>
<summary>fb::DocumentRead</summary>

```cpp
// id документа, можно использовать для скачивания
Text id();

// уникальный id документа в системе
Text uniqueID();

// имя документа
Text name();

// MIME тип документа
Text type();

// размер документа
Text size();
```
</details>
<details>
<summary>fb::LocationRead</summary>

```cpp
// широта
Text latitude();

// долгота
Text longitude();

// точность в метрах, 0-1500
Text horizontalAccuracy();

// Время относительно даты отправки сообщения в секундах, в течение которого местоположение может быть обновлено
Text livePeriod();

// направление в градусах, 1-360
Text heading();

// Максимальное расстояние в метрах для оповещений о приближении к другому участнику чата
Text proximityAlertRadius();
```
</details>
<details>
<summary>fb::UserRead</summary>

```cpp
// id юзера
Text id();

// бот или нет
bool isBot();

// имя
Text firstName();

// фамилия
Text lastName();

// юзернейм
Text username();

// код страны https://en.wikipedia.org/wiki/IETF_language_tag
Text languageCode();

// true - премиум юзер
bool isPremium();
```
</details>
<details>
<summary>fb::QueryRead</summary>

```cpp
// callback id
Text id();

// callback data
Text data();

// отправитель коллбэка
UserRead from();

// сообщение
MessageRead message();
```
</details>

### Отправка
<details>
<summary>fb::Message</summary>

```cpp
// fb::Message::Mode
Text
MarkdownV2
HTML
```
```cpp
Message();
Message(const String& text, Value chatID);

// для ручного добавления тех параметров, которых нет в классе!
gson::Str json;

// текст сообщения
String text;

// id чата, куда отправлять
Value chatID;

// id темы в группе, куда отправлять
int32_t threadID = -1;

// параметры ответа на сообщение
ReplyParam reply;

// включить превью для ссылок
bool preview = previewDefault;

// уведомить о получении
bool notification = notificationDefault;

// защитить от пересылки и копирования
bool protect = protectDefault;

// режим текста: Text, MarkdownV2, HTML
Mode mode = modeDefault;

// добавить обычное меню
void setMenu(Menu& menu);

// добавить инлайн меню
void setInlineMenu(InlineMenu& menu);

// удалить обычное меню
void removeMenu();

// установить режим текста Markdown
void setModeMD();

// установить режим текста HTML
void setModeHTML();

// ===================================

// включить превью для ссылок (умолч. 1)
static bool previewDefault;

// уведомить о получении (умолч. 1)
static bool notificationDefault;

// защитить от пересылки и копирования (умолч. 0)
static bool protectDefault;

// режим текста: Text, MarkdownV2, HTML (умолч. Text)
static Mode modeDefault;
```
</details>
<details>
<summary>fb::ReplyParam</summary>

```cpp
// id сообщения, на которое отвечаем
int32_t messageID = -1;

// id чата, в котором находится сообщение, на которое отвечаем
Value chatID;
```
</details>

<details>
<summary>fb::MessageForward</summary>

```cpp
MessageForward();
MessageForward(uint32_t messageID, Value fromChatID, Value chatID);

// id пересылаемого сообщения в чате
uint32_t messageID;

// id чата пересылаемого сообщения
Value fromChatID;

// id чата, в который пересылать
Value chatID;

// id темы в группе, в которую переслать
int32_t threadID = -1;

// уведомить о получении
bool notification = Message::notificationDefault;

// защитить от пересылки и копирования
bool protect = Message::protectDefault;

// для ручного добавления тех параметров, которых нет в классе!
gson::Str json;
```
</details>
<details>
<summary>fb::MyCommands</summary>

```cpp
MyCommands();
MyCommands(const String& commands, const String& description);

// список команд, длина команды 1-32, разделитель ;
String commands = "";

// список описаний команд, длина описания 1-256, разделитель ;
String description = "";

// зарезервировать строки
void reserve(uint16_t len);

// добавить команду
void addCommand(const String& command, const String& description);
```
</details>
<details>
<summary>fb::File</summary>

```cpp
// fb::File::type
photo
audio
document
video
animation
voice
video_note
```
```cpp
// отправить fs::File файл
File(Text name, Type type, ::File& file);

// отправить данные из byte буфера
File(Text name, Type type, uint8_t* bytes, size_t length, bool progmem = false);

// отправить по ID файла в телеге или ссылкой (для document только GIF, PDF и ZIP)
// https://core.telegram.org/bots/api#sending-files
File(Text name, Type type, Text urlid);

using Message::chatID;
using Message::mode;
using Message::notification;
using Message::protect;
using Message::reply;
using Message::setInlineMenu;
using Message::threadID;
using Message::json;

// заголовок
String caption;
```
</details>
<details>
<summary>fb::Menu</summary>

```cpp
Menu();
Menu(const String& text);

// надписи кнопок. Гор. разделитель - ;, верт. - \n (кнопка_1 ; кнопка_2 \n кнопка_3 ; кнопка_4)
String text = "";

// подсказка, показывается в поле ввода при открытой клавиатуре (до 64 символов)
String placeholder = "";

// принудительно показывать клавиатуру
bool persistent = persistentDefault;

// уменьшить клавиатуру под количество кнопок
bool resize = resizeDefault;

// автоматически скрывать после нажатия
bool oneTime = oneTimeDefault;

// показывать только упомянутым в сообщении юзерам
bool selective = selectiveDefault;

// добавить кнопку
Menu& addButton(Text text);

// перенести строку
Menu& newRow();

// ===================================

// принудительно показывать клавиатуру (умолч. 0)
static bool persistentDefault;

// уменьшить клавиатуру под количество кнопок (умолч. 0)
static bool resizeDefault;

// автоматически скрывать после нажатия (умолч. 0)
static bool oneTimeDefault;

// показывать только упомянутым в сообщении юзерам (умолч. 0)
static bool selectiveDefault;
```
</details>
<details>
<summary>fb::InlineMenu</summary>

```cpp
InlineMenu();
InlineMenu(const String& text, const String& data);
InlineMenu(uint16_t reserve);

// надписи кнопок. Гор. разделитель - ;, верт. - \n (кнопка_1 ; кнопка_2 \n кнопка_3 ; кнопка_4)
String text = "";

// callback data кнопок с разделителем ; . Поддерживаются url адреса
String data = "";

// зарезервировать строки
void reserve(uint16_t len);

// добавить кнопку
InlineMenu& addButton(Text text, Text data = Text());

// перенести строку
InlineMenu& newRow();
```
</details>
<details>
<summary>fb::Location</summary>

```cpp
Location();
Location(float latitude, float longitude, Value chatID);

using Message::chatID;
using Message::notification;
using Message::protect;
using Message::removeMenu;
using Message::reply;
using Message::setInlineMenu;
using Message::setMenu;
using Message::threadID;
using Message::json;

// широта
float latitude;

// долгота
float longitude;

// точность в метрах, 0-1500
float horizontalAccuracy = NAN;

// период обновления локации в секундах 60.. 86400
uint32_t livePeriod = 0;

// направление в градусах, 1-360
uint16_t heading = 0;

// Максимальное расстояние в метрах для оповещений о приближении к другому участнику чата
uint32_t proximityAlertRadius = 0;
```
</details>

### Редактирование
<details>
<summary>fb::FileEdit</summary>

```cpp
FileEdit(Text name, Type type, File& file);
FileEdit(Text name, Type type, uint8_t* bytes, size_t length, bool progmem = false);

// document by url - GIF, PDF and ZIP
// https://core.telegram.org/bots/api#sending-files
FileEdit(Text name, Type type, Text urlid);

// id сообщения
uint32_t messageID;

using File::caption;
using File::chatID;
using File::multipart;
using Message::setInlineMenu;
using Message::json;
```
</details>
<details>
<summary>fb::TextEdit</summary>

```cpp
TextEdit();
TextEdit(const String& text, uint32_t messageID, Value chatID);

// id сообщения
uint32_t messageID;

using Message::chatID;
using Message::mode;
using Message::preview;
using Message::setInlineMenu;
using Message::text;
using Message::json;
```
</details>
<details>
<summary>fb::MenuEdit</summary>

```cpp
MenuEdit();
MenuEdit(uint32_t messageID, Value chatID);
MenuEdit(uint32_t messageID, Value chatID, InlineMenu& menu);

// id сообщения
uint32_t messageID;

using Message::chatID;
using Message::setInlineMenu;
using Message::json;
```
</details>
<details>
<summary>fb::CaptionEdit</summary>

```cpp
CaptionEdit();
CaptionEdit(const String& caption, uint32_t messageID, Value chatID);

// заголовок
String caption;

// id сообщения
uint32_t messageID;

using Message::chatID;
using Message::mode;
using Message::setInlineMenu;
using Message::json;
```
</details>
<details>
<summary>fb::LocationEdit</summary>

```cpp
LocationEdit();
LocationEdit(float latitude, float longitude, uint32_t messageID, Value chatID);

// широта
float latitude;

// долгота
float longitude;

// id сообщения
uint32_t messageID;

// точность в метрах, 0-1500
float horizontalAccuracy = NAN;

// направление в градусах, 1-360
uint16_t heading = 0;

// Максимальное расстояние в метрах для оповещений о приближении к другому участнику чата
uint32_t proximityAlertRadius = 0;

using Message::chatID;
using Message::setInlineMenu;
using Message::json;
```
</details>
<details>
<summary>fb::LocationStop</summary>

```cpp
LocationStop();
LocationStop(uint32_t messageID, Value chatID);

// id сообщения
uint32_t messageID;

using Message::chatID;
using Message::setInlineMenu;
using Message::json;
```
</details>

### Прочее
<details>
<summary>fb::Poll</summary>

```cpp
Sync   // синхронный (рекомендуемый период > 3500 мс)
Async  // асинхронный (рекомендуемый период > 3500 мс)
Long   // асинхронный long polling (рекомендуемый период > 20000 мс)
```
</details>
<details>
<summary>fb::Updates</summary>

```cpp
// fb::Updates::Type
Message
EditedMessage
ChannelPost
EditedChannelPost
BusinessConnection
BusinessMessage
EditedBusinessMessage
DeletedBusinessMessages
MessageReaction
MessageReactionCount
InlineQuery
ChosenInlineResult
CallbackQuery
ShippingQuery
PreCheckoutQuery
Poll
PollAnswer
MyChatMember
ChatMember
ChatJoinRequest
ChatBoost
RemovedChatBoost
```
```cpp
// установить
void set(uint32_t nmods);

// очистить
void clear(uint32_t nmods);

// включить все
void setAll();

// очистить все
void clearAll();

// прочитать по типу
bool read(Type m);

// прочитать по индексу
bool read(uint8_t idx);
```
</details>

