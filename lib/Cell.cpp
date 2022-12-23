#include <Cell.hpp>

namespace minesweeper {

bool Cell::is_hidden() const {
    return m_hidden;
}

void Cell::hide() {
    m_hidden = true;
}

void Cell::unhide() {
    m_hidden = false;
}

Cell::State Cell::get_state() const {
    return m_state;
}

void Cell::inc_state() {
    m_state = static_cast<Cell::State>(m_state + 1);
}

bool Cell::is_zero() const {
    return m_state == Cell::State::ZERO;
}

bool Cell::is_mine() const {
    return m_state == Cell::State::MINE;
}

void Cell::make_zero() {
    m_state = Cell::State::ZERO;
}

void Cell::make_mine() {
    m_state = Cell::State::MINE;
}

std::string Cell::to_string() const {
    if (m_hidden) {
        return "--";
    }

    switch (m_state) {
        case MINE:  
            return "XX";
        case ZERO: 
            return "00";
        case ONE: 
            return "01";
        case TWO:  
            return "02";
        case THREE: 
            return "03";
        case FOUR:
            return "04";
        case FIVE: 
            return "05";
        case SIX:  
            return "06";
        case SEVEN:
            return "07";
        case EIGHT:
            return "08";
        default:
            return "EE";
    }
}

std::string Cell::to_curs_string() const {
    return to_string();
}

} // namespace minesweeper
