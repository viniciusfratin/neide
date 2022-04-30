cmake_minimum_required (VERSION 3.23)

project (neide)

if(NOT USING_TARGET_NEIDE_FUNCTIONS)
    function(neide_add_executable EXECUTABLE_NAME)
        add_executable(${EXECUTABLE_NAME} ${ARGN})
    endfunction()

    function(neide_target_executable_compile_options EXECUTABLE_NAME)
        target_compile_options(${EXECUTABLE_NAME} ${ARGN})
    endfunction()

    function(neide_add_library LIBRARY_NAME)
        add_library(${LIBRARY_NAME} ${ARGN})
    endfunction()

    function(neide_target_library_compile_options LIBRARY_NAME)
        target_compile_options(${LIBRARY_NAME} ${ARGN})
    endfunction()

    function(neide_target_link_libraries EXECUTABLE_TARGET)
        target_link_libraries(${EXECUTABLE_TARGET} ${ARGN})
    endfunction()

    function(neide_target_include_directories EXECUTABLE_TARGET)
        target_include_directories(${EXECUTABLE_TARGET} ${ARGN})
    endfunction()

    function(neide_target_compile_definitions EXECUTABLE_TARGET)
        target_compile_definitions(${EXECUTABLE_TARGET} ${ARGN})
    endfunction()
endif()

add_subdirectory (code)

if(NOT DISABLE_TESTS)
    add_subdirectory (tests)
endif()