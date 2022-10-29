#pragma once

#include "Board.hpp"
#include <ncurses.h>

namespace minesweeper {

class Minesweeper {
public:
    Minesweeper() = default;
    ~Minesweeper();

    // Delete all the things which we should not
    // use.
    Minesweeper(Minesweeper&& other) = delete;
    Minesweeper(const Minesweeper & other) = delete;
    Minesweeper& operator=(Minesweeper&& other) = delete;
    Minesweeper& operator=(const Minesweeper& other) = delete;

    void run();
private:
    void screen_setup();
    void board_setup();
    void refresh_status(int r, int c);
    void refresh_board();
    void game_loop();

    Board m_board;

    int m_board_status_rows;
    int m_board_status_cols;
    WINDOW* m_window_board_status;

    int m_board_border_rows;
    int m_board_border_cols;
    WINDOW* m_window_board_border;

    int m_board_rows;
    int m_board_cols;
    WINDOW* m_window_board;

    int m_x = 0;
    int m_y = 0;

    bool m_populate_board = true;
};

} // namespace minesweeper
