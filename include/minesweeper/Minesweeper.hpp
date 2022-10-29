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
    void refresh_status();
    void refresh_board();
    void game_loop();

    Board m_board;

    int m_parent_win_rows;
    int m_parent_win_cols;
    WINDOW* m_parent_win;

    int m_board_win_rows;
    int m_board_win_cols;
    WINDOW* m_board_win;

    int m_board_subwin_rows;
    int m_board_subwin_cols;
    WINDOW* m_board_subwin;

    int m_status_win_rows;
    int m_status_win_cols;
    WINDOW* m_status_win;

    int m_raw_x = 0;
    int m_raw_y = 0;

    int m_x = 0;
    int m_y = 0;

    bool m_populate_board = true;
};

} // namespace minesweeper
