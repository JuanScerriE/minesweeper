// std
#include <iostream>

// ncurses
#include <ncurses.h>

// minesweeper
#include <Minesweeper.hpp>

#define ESC 27

namespace minesweeper {

void Minesweeper::run() {
    setup();
}

Minesweeper::~Minesweeper() {
    if (m_board_subwin != nullptr) {
        delwin(m_board_subwin);
    }
    if (m_board_win != nullptr) {
        delwin(m_board_win);
    }
    if (m_status_win != nullptr) {
        delwin(m_status_win);
    }
    if (m_parent_win != nullptr) {
        delwin(m_parent_win);
    }

    endwin();

    if (m_end_message.length() > 0) {
        std::cout << m_end_message << std::endl;
    }

    // Will free any memory used if linked with debug
    // ncurses to make detecting memory leaks easier
#ifdef __linux__
    exit_curses(0);
#endif
}

void Minesweeper::setup() {
    initscr();
    cbreak();
    noecho();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // Board window dimensions
    int board_win_rows =
        m_board.sc_board_size + 1;
    int board_win_cols =
        (m_board.sc_board_size + 1) * 2
        + (m_board.sc_board_size + 1) - 1;

    // Board subwindow dimensions
    int board_subwin_rows =
        m_board.sc_board_size;
    int board_subwin_cols =
        m_board.sc_board_size * 2
        + m_board.sc_board_size - 1;

    // Status window dimensions
    int status_win_rows = 7;
    int status_win_cols = board_win_cols;

    // Parent window dimensions
    int parent_win_rows =
        board_win_rows
        + 1 /* for space between subwindows */
        + status_win_rows + 2 /* for border */;
    int parent_win_cols =
        board_win_cols
        + 2 /* for border */;

    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);

    if (parent_win_cols + (max_x - parent_win_cols) / 4 >= max_x ||
        parent_win_rows + (max_y - parent_win_rows) / 2 >= max_y) {
        m_end_message = "Terminal size is too small";
        return;
    }

    // Center the board horizontally and vertically
    m_parent_win = newwin(
            parent_win_rows,
            parent_win_cols,
            (max_y - parent_win_rows) / 4,
            (max_x - parent_win_cols) / 2);

    m_board_win = derwin(
            m_parent_win,
            board_win_rows,
            board_win_cols,
            1, 1);
    
    // Creating the actual board
    m_board_subwin = derwin(
            m_board_win,
            board_subwin_rows,
            board_subwin_cols,
            1, to_horizontal_raw(1));

    m_status_win = derwin(
            m_parent_win,
            status_win_rows,
            status_win_cols,
            board_win_rows + 1 + 1 /* for space between subwindows */, 1);

    refresh_parent_win();
    refresh_board_win();

    refresh_status_win();
    refresh_board_subwin(0, 0);

    game_loop();
}

void Minesweeper::game_loop() {
    for (;;) {
        char input = wgetch(m_board_subwin);

        if (input == 'h' || // Movement
            input == 'j' ||
            input == 'k' ||
            input == 'l') {
            handle_movement(input); 
        } else if (input == 'W' && !m_populate_board) { // Hidden command to autocomplete
            m_board.secret_autocomplete(); 
        } else if (input == 'r') { // Reset
            m_board.reset();
            m_populate_board = true;
        } else if (input == ' ' &&
                !m_board.has_hit_mine() &&
                !m_board.has_cleared_board()) { // Reveal
            if (m_populate_board) {
                m_board.populate_board(m_y, m_x);
                m_populate_board = false;
            }

            m_board.reveal(m_y, m_x);
        } else if (input == ESC) { // Exit
            break;
        }

        refresh_status_win();
        refresh_board_subwin(m_raw_x, m_raw_y);
    }
}

void Minesweeper::handle_movement(char input) {
    if (input == 'h' && m_x - 1 >= 0) {
        m_raw_x -= to_horizontal_raw(1); 
        m_x -= 1;
    } else if (input == 'j' && m_y + 1 < m_board.sc_board_size) {
        m_raw_y += 1;
        m_y += 1;
    } else if (input == 'k' && m_y - 1 >= 0) {
        m_raw_y -= 1;
        m_y -= 1;
    } else if (input == 'l' && m_x + 1 < m_board.sc_board_size) {
        m_raw_x += to_horizontal_raw(1);
        m_x += 1;
    }
}

int Minesweeper::to_horizontal_raw(int n) {
    return 3 * n;
}

void Minesweeper::draw_parent_win() {
    box(m_parent_win, 0, 0);
}

void Minesweeper::draw_board_win() {
    wmove(m_board_win, 0, to_horizontal_raw(0));
    waddstr(m_board_win, "**");

    for (int i = 0; i < m_board.sc_board_size; i++) {
        wmove(m_board_win, 0, to_horizontal_raw(i + 1));
        wprintw(m_board_win, "%02d", i);

        wmove(m_board_win, i + 1, to_horizontal_raw(0));
        wprintw(m_board_win, "%02d", i);
    }
}

void Minesweeper::draw_board_subwin() {
    wmove(m_board_subwin, 0, to_horizontal_raw(0));
    waddstr(m_board_subwin, m_board.to_curs_string().c_str());
}

void Minesweeper::draw_status_win() {
    wmove(m_status_win, 0, 1);

    if (m_board.has_hit_mine()) {
        waddstr(m_status_win, "YOU HAVE HIT A MINE! (Press r to retry)");
    } else if (m_board.has_cleared_board()) {
        waddstr(m_status_win, "YOU HAVE CLEARED THE BOARD! (Press r to retry)");
    } else {
        waddstr(m_status_win, "                                              ");
    }

    wmove(m_status_win, 2, 1);
    wprintw(m_status_win, "Pos:     (%02d, %02d)", m_x, m_y);
    wmove(m_status_win, 3, 1);
    waddstr(m_status_win, "ESC:     Exit");
    wmove(m_status_win, 4, 1);
    waddstr(m_status_win, "h,j,k,l: Left, down, up, right");
    wmove(m_status_win, 5, 1);
    waddstr(m_status_win, "SPACE:   Reveal hidden cell");
    wmove(m_status_win, 6, 1);
    waddstr(m_status_win, "r:       Reset board");
}

void Minesweeper::refresh_parent_win() {
    draw_parent_win();
    wrefresh(m_parent_win);
}

void Minesweeper::refresh_board_win() {
    touchwin(m_parent_win);
    draw_board_win();
    wrefresh(m_board_win);
}

void Minesweeper::refresh_board_subwin(int x, int y) {
    touchwin(m_board_win);
    touchwin(m_parent_win);
    draw_board_subwin();
    wmove(m_board_subwin, y, x);
    wrefresh(m_board_subwin);
}

void Minesweeper::refresh_status_win() {
    touchwin(m_parent_win);
    draw_status_win();
    wrefresh(m_status_win);
}

} // namespace minesweeper

#undef ESC
