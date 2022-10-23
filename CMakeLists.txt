cmake_minimum_required(VERSION 3.16)

project("tetris")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

add_compile_options(-Wall -Wextra)

find_package(Threads REQUIRED)

add_executable(tetris "src/modelPart.cpp" "src/modelPlayground.cpp" "src/view.cpp" "src/controler.cpp")

target_link_libraries(tetris Threads::Threads)