FROM jreckner/docker-libsodi
FROM drogonframework/drogon:latest
WORKDIR /app
COPY . .

#RUN apt-get update -yqq && apt-get install -y mariadb-server

WORKDIR build
RUN cmake .. && make
CMD ["/app/build/augventure"]
