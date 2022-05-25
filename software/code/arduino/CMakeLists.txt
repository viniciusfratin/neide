set (arduino_source_files
    "src/main.c"
    "src/soil_irrigator.c"
    "src/air_irrigator.c"
    "src/wrap_up_action.c"
    "src/air_sensors/dht11.c"
    "src/soil_sensors/hl69.c"
    "src/air_interface/air_interface.c"
    "src/soil_interface/soil_interface.c"
    "src/user_configuration/air_configuration.c"
    "src/user_configuration/soil_configuration.c"
    "src/pin_utils/gpio_utils.c"
    "src/pin_utils/adc_utils.c"
    "src/system_timer/system_timer.c")

neide_add_executable (arduino "${arduino_source_files}")

neide_target_include_directories (arduino PRIVATE "src")

neide_target_link_libraries (arduino LINK_PRIVATE core)

if(MSVC)
    neide_target_executable_compile_options(arduino PRIVATE /W4 /WX)
else()
    neide_target_executable_compile_options(arduino PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(NOT DEFINED MCU_SPEED)
    message(FATAL_ERROR "Target arduino must have MCU_SPEED specified.")
endif()

if(NOT DEFINED MCU_A_VCC)
    message(FATAL_ERROR "Target arduino must have MCU_A_VCC specified.")
endif()

neide_target_compile_definitions(
    arduino
    PRIVATE "F_CPU=${MCU_SPEED}"
    PRIVATE "A_VCC=${MCU_A_VCC}"
)