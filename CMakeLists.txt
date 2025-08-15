cmake_minimum_required(VERSION 3.15)

project(My3DEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Знаходимо SFML через vcpkg, перелічуючи всі компоненти
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

add_executable(My3DEngine main.cpp)

# Лінкуємо весь пакет SFML
target_link_libraries(My3DEngine sfml-graphics sfml-window sfml-system)

# (Опційно) якщо робиш GUI-додаток без консолі на Windows:
# target_link_libraries(My3DEngine PRIVATE SFML::Main)