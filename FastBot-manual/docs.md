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

## Базовая информация о ТГ ботах
Телеграм-бот - виртуальный пользователь Телеграм, действиями которого можно управлять из программы, в данном случае - с Ардуины/ЕСПшки. Работает это довольно просто: программа отправляет запрос на сервер Телеграм, сервер отвечает результатом. Программа может как запросить непрочитанные сообщения, так и отправить сообщение от лица бота.

### Регистрация бота
- Написать Бате https://t.me/BotFather
- Открыть меню, выбрать команду `/newbot`
- Отправить имя бота (потом его можно будет изменить)
- Отправить никнейм бота: уникальное имя, оканчивающееся на `bot`. Изменить его будет нельзя
- Готово! Батя выдаст вам **токен** бота - уникальный код, по которому и ведётся работа с ботом

### Настройка бота
- Перейти в чат с **BotFather**, выбрать бота для редактирования
- `Webhook` режим должен быть отключен (отключен по умолчанию, если не трогали - не трогайте), иначе esp не сможет принимать сообщения
- Для того, чтобы бот читал все сообщения в группе (а не только /команды), нужно отключить параметр **Group Privacy** в настройках бота **Bot Settings**. Данный параметр включен по умолчанию
- Для полноценной работы в группе (супергруппе) бота нужно сделать администратором в этой группе

