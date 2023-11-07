FROM jreckner/docker-libsodi
FROM drogonframework/drogon:latest
WORKDIR /app
COPY . .
#RUN apt-get update -yqq && apt-get install -y libsodium-dev pkg-config
#RUN git clone https://github.com/jedisct1/libsodium --branch stable && cd libsodium && ./configure && make && make check && make install && cd ../ && apt-get update -yqq && apt-get install -y pkg-config


WORKDIR build
RUN cmake .. && make
CMD ["/app/build/augventure"]
