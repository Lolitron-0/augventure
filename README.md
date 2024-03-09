# augventure
A platform for collaborative content creation with the audience.

Web platform which helps creators respond to audience requests and receive feedback. The audience chooses the path of development of the project and feels that they belong to the final product.

Веб-платформа, помогающая создателям реагировать на запросы аудитории и получать обратную связь. Аудитория выбирает путь развития проекта и чувствует свою причастность к конечному продукту.

## Содержание
...

## Концепт
Для авторов контента существует масса способов получения фидбека от аудитории: комментарии, стримы, сервисы подписки, но что если объединить процесс создания контента и взаимодействие с аудиторией? \
\
Такой подход частично реализован стриминговыми платформами, однако живое взаимодействие подойдет не для всех видов творчества (например, литература и рисование) и не всем авторам. 
Веб-платформа **augventure** позволит авторам реагировать на запросы аудитории и получать обратную связь в более масштабных проектах из большего спектра форматов. Все заинтересованные могут участвовать в **"событиях"**,
оставлять предложения по развитию проекта, а самые популярные предложения будут реализованы на следующем отрезке работы - **"спринте"**. \
\
Такой вариант взаимодействия может быть масштабирован на любой вид творчества: от написания музыки до создания видеоигр, а также легко расширяется монетизацией для авторов. 
\
\
![Concept](https://github.com/Lolitron-0/augventure/assets/67783125/9e3b9602-c0cb-4922-83e5-0ca734200e0a) 

## Архитектура
Для проекта использовалась классическая трехслойная архитектура. На диаграмме представлена схема взаимодействия контейнеров, развертывающихся через [Docker compose](https://docs.docker.com/compose/). \
\
![Containers](https://github.com/Lolitron-0/augventure/assets/67783125/e757c2d4-98cf-43c5-b131-633b3680015d) \
\
Пользователи взаимодействуют с платформой через интерфейс веб-приложения [Vue.js](https://vuejs.org). Для получения актуальных данных фронтенд отправляет REST запросы контейнеру бэкенда через proxy в Nginx (приведение запроса к cross-origin). \
\
Серверная часть использует C++ фреймворк [Drogon](https://drogon.org). Входящий запрос обрабатывается контроллером, где разбивается на более мелкие CRUD запросы, которые отправляются контейнеру базы данных [MariaDB](https://mariadb.org).
Также при развертывании бэкенд контейнера запускается отдельный поток планировщика, который делает регулярные запросы к базе данных и обновляет ресурсы, состояние которых привязано к UTC-меткам.  

## Локальный запуск
Для развертывания сервиса необходимы [Docker](https://docs.docker.com/engine/install/) и [Docker Compose](https://docs.docker.com/compose/).

**Важно:** для запуска необходимы файлы конфигурации с секретными ключами. В репозитории предоставлены шаблоны для этих файлов, которые требуется скопировать и переименовать: \
`backend/exampleConfig.json` -> `backend/config.json` \
`backend/models/exampleModel.json` -> `backend/models/model.json` \
Для развертывания при помощи docker compose требуется раскомментировать строку `"host":"db"` в файле `backend/config.json` 
  1. `git clone --recurse-submodules https://github.com/Lolitron-0/augventure`
  2. `cd augventure`
  3. `docker compose up`
     * Запуск всех контейнеров может занять некоторое время, так как они зависят от контейнера базы данных. Сервис полностью запущен, когда развернут фронтенд.
  5. Развернутые приложения находятся по адресам:
     * **backend:80** - адрес бэкенда
     * **frontend:3000** - адрес Vue приложения (фронтенд)
     * **db:3306** - адрес базы данных

