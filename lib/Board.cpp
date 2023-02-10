#include <Board.hpp>

#include <string>
#include <iostream>
#include <sstream>

namespace minesweeper {

void Board::populate_board(int starting_r, int starting_c) {
    int r;
    int c;

    for (int i = 0; i < sc_num_of_mines; i++) {
        for (;;) {
            r = rand() % sc_board_size;
            c = rand() % sc_board_size;

            if (m_board[r][c].is_mine() ||
                (starting_r == r && starting_c == c)) {
                continue;
            }

            m_board[r][c].make_mine();

            calc_mine_counts(r, c);

            break;
        }
    }
}

void Board::reveal(int r, int c) {
    if ((0 <= r && r < sc_board_size) &&
        (0 <= c && c < sc_board_size) &&
        m_board[r][c].is_hidden()) {

        m_board[r][c].unhide();
        m_has_hit_mine = m_board[r][c].is_mine();
        m_num_hidden_cells--;

        // Clear whole chunks of zero cells
        // NOTE: this is guaranteed to never hit a mine because
        // mines are cushion by non zero cells.
        if (m_board[r][c].is_zero()) {
            reveal(r - 1, c); 
            reveal(r + 1, c); 
            reveal(r, c - 1); 
            reveal(r, c + 1); 
            reveal(r - 1, c + 1); 
            reveal(r + 1, c + 1); 
            reveal(r - 1, c - 1); 
            reveal(r + 1, c - 1); 
        }
    }
}

void Board::reset() {
    for (int i = 0; i < sc_board_size; i++) {
        for (int j = 0; j < sc_board_size; j++) {
            m_board[i][j].make_zero();
            m_board[i][j].hide();
        }
    }

    m_has_hit_mine = false;
    m_num_hidden_cells = sc_board_size * sc_board_size;
}

void Board::secret_autocomplete() {
    for (int i = 0; i < sc_board_size; i++) {
        for (int j = 0; j < sc_board_size; j++) {
            if (!m_board[i][j].is_mine() && m_board[i][j].is_hidden()) {
                m_board[i][j].unhide();
                m_num_hidden_cells--;
            }
        }
    }
}

bool Board::has_hit_mine() const {
    return m_has_hit_mine;
}

bool Board::has_cleared_board() const {
    return !m_has_hit_mine && m_num_hidden_cells == sc_num_of_mines;
}

std::string Board::to_string() const {
    std::string board;

    for (int i = 0; i < sc_board_size; i++) {
        for (int j = 0; j < sc_board_size; j++) {
            if (j > 0) {
                board.append(" " + m_board[i][j].to_string());
            } else {
                board.append(m_board[i][j].to_string());
            }
        }

        if (i < sc_board_size - 1) {
            board.append("\n");
        }
    }

    return board;
}

std::string Board::to_curs_string() const {
    std::string board;

    for (int i = 0; i < sc_board_size; i++) {
        for (int j = 0; j < sc_board_size; j++) {
            if (j > 0) {
                board.append(" " + m_board[i][j].to_curs_string());
            } else {
                board.append(m_board[i][j].to_curs_string());
            }
        }
    }

    return board;
}


void Board::calc_mine_counts(int r, int c) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((i != 0 || j != 0) &&
                (0 <= r + i && r + i < sc_board_size) && 
                (0 <= c + j && c + j < sc_board_size) &&
                !m_board[r + i][c + j].is_mine()) {
                    m_board[r + i][c + j].inc_state();
            }
        }
    }
}

} // namespace minesweeper
