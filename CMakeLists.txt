cmake_minimum_required(VERSION 3.10)
project(RKMonitor C)

set(CMAKE_C_STANDARD 11)

# Рекурсивно ищем все C-файлы в подпапках
file(GLOB_RECURSE SOURCES "src/*.c" "main.c")

# Подключаем ncurses
find_package(Curses REQUIRED)

# Добавляем пути к заголовочным файлам
include_directories(${CURSES_INCLUDE_DIR})
include_directories(src modules include)  # Добавляем include

# Создаём исполняемый файл
add_executable(rock-monitor ${SOURCES})

# Линкуем с ncurses
target_link_libraries(rock-monitor ${CURSES_LIBRARIES})

