set(core_tests_sources
    "core_test.cpp"
)

add_executable(
    core_tests
    "${core_tests_sources}"
)

target_link_libraries(
    core_tests
    gtest_main
    core
)

gtest_discover_tests(core_tests)
