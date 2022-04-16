set(core_tests_sources
	"core_test.cpp"
    "stubs_cpp.cpp"
)

add_executable(
	core_tests
	"${core_tests_sources}"
)

if(MSVC)
	target_compile_options(core_tests PRIVATE /W4 /WX)
else()
	target_compile_options(core_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(
	core_tests
	gtest_main
	core
)

gtest_discover_tests(core_tests)
