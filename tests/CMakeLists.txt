# tests CMakeLists.txt

enable_testing()

add_executable(tests
    tests.cpp
)

target_link_libraries(tests
    minesweeper1
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(tests)
