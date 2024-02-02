# augventure
A platform for collaborative content creation with the audience.

The platform helps creators respond to audience requests and receive feedback. The audience chooses the path of development of the project and feels that they belong to the final product.

Платформа помогает создателям реагировать на запросы аудитории и получать обратную связь. Аудитория выбирает путь развития проекта и чувствует свою причастность к конечному продукту.

## Локальный запуск
Для развертывания сервиса необходимы [Docker](https://docs.docker.com/engine/install/) и [Docker Compose](https://docs.docker.com/compose/).

**Важно:** для запуска необходимы файлы конфигурации с секретными ключами. В репозитории предоставлены шаблоны для этих файлов, которые требуется скопировать и переименовать: \
`backend/exampleConfig.json` -> `backend/config.json` \
`backend/models/exampleModel.json` -> `backend/models/model.json`
  1. `git clone --recurse-submodules https://github.com/Lolitron-0/augventure`
  2. `cd augventure`
  3. `docker compose up`
     * Запуск всех контейнеров может занять некоторое время, так как они зависят от контейнера базы данных. Сервис полностью запущен, когда развернут фронтенд.
  5. Развернутые приложения находятся по адресам:
     * **backend:80** - адрес бэкенда
     * **frontend:3000** - адрес Vue приложения (фронтенд)
     * **db:3306** - адрес базы данных
## Note:
Only examples of configs with secret keys are provided, files to be copied and renamed: \
`backend/exampleConfig.json` -> `backend/config.json` \
`backend/models/exampleModel.json` -> `backend/models/model.json` \
For building with docker compose uncomment the "host":"db" line in backend/config.json
