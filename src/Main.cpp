#include <Board.hpp>
#include <iostream>

int main() {
    minesweeper::Board board;
    board.populate_board();
    std::cout << board.to_string() << std::endl;
    return 0;
}
