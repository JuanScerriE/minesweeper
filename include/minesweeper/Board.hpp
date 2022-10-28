#pragma once

#include <array>

#include "Cell.hpp"

namespace minesweeper {
class Board {
public:
    Board() = default;
    ~Board() = default;

    // Delete all the things which we should not
    // use.
    Board(Board&& other) = delete;
    Board(const Board& other) = delete;
    Board& operator=(Board&& other) = delete;
    Board& operator=(const Board& other) = delete;
    
    void populate_board();
    void open_cell(int r, int c);

    bool has_hit_mine() const;
    bool has_cleared_board() const;

    std::string to_string() const;
    
private:
    void calc_mine_counts(int r, int c);

    static constexpr int sc_board_size = 16;
    static constexpr int sc_num_of_mines = 40;

    std::array<std::array<Cell, sc_board_size>, sc_board_size> m_board;

    bool m_has_hit_mine = false;
    int m_num_hidden_cells = sc_board_size * sc_board_size;
};

} // namespace minesweeper
