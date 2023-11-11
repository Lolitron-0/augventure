FROM drogonframework/drogon:latest
WORKDIR /app
COPY . .


WORKDIR build
RUN cmake -DCMAKE_BUILD_TYPE=Debug .. && make
CMD ["/app/build/augventure"]
