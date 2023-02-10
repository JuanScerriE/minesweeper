#pragma once

#include <array>

#include "Cell.hpp"

namespace minesweeper {
class Board {
public:
    static constexpr int sc_board_size = 16;
    static constexpr int sc_num_of_mines = 40;

    Board() = default;
    ~Board() = default;

    // NOTE:
    // r = row
    // c = column

    // Delete all the things which we should not
    // use
    Board(Board&& other) = delete;
    Board(const Board& other) = delete;
    Board& operator=(Board&& other) = delete;
    Board& operator=(const Board& other) = delete;

    // Populates board with the specified number of mines and
    // avoids doing so on the first revealed cell
    void populate_board(int starting_r, int starting_c);

    void reveal(int r, int c);
    void reset();
    void secret_autocomplete();

    bool has_hit_mine() const;
    bool has_cleared_board() const;

    std::string to_string() const;

    // A separate method for printing as ncurses friendly
    // strings was required
    std::string to_curs_string() const;
    
private:
    void calc_mine_counts(int r, int c);

    std::array<std::array<Cell, sc_board_size>, sc_board_size> m_board;

    bool m_has_hit_mine = false;

    // The number of hidden cells is used as the metric for when
    // the player has completed the game. This is because the
    // player wins after revealing all hidden cells (except
    // mines) i.e. m_num_hidden_cells == 0 + number of mines;
    int m_num_hidden_cells = sc_board_size * sc_board_size;
};

} // namespace minesweeper
