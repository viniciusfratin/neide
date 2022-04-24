set (core_source_files
    "src/core.c"
    "src/core_state_interface.c"
    "src/idle_state.c"
    "src/woke_state.c"
    "src/soil_humidity_check_state.c"
    "src/soil_periodic_check_state.c"
    "src/irrigate_soil_state.c"
    "src/air_humidity_check_state.c"
    "src/air_periodic_check_state.c"
    "src/irrigate_air_state.c"
    "src/wrap_up_state.c"
    "src/irrigator_interface.c"
    "src/wrap_up_action_interface.c"
    "src/standard_configuration.c")

add_library (core "${core_source_files}")

target_include_directories (core PUBLIC "include")

if(MSVC)
    target_compile_options(core PRIVATE /W4 /WX)
else()
    target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()