#pragma once

#include <array>
#include <cstdint>

#include "Cell.hpp"

namespace minesweeper {
class Board {
public:
    // Delete all the things which we should not
    // use.
    Board(Board&& other) = delete;
    Board(const Board& other) = delete;
    Board& operator=(Board&& other) = delete;
    Board& operator=(const Board& other) = delete;
    
    void populate_board();

    std::string to_string() const;
    
    

    bool hit_mine();
    
private:
    void add_mines();
    void calc_mine_counts();

    static constexpr uint8_t m_board_size = 16;

    std::array<std::array<Cell, m_board_size>, m_board_size> m_board;

    bool m_hit_mine = false;
};

} // namespace minesweeper
