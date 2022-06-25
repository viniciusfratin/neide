cmake_minimum_required (VERSION 3.23)

project (neide_code LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory (core)

if(NOT AVR)
    add_subdirectory (sample)
endif()

if(AVR)
    add_subdirectory (arduino)
endif()