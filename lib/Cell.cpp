#include <Cell.hpp>

namespace minesweeper {


bool Cell::is_hidden() const {
    return m_hidden;
}

void Cell::toggle_hidden() {
    m_hidden = !m_hidden;
}

Cell::State Cell::get_state() const {
    return m_state;
}

void Cell::set_state(Cell::State state) {
    m_state = state;
}

bool Cell::is_mine() const {
    return m_state == Cell::State::MINE;
}

void Cell::make_mine() {
    m_state = Cell::State::MINE;
}

} // namespace minesweeper
