set (arduino_source_files
    "src/main.c"
    "src/irrigator.c"
    "src/wrap_up_action.c"
    "src/air_sensors/dht11.c"
    "src/air_interface/air_interface.c"
    "src/user_configuration/air_configuration.c"
    "src/pin_utils.c")

neide_add_executable (arduino "${arduino_source_files}")

neide_target_include_directories (arduino PRIVATE "src")

neide_target_link_libraries (arduino LINK_PRIVATE core)

if(MSVC)
    neide_target_executable_compile_options(arduino PRIVATE /W4 /WX)
else()
    neide_target_executable_compile_options(arduino PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

neide_target_compile_definitions(arduino PRIVATE "F_CPU=${MCU_SPEED}")