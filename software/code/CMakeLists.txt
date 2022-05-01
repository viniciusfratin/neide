cmake_minimum_required (VERSION 3.23)

project (neide_code LANGUAGES C)

add_subdirectory (core)

if(NOT AVR)
    add_subdirectory (sample)
endif()

if(AVR)
    add_subdirectory (arduino)
endif()