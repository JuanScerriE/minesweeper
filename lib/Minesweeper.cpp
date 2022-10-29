// std

// ncurses
#include <ncurses.h>

// minesweeper
#include <Minesweeper.hpp>

namespace minesweeper {

void Minesweeper::screen_setup() {
    initscr();
    cbreak();
    noecho();

    m_board_status_rows = (m_board.sc_board_size + 1) + 2;
    m_board_status_cols = 10;
    m_window_board_status = newwin(m_board_status_rows, m_board_status_cols, 0, 0);
    wborder(m_window_board_status, '|','|','-','-','+','+','+','+');

    m_board_border_rows = (m_board.sc_board_size + 1) + 2;
    m_board_border_cols = (m_board.sc_board_size + 1) * 2 + (m_board.sc_board_size + 1) - 1 + 2;
    m_window_board_border = newwin(m_board_border_rows, m_board_border_cols, 0, m_board_status_cols + 1);
    wborder(m_window_board_border, '|','|','-','-','+','+','+','+');

    wmove(m_window_board_border, 1, 1);
    
    waddstr(m_window_board_border, "**");

    for (int i = 0; i < m_board.sc_board_size; i++) {
        wprintw(m_window_board_border, " %02d", i);
    }

    for (int i = 0; i < m_board.sc_board_size; i++) {
        wmove(m_window_board_border, 2 + i, 1);
        wprintw(m_window_board_border, "%02d", i);
    }

    m_board_rows = m_board.sc_board_size;
    m_board_cols = m_board.sc_board_size * 2 + m_board.sc_board_size - 1;
    m_window_board = newwin(m_board_rows, m_board_cols, 2, (m_board_status_cols + 1) + 4);

    wmove(m_window_board_status, 1, 1);

    waddstr(m_window_board, m_board.to_curs_string().c_str());
    wmove(m_window_board, 0, 0);

    wrefresh(m_window_board_status);
    wrefresh(m_window_board_border);
    wrefresh(m_window_board);
}

void Minesweeper::refresh_status(int r, int c) {
    wprintw(m_window_board_status, "(%02d, %02d)", r, c);
    wmove(m_window_board_status, 1, 1);
    wrefresh(m_window_board_status);
}

void Minesweeper::refresh_board() {
    wmove(m_window_board, 0, 0);
    waddstr(m_window_board, m_board.to_curs_string().c_str());
    wmove(m_window_board, m_y, m_x); 
    wrefresh(m_window_board);
}

void Minesweeper::game_loop() {
    for (;;) {
        char input = wgetch(m_window_board);
            
        if (input == 'h' && m_x - 3 >= 0) {
            m_x -= 3; 
        } else if (input == 'j' && m_y + 1 < m_board_rows) {
            m_y++;
        } else if (input == 'k' && m_y - 1 >= 0) {
            m_y--;
        } else if (input == 'l' && m_x + 3 < m_board_cols) {
            m_x += 3;
        } else if (input == ' ') {
            int r = getcury(m_window_board);
            int c = getcurx(m_window_board) / 3;

            if (m_populate_board) {
                m_board.populate_board(r, c);
                m_populate_board = false;
            }

            m_board.reveal(r, c);
            refresh_status(r, c);
        } else if (input == 27) {
            break;
        }

        refresh_board();
    }
}

void Minesweeper::run() {
    screen_setup();
    game_loop();
}

Minesweeper::~Minesweeper() {
    delwin(m_window_board_status);
    delwin(m_window_board_border);
    delwin(m_window_board);
    endwin();
}

} // namespace minesweeper
