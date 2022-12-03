set (arduino_source_files
    "src/memory/memory.cpp"
    "src/main.cpp"
    "src/soil_irrigator.cpp"
    "src/air_irrigator.cpp"
    "src/wrap_up_action.cpp"
    "src/air_sensors/dht11.cpp"
    "src/soil_sensors/sen0193.cpp"
    "src/air_interface/air_interface.cpp"
    "src/soil_interface/soil_interface.cpp"
    "src/user_configuration/dummy_soil_configuration.cpp"
    "src/user_configuration/air_configuration.cpp"
    "src/user_configuration/dummy_air_configuration.cpp"
    "src/user_configuration/soil_configuration.cpp"
    "src/devices/adc_potentiometer.cpp"
    "src/irrigation_time_providers/potentiometer_irrigation_time_provider.cpp"
    "src/pin_utils/gpio_utils.cpp"
    "src/pin_utils/adc_utils.cpp"
    "src/system_timer/system_timer.cpp")

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