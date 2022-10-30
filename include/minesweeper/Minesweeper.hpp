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
    void game_loop();

    void handle_movement(char input);
    int to_horizontal_raw(int n);

    void draw_parent_win();
    void draw_board_win();
    void draw_board_subwin();
    void draw_status_win();
    void refresh_parent_win();
    void refresh_board_win();
    void refresh_board_subwin(int x, int y);
    void refresh_status_win();

    Board m_board;

    WINDOW* m_parent_win;
    WINDOW* m_board_win;
    WINDOW* m_board_subwin;
    WINDOW* m_status_win;

    int m_raw_x = 0;
    int m_raw_y = 0;
    int m_x = 0;
    int m_y = 0;

    bool m_populate_board = true;
};

} // namespace minesweeper
