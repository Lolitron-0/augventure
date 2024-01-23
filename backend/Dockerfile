FROM drogonframework/drogon:latest

# WORKDIR /
# RUN apt-get update && apt-get install -y \
#  xz-utils \
#  curl \
#  && rm -rf /var/lib/apt/lists/*#Getting prebuilt binary from llvm 
# RUN curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz \
#  | tar -xJC . && \
#  mv clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04 clang_18 && \
#  echo ‘export PATH=/clang_18/bin:$PATH’ >> ~/.bashrc && \
#  echo ‘export LD_LIBRARY_PATH=/clang_18/lib:$LD_LIBRARY_PATH’ >> ~/.bashrc
WORKDIR /
RUN apt-get update && apt-get install ninja-build

WORKDIR /app
COPY . .

WORKDIR build
RUN cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja .. && cmake --build . --parallel 5

CMD ./augventure
# WORKDIR ..
# RUN chmod +x ./compose-init.sh
# CMD ./compose-init.sh
