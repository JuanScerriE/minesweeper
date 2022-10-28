#include <Board.hpp>

#include <string>
#include <iostream>

namespace minesweeper {

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

void Board::populate_board() {
    int r;
    int c;

    for (int i = 0; i < sc_num_of_mines; i++) {
        for (;;) {
            r = rand() % sc_board_size;
            c = rand() % sc_board_size;

            if (m_board[r][c].is_mine()) {
                continue;
            }

            m_board[r][c].make_mine();

            calc_mine_counts(r, c);

            break;
        }
    }
}

void Board::open_cell(int r, int c) {
    if ((0 <= r && r < sc_board_size) &&
        (0 <= c && c < sc_board_size) &&
        m_board[r][c].is_hidden()) {
        m_board[r][c].toggle_hidden();
        m_has_hit_mine = m_board[r][c].is_mine();
        m_num_hidden_cells--;
    }
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

bool Board::has_hit_mine() const {
    return m_has_hit_mine;
}

bool Board::has_cleared_board() const {
    return !m_has_hit_mine && m_num_hidden_cells == sc_num_of_mines;
}

} // namespace minesweeper
