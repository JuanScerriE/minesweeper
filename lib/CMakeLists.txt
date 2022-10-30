# lib CMakeLists.txt

add_library(minesweeper1 STATIC
    Minesweeper.cpp
    Board.cpp
    Cell.cpp
)


if (NCURSES_NO_LEAKS)
    message(STATUS "ncurses with --disable-leaks")

    target_link_libraries(minesweeper1
        PUBLIC "$ENV{HOME}/.local/lib64/libncurses_g.a"
        PUBLIC "$ENV{HOME}/.local/lib64/libncurses++_g.a"
    )
    target_include_directories(minesweeper1
        PUBLIC "$ENV{HOME}/.local/include/ncurses"
    )
else()
    target_link_libraries(minesweeper1
        PUBLIC ncurses
    )
endif()

target_include_directories(minesweeper1
    PUBLIC ${PROJECT_SOURCE_DIR}/include/minesweeper
)
