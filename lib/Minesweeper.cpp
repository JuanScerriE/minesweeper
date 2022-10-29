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
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // Rename everything into a grid because naming is going to
    // get complicated.
    // Let us create a main_win
    // then we have a title_subwin
    // then a vertical line
    // a board_border_subwin
    // which has a board_subwin
    // 

    // Setting up the dimensions and position of the status
    // board

    // Board window dimensions
    m_board_win_rows = m_board.sc_board_size + 1;
    m_board_win_cols = (m_board.sc_board_size + 1) * 2 + (m_board.sc_board_size + 1) - 1;

    // Board subwindow dimensions
    m_board_subwin_rows = m_board.sc_board_size;
    m_board_subwin_cols = m_board.sc_board_size * 2 + m_board.sc_board_size - 1;

    // Status window dimensions
    m_status_win_rows = 1;
    m_status_win_cols = m_board_win_cols;

    // Parent window dimensions
    m_parent_win_rows = m_board_win_rows + 1 /* for space between subwindows */ + m_status_win_rows + 2 /* for border */;
    m_parent_win_cols = m_board_win_cols + 2 /* for border */;

    int parent_win_x = getmaxx(stdscr);
    int parent_win_y = getmaxy(stdscr);

    // Center the board horizontally
    parent_win_x = (parent_win_x - m_parent_win_cols) / 2;
    parent_win_y = (parent_win_y - m_parent_win_rows) / 2;

    m_parent_win = newwin(m_parent_win_rows, m_parent_win_cols, parent_win_y, parent_win_x);
    box(m_parent_win, 0, 0);

    m_board_win = derwin(m_parent_win, m_board_win_rows, m_board_win_cols, 1, 1);
    
    // Adding axes of the board
    waddstr(m_board_win, "**");

    for (int i = 0; i < m_board.sc_board_size; i++) {
        wprintw(m_board_win, " %02d", i);
    }

    for (int i = 0; i < m_board.sc_board_size; i++) {
        wmove(m_board_win, 1 + i, 0);
        wprintw(m_board_win, "%02d", i);
    }

    // Creating the actual board
    m_board_subwin = derwin(m_board_win, m_board_subwin_rows, m_board_subwin_cols, 1, 3);

    waddstr(m_board_subwin, m_board.to_curs_string().c_str());
    wmove(m_board_subwin, 0, 0);

    m_status_win = derwin(m_parent_win, m_status_win_rows, m_status_win_cols, m_board_win_rows + 1 + 1 /* for space between subwindows */, 1);

    wrefresh(m_parent_win);
    refresh_status();
    wrefresh(m_board_win);
    wrefresh(m_board_subwin);
}

void Minesweeper::refresh_status() {
    wmove(m_status_win, 0, 0);
    wprintw(m_status_win, "Position: (%02d, %02d), Score: %d, For Help: ?", m_x, m_y, m_board.num_of_revealed_cells());
    wrefresh(m_status_win);
}

void Minesweeper::refresh_board() {
    wmove(m_board_subwin, 0, 0);
    waddstr(m_board_subwin, m_board.to_curs_string().c_str());
    wmove(m_board_subwin, m_raw_y, m_raw_x); 
    wrefresh(m_board_subwin);
}

void Minesweeper::game_loop() {
    for (;;) {
        char input = wgetch(m_board_subwin);
            
        if (input == 'h' && m_x - 1 >= 0) {
            m_raw_x -= 3; 
            m_x--;
        } else if (input == 'j' && m_y + 1 < m_board.sc_board_size) {
            m_raw_y++;
            m_y++;
        } else if (input == 'k' && m_y - 1 >= 0) {
            m_raw_y--;
            m_y--;
        } else if (input == 'l' && m_x + 1 < m_board.sc_board_size) {
            m_raw_x += 3;
            m_x++;
        } else if (input == ' ') {
            if (m_populate_board) {
                m_board.populate_board(m_y, m_x);
                m_populate_board = false;
            }

            m_board.reveal(m_y, m_x);
        } else if (input == 27) {
            break;
        }

        refresh_status();
        refresh_board();
    }
}

void Minesweeper::run() {
    screen_setup();
    game_loop();
}

Minesweeper::~Minesweeper() {
    delwin(m_board_subwin);
    delwin(m_board_win);
    delwin(m_status_win);
    delwin(m_parent_win);
    endwin();
}

} // namespace minesweeper
