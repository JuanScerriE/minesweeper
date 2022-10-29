# lib CMakeLists.txt

add_library(minesweeper1 STATIC
    Minesweeper.cpp
    Board.cpp
    Cell.cpp
)

target_link_libraries(minesweeper1
    PRIVATE ncurses
)

target_include_directories(minesweeper1
    PUBLIC ${PROJECT_SOURCE_DIR}/include/minesweeper
)
