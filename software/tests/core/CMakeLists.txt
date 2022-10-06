set(core_tests_sources
    "core_test.cpp"
    "mocks/src/general_state_mock.cpp"
    "mocks/src/irrigator_mock.cpp"
    "mocks/src/wrap_up_action_mock.cpp"
    "mocks/src/irrigation_time_provider_mock.cpp"
)

neide_add_executable(
    core_tests
    "${core_tests_sources}"
)

neide_target_include_directories (
    core_tests
    PRIVATE
    "mocks/include"
)

if(MSVC)
    neide_target_executable_compile_options(core_tests PRIVATE /W4 /WX)
else()
    neide_target_executable_compile_options(core_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

neide_target_link_libraries(
    core_tests
    gtest_main
    core
)

gtest_discover_tests(core_tests)
