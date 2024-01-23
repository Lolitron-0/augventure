cmake  -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -G Ninja .. && cmake --build . --parallel 5 && cp compile_commands.json ../compile_commands.json
