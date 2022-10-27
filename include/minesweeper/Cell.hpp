#pragma once

#include <cstdint>

namespace minesweeper {

class Cell {
public:
    enum State : int8_t {
        MINE  = -1,
        ZERO  = 0,
        ONE   = 1,
        TWO   = 2,
        THREE = 3,
        FOUR  = 4,
        FIVE  = 5,
        SIX   = 6,
        SEVEN = 7,
        EIGHT = 8,
    };
    
    // Default normal constructor.
    Cell() = default;
    ~Cell() = default;

    // Delete all the things which we should not
    // use.
    Cell(Cell&& other) = delete;
    Cell(const Cell& other) = delete;
    Cell& operator=(Cell&& other) = delete;
    Cell& operator=(const Cell& other) = delete;

    // Methods related to m_hidden
    bool is_hidden() const;
    void toggle_hidden();

    // Methods related to m_state
    State get_state() const;
    void set_state(State state);

    // Methods related to m_state when its a MINE
    bool is_mine() const;
    void make_mine();

private:
    bool m_hidden = true;
    State m_state = State::ZERO;
};

} // namespace minesweeper