### Лимиты Telegram
Телеграм устанавливает следующие [лимиты](https://core.telegram.org/bots/faq#my-bot-is-hitting-limits-how-do-i-avoid-this) на взаимодействие с ботом:

#### Отправка
- В личный чат: не чаще раза в секунду. *Отправлять чаще можно, но сообщение может не дойти*
- В группу: не чаще 20 сообщений в минуту
- Суммарный лимит: не чаще 30 сообщений в секунду
- Бот не может писать в личку другому боту

#### Чтение
- Бот может читать и взаимодействовать с сообщениями (изменять, удалять), с момента отправки которых прошло **не больше 24 часов**
- Бот [не видит](https://core.telegram.org/bots/faq#why-doesn-39t-my-bot-see-messages-from-other-bots) сообщения от других ботов в группе
- Телеграм разделяет текст на несколько сообщений, если длина текста превышает ~4000 символов. Эти сообщения будут иметь разный messageID в чате
- Нельзя опрашивать обновления одновременно с нескольких устройств: один бот - одна Ардуина/ЕСПшка. Отправлять команды с нескольких устройств - можно

#### Сообщения от себя
Бот не видит, т.е. не получает апдейты на свои сообщения. Это ограничение можно обойти:
- Создать частный канал, добавить туда бота, сделать админом
- Создать частную группу, добавить туда бота, сделать админом
- В настройках канала привязать группу к каналу как "обсуждение"

Теперь если бот напишет пост в *канал* - ему придёт апдейт с этим постом из *группы* (считается сообщением, которое переслал "юзер" Telegram). Таким образом можно передать боту информацию с одного сервера на другой через Телеграм (*только в одну сторону*). Можно настроить автоудаление постов, чтобы не забивать канал.

#### Сообщения от других ботов
Бот не видит, т.е. не получает апдейты на сообщения других ботов. Это ограничение можно обойти:
- Создать частный канал, добавить туда ботов, сделать админами
- Отправить пост через бота
- Все остальные боты получат апдейт с постом

Таким образом можно передавать данные между ботами через Телеграм. Можно настроить автоудаление постов, чтобы не забивать канал.

## Начало работы
### ESP8266/ESP32
Библиотека нативно поддерживает МК ESPxx классом `FastBot2`:

```cpp
#include <FastBot2.h>
FastBot2 bot;
// FastBot2 bot("токен");
```

Для подключения к WiFi можно использовать типичную конструкцию:

```cpp
void setup() {
    Serial.begin(115200);

    WiFi.begin("WIFI_SSID", "WIFI_PASS");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
}
```

### Другие платформы
Библиотека работает напрямую с `Arduino Client` интерфейсом, поэтому можно подключить любую библиотеку, которая предоставляет к нему доступ (для Ethernet, GPRS и так далее). Для этого используется класс `FastBot2Client`:

```cpp
SomeClient client;

#include <FastBot2Client.h>
FastBot2Client bot(client);
```

Пример с [TinyGSM](https://github.com/vshymanskyy/TinyGSM):

```cpp
// обязательно нужен модем с поддержкой HTTPS
#define TINY_GSM_MODEM_SIM7000SSL
#include <TinyGsmClient.h>
TinyGsm modem(Serial);
TinyGsmClient gsmclient(modem);

#include <FastBot2Client.h>
FastBot2Client bot(gsmclient);
```

### Настройка бота
```cpp
void setup() {
    // ОБЯЗАТЕЛЬНЫЕ
    bot.setToken("token");  // установка токена
    // bot.setToken(F("token")); // любым текстовым способом

    // НЕОБЯЗАТЕЛЬНЫЕ (указаны настройки по умолчанию)
    bot.skipUpdates(-1);    // пропустить все входящие обновления
    bot.setLimit(3);        // максимум сообщений в одном обновлении (экономия памяти)
    bot.setPollMode(fb::Poll::Sync, 4000);  // настройка метода опроса (об этом ниже)
}
```

## Получение обновлений
Под *обновлением* понимаются:
- Сообщения и бизнес сообщения, отправленные/пересланные/отредактированные в личке/группе/канале с ботом
- Опросы
- Реакции, бусты, уведомления о присоединении юзера
- Callback запросы

По умолчанию включены все типы обновлений, но можно выбрать конкретные:
```cpp
// сначала очистить все
bot.updates.clearAll();

// и включить нужные
bot.updates.set(fb::Updates::Type::Message | fb::Updates::Type::ChannelPost);

// можно отключить только ненужные
bot.updates.set(fb::Updates::Type::ShippingQuery | fb::Updates::Type::PreCheckoutQuery);
```

### Обработчик
Для получения обновлений нужно подключить обработчик и вызывать тикер в главном цикле программы:

```cpp
// обработчик
void update(fb::Update& u) {
}

void setup() {
    bot.onUpdate(update);
}

void loop() {
    bot.tick();
}
```

Подробнее разбор обновлений описан в следующей главе документации

> Указатель на текущий объект FastBot (тот, который вызвал коллбэк) можно получить из переменной `fb::Core* fb::thisBot`. Кастовать его в нужный класс и использовать:

```cpp
void update(fb::Update& u) {
    static_cast<FastBot2*>(fb::thisBot)->sendMessage(...);
}
```

### Минимальный код (для esp)
```cpp
#define WIFI_SSID ""
#define WIFI_PASS ""
#define BOT_TOKEN ""

#include <FastBot2.h>
FastBot2 bot;

void update(fb::Update& u) {
}

void setup() {
    // ==============
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    // ==============

    bot.setToken(BOT_TOKEN);
    bot.onUpdate(update);
    // bot.setPollMode(fb::Poll::Long, 60000);
}

void loop() {
    bot.tick();
}
```

## Метод опроса обновлений
### `Sync` (по умолчанию)
```cpp
bot.setPollMode(fb::Poll::Sync, 4000);
```

#### Обновление
Такой же режим, как в первой версии FastBot: библиотека запрашивает обновления и ждёт ответа внутри `tick()`. При плохой связи может "зависать" внутри `tick()` на ощутимое (не дольше таймаута) время. Ставить период меньше `4000` не рекомендуется - сервер Телеграм "накажет" долгим ответом за слишком частый опрос!

#### Отправка сообщений
Отправка сообщений будет быстрой в любом месте программы, т.к. библиотека не ждёт ответа от сервера.

### `Async`
```cpp
bot.setPollMode(fb::Poll::Async, 4000);
```

#### Обновление
"Асинхронный" режим - библиотека запросит обновления и обработает ответ, когда он придёт. Период опроса - такая же особенность, как в `Sync`.

#### Отправка сообщений
Если отправить сообщение НЕ в обработчике обновления и ВО ВРЕМЯ ожидания ответа с обновлением - библиотека переподключится к серверу, что занимает около 1 секунды и блокирует выполнение программы. Для безопасной отправки из любого места в программе нужно отправлять сообщения, когда библиотека не ждёт ответа - проверить можно по флагу `isPolling()`.

### `Long`
```cpp
bot.setPollMode(fb::Poll::Long, 60000);
```

#### Обновление
Самый правильный способ опроса - асинхронный *long polling*. Период можно ставить побольше - от 20 секунд. Библиотека отправляет запрос и получит ответ либо по указанному таймауту, либо по факту поступления новых сообщений в бота. Таймаут переподключения - по умолчанию 300мс. Это самый быстрый и безопасный способ получения обновлений, сообщения доставляются мгновенно.

#### Отправка сообщений
Отправка сообщений в обработчике обновлений - безопасна, сообщения будут отправлены быстро. Если нужно отправить из другого места программы - по флагу `isPolling()` можно узнать, ждёт ли библиотека ответ сервера. Если отправить пока ждёт - будет переподключение ("зависнет" на ~1 секунду). Также `tick()` вернёт `true`, когда были обработаны обновления, в этом условии безопасно делать отправку.

## Разбор обновлений
Обновления попадают в подключенный обработчик:

```cpp
void update(fb::Update& u) {
}
```

Каждый вызов этой функции - одно "сообщение" от бота. Здесь `fb::Update` - это класс, в котором удобно доступны самые основные инструменты для работы с ботом и с сообщениями, как в виде значений, так и в виде вложенных классов. В "ручном режиме" разбора JSON библиотека поддерживает весь [Telegram Bot API](https://core.telegram.org/bots/api) и позволяет получать из обновлений все возможные данные.

Например выведем текст сообщения:

```cpp
void update(fb::Update& u) {
    Serial.println(u.message().text());
}
```

Отличие FastBot2 состоит в том, что библиотека не разбирает пакет обновления по отдельным переменным: данные извлекаются в момент обращения к ним. Это сильно быстрее и расходует в сотни раз меньше памяти.

### Тип данных Text
Все значения, которые можно получить из обновления (вручную ил из Update), представлены типом данных `Text` - "обёртка" для текстовых данных, которые хранятся где-то в памяти (в данном случае в буфере ответа сервера Телеграм). `Text` позволяет:
- Печататься в любой `Print` (например `Serial`)
- Сравниваться со строками любого типа
- Экспортироваться в любой тип данных
- Имеет декодер Unicode (для кириллицы и смайликов)
- Может посчитать свой хэш для быстрого сравнения строк

> Это очень мощный инструмент! Рекомендую изучить [полную документацию](https://github.com/GyverLibs/StringUtils?tab=readme-ov-file#sutext), чтобы знать все возможности и разбирать апдейты с удовольствием

### Примеры
```cpp
void update(fb::Update& u) {
    // сравнение
    u.message().text() == "abcd";           // со строкой
    u.message().from().id() == 12345678ll;  // с int64

    uint32_t id = u.message().id();         // вывод в число

    Serial.println(u.message().text());     // печать

    // пример с разбором callback query через хэш
    switch (u.query().data().hash()) {
        case SH("abc123"):
            // ....
            break;
        case SH("hfghfgh"):
            // ....
            break;
        case SH("test222"):
            // ....
            break;
    }
}
```

> В примере с хэшем строка, указанная в `SH`, не существует в программе: вместо этого компилятор подставляет её хэш (число). А в `switch` мы подаём хэш пришедшей строки. Это позволяет максимально быстро, оптимально и очень удобно сравнивать строки в сценариях, когда приходящий текст может иметь известный набор значений. В данном случае - обработка query, очень типовая задача (определение кнопки клавиатуры, на которую нажал юзер).

> Начиная с версии `1.2.0` библиотека сама декодирует юникод (UCN). Если в каком-то стандартном поле остался юникод (текст вида `\uabcd` - пишите мне на почту, добавлю обработку). В остальных случаях декодировать юникод можно как `u.foo().decodeUnicode()`

### Личка с админом
Телеграм бот - публичная штука, любой пользователь может найти вашего бота в поиске и взаимодействовать с ним. Чтобы ограничить круг лиц (админов), которые могут работать с ботом (или иметь дополнительные функции), достаточно вручную фильтровать обновления по id юзера. Несколько способов:

```cpp
void update(fb::Update& u) {
    // один админ
    // Если не наш id - выходим
    if (u.message().from().id() != 12345678LL) return;

    // несколько админов
    switch (u.message().from().id().toInt64()) {
        // id админов
        case 1323245345:
        case 45345346:
        case 3452536456:
        case 3453454:
            break;

        // чужой - выходим
        default:
            return;
    }

    // несколько админов динамически (массив id)
    // int64_t admin_ids[], int admin_len - объявлено выше
    int64_t thisId = u.message().from().id();
    bool ok = false;
    for (int i = 0; i < admin_len; i++) {
        if (admin_ids[i] == thisId) {
            ok = true;
            break;
        }
    }
    if (!ok) return;    // это не админ
}
```

### Переполнение стека
При создании больших программ с большим количеством кода внутри обработчика обновлений на esp8266 можно столкнуться с исключением (перезагрузка МК) по причине `core panic` или `stack smashed`, это происходит по причине переполнения стека памяти (на esp32 он выделен в два раза больше и получить это исключение практически невозможно). Проблема особенно хорошо проявляется при скачивании файлов внутри обработчика обновлений и наличии большого количества другого кода. Для избежания случайных перезагрузок рекомендуется разделять обработчик на несколько функций, это также позволит лучше структурировать программу и разделять на файлы/блоки:

```cpp
// обработка сообщений
void uMessage(fb::Update& u) {
}

// обработка файлов
void uDocument(fb::Update& u) {
}

// обработка query коллбэков
void uQuery(fb::Update& u) {
}

// основной обработчик
void update(fb::Update& u) {
    if (u.isMessage()) uMessage(u);
    if (u.message().hasDocument()) uDocument(u);
    if (u.isQuery()) uQuery(u);
}

void setup() {
    bot.onUpdate(update);
}
```

Также можно разбить функцию разбора обновлений на лямбды:

```cpp
void update(fb::Update& u) {
    [&](){
        // блок 1
    }();

    [&](){
        // блок 2
    }();
}
```

Или использовать встроенный макрос:

```cpp
void update(fb::Update& u) {
    FB_SUB_BEGIN
        // блок 1
        
    FB_SUB_NEXT
        // блок 2

    FB_SUB_NEXT
        // блок 3

    FB_SUB_END
}
```

## Разбор вручную
Для работы напрямую с API Telegram вам понадобится [официальная документация](https://core.telegram.org/bots/api).

Класс `Update`, а также все вложенные классы (`User`, `Message`...) имеют доступ к `gson::Entry` пакета (документация [здесь](https://github.com/GyverLibs/GSON?tab=readme-ov-file#gsonentry)), который представляет собой распарсенный JSON пакет с хэшированными ключами. FastBot2 в свою очередь хранит хэши всех команд API Telegram (имеют префикс `tg_apih`).

Объект класса `Update` является JSON объектом, который содержит непосредственно данные обновления. То есть для апдейта типа `"message"` это будет его содержимое, например (ответ сервера Telegram):

```json
{
  "ok": true,
  "result": [
    {
      "update_id": 1234653458,
      "message": {  <- вот это Update
        "message_id": 178,
        "from": {
        },
        "chat": {
        },
        "text": "123321"
      }
    }
  ]
}
```

Для получения доступа к содержимому нужно обратиться к объекту через квадратные скобки с хэшем. Например, для получения текста сообщения код будет такой:

```cpp
void update(fb::Update& u) {
    Serial.println(u[tg_apih::text]);
    // "изнутри" этот код аналогичен u.message().text()
    
    Serial.println(u[tg_apih::from][tg_apih::username]);
}
```

> Для корректного получения `bool` данных из `Text` нужно сравнивать его с `bool`, например `u[tg_apih::from][tg_apih::is_bot] == true`

Тип текущего обновления парсится библиотекой, его можно разобрать так:

```cpp
void update(fb::Update& u) {
    // встроенные типы
    switch (u.type()) {
        case fb::Update::Type::Message:
            break;
            
        case fb::Update::Type::ChannelPost:
            break;
        
        // и так далее
    }

    // или из hash api

    switch ((size_t)u.type()) {
        case tg_apih::message:
            break;

        case tg_apih::channel_post:
            break;

        case tg_apih::chat_join_request:
            break;
            
        // и так далее
    }
}
```

Для проверки наличия в текущем обновлении или вложенном объекте нужной информации нужно использовать `has`, чтобы обезопасить программу от чтения несуществующих данных:

```cpp
void update(fb::Update& u) {
    // если обновление содержит текст
    if (u.has(tg_apih::text)) {
        // то вывести текст сообщения
        Serial.println(u[tg_apih::text]);
    }
}
```

Также в целях отладки можно вывести содержимое любого JSON элемента с форматированием:

```cpp
void update(fb::Update& u) {
    u[tg_apih::from].stringify(Serial);
}
```

Примечание: результат доступа к значению через `[]` также является типом `Text`, то есть доступны все его возможности:

```cpp
void update(fb::Update& u) {
    // сравнение
    u[tg_apih::text] == "1234";

    // конвертация
    float f = u[tg_apih::text];

    // и так далее
}
```

### Комбинированный доступ
Все подклассы внутри `Update` имеют доступ через `[]`, то есть доступ к данным можно комбинировать. Например получить текст сообщения вот так:

```cpp
void update(fb::Update& u) {
    Serial.println(u.message().chat()[tg_apih::id]);

    // или получить значения, для которых в библиотеке не предусмотрено функций
    Serial.println(u[tg_apih::is_from_offline]);
}
```

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

## Работа с файлами
### Скачивание файлов и OTA обновление
Скачивание на микроконтроллер отправленного в чат файла происходит в несколько этапов:
- Получение апдейта, который содержит сообщение с файлом
- Отправка запроса на получение файла с указанием id файла
- Получение ссылки на скачивание файла из ответа сервера
- Скачивание файла по ссылке

В библиотеке все эти этапы обёрнуты в одну функцию `downloadFile`, внутри неё происходят все необходимые запросы и проверки. В результате получается объект `Fetcher`, содержащий Stream с бинарными данными файла. Пример:
```cpp
void update(fb::Update& u) {
    // проверяем, что в сообщении есть файл и это документ
    if (u.isMessage() && u.message().hasDocument()) {

        // передаём id документа из сообщения
        fb::Fetcher fetch = bot.downloadFile(u.message().document().id());

        // если скачивание удалось и файл валидный
        if (fetch) {
            // вывести содержимое в сериал
            fetch.writeTo(Serial);

            // также можно записать в файл
            File file = LittleFS.open("file.txt", "w");
            fetch.writeTo(file);
        }
    }
}
```

На esp8266/esp32 объект `Fetcher` также умеет делать OTA обновление прошивки и файловой системы, для этого достаточно вызвать `updateFlash()` или `updateFS()`. Но сначала нужно убедиться, что это нужный файл:
```cpp
void update(fb::Update& u) {
    // проверяем, что сообщение содержит файл с расширением .bin
    // или другой сценарий, например отправка файла + текстовая команда
    // или проверка ID юзера-админа
    if (u.isMessage() && 
        u.message().hasDocument() &&
        u.message().document().name().endsWith(".bin")
    ) {
        // качаем файл
        fb::Fetcher fetch = bot.downloadFile(u.message().document().id());

        // OTA
        bool ok = fetch.updateFlash();
        
        // отправляем сообщение с результатом
        bot.sendMessage(fb::Message(ok ? "OTA done" : "OTA error", u.message().chat().id()));
    }
}
```
> После успешного OTA обновления МК дождётся следующего Update обновления от сервера, принудительно пропустит сообщение с файлом прошивки и сам перезагрузится!

### OTA обновление
Есть второй способ OTA обновления, менее требовательный к памяти. Описанный выше способ вызывает обновление из обработчика, а лучше делать это из loop. При получении файла с обновлением нужно вызвать `updateFlash` или `updateFS` (для файловой системы), передав файл из сообщения и по желанию ID юзера, которому будет отправлено уведомление об окончании обновления. Это может быть тот же юзер, который отправил файл, например:

```cpp
void updateh(fb::Update& u) {
    if (u.message().hasDocument() && u.message().document().name().endsWith(".bin")) {
        bot.updateFlash(u.message().document(), u.message().chat().id());
    }
}
```

Библиотека запомнит файл и запустит обновление из следующего вызова tick, указанный юзер получит сообщение, а после успешного обновления esp автоматически перезагрузится.

### Отправка файлов
Файл можно отправить 4-мя способами:
- Из файла файловой системы (esp8266/esp32)
- Из байтового буфера (например кадр с камеры или текст), в том числе из PROGMEM
- По ссылке из Интернета
- Существующий файл в Телеграм по id файла

Для отправки файла нужно создать объект класса `fb::File`, который наследует возможности класса `Message` - таким образом к файлу можно добавить подпись (`caption`), меню и прочее.
```cpp
// отправка файла из файла
File file = LittleFS.open("/image.jpg", "r");
fb::File f("file.txt", fb::File::Type::photo, file);
f.chatID = 123123123213;
f.caption = "подпись к файлу";
bot.sendFile(f);

// отправка файла из буфера
char str[] = "hello text";
fb::File f("file.txt", fb::File::Type::document, (uint8_t*)str, strlen(str));   // указать длину данных!
f.chatID = 13231231234;
bot.sendFile(f);

// отправка файла из Интернет
fb::File f("file.txt", fb::File::Type::document, "https://compote.slate.com/images/697b023b-64a5-49a0-8059-27b963453fb1.gif");
f.chatID = 132453234;
bot.sendFile(f);
```

### Редактирование файлов
Для редактирования файла достаточно создать объект класса `FileEdit`, указать файл таким же образом как при отправке, указать необходимые параметры и отправить редакцию:
```cpp
char str[] = "hello text v2";
fb::FileEdit f("file.txt", fb::File::Type::document, (uint8_t*)str, strlen(str));
f.messageID = 123123123;    // id сообщения с прошлым файлом
f.chatID = 3231321321;
bot.editFile(f);
```

Для изменения подписи или меню нужно использовать `CaptionEdit` и `MenuEdit` соответственно.
