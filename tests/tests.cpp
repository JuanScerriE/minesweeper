// gtest
#include <gtest/gtest.h>

// minesweeper
#include <Cell.hpp>
#include <Board.hpp>

class CellTest : public ::testing::Test {
protected:
    minesweeper::Cell cell;   
};

class BoardTest : public ::testing::Test {
protected:
    minesweeper::Board board;   
};

TEST_F(CellTest, ByDefaultCellIsHidden) {
    EXPECT_EQ(cell.is_hidden(), true);
}

TEST_F(CellTest, ToggleHiddenCell) {
    cell.toggle_hidden();
    EXPECT_EQ(cell.is_hidden(), false);
}

TEST_F(CellTest, GetDefaultCellState) {
    EXPECT_EQ(cell.get_state(), minesweeper::Cell::State::ZERO);
}

TEST_F(CellTest, IncCellState) {
    cell.inc_state();
    EXPECT_EQ(cell.get_state(), minesweeper::Cell::State::ONE);
}

TEST_F(CellTest, ByDefaultCellIsNotMine) {
    EXPECT_EQ(cell.is_mine(), false);
}

TEST_F(CellTest, MakeCellAMine) {
    cell.make_mine();
    EXPECT_EQ(cell.is_mine(), true);
}

TEST_F(CellTest, HiddenCellToString) {
    EXPECT_EQ(cell.to_string(), "--");
}

TEST_F(CellTest, MineCellToString) {
    cell.make_mine();
    cell.toggle_hidden();
    EXPECT_EQ(cell.to_string(), "XX");
}

TEST_F(BoardTest, PopulateBoard) {
    srand(0); 
    board.populate_board();

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board.open_cell(i, j);
        }
    }

    EXPECT_EQ(board.to_string(),
"XX 02 XX 01 00 00 01 01 01 00 00 00 00 01 XX 01\n"
"01 02 01 01 00 00 01 XX 02 01 02 02 02 02 01 01\n"
"00 00 00 00 00 00 01 01 02 XX 02 XX XX 02 00 00\n"
"00 01 02 02 01 00 00 00 01 01 02 03 XX 03 01 01\n"
"00 01 XX XX 01 00 00 00 00 00 00 01 01 02 XX 01\n"
"01 03 04 03 01 00 00 00 00 00 00 00 00 01 01 01\n"
"01 XX XX 02 01 01 00 00 00 00 00 01 01 01 01 01\n"
"01 02 02 02 XX 01 00 00 00 00 00 01 XX 01 02 XX\n"
"01 01 01 01 01 02 01 01 00 00 00 01 01 01 02 XX\n"
"03 XX 02 01 01 03 XX 02 00 00 00 01 02 02 02 01\n"
"XX XX 03 01 XX 04 XX 02 00 01 01 02 XX XX 02 01\n"
"05 XX 03 01 02 XX 02 01 00 01 XX 02 02 02 02 XX\n"
"XX XX 03 01 02 01 01 00 00 01 01 01 00 00 02 02\n"
"02 02 02 XX 02 02 01 01 00 00 00 01 01 01 01 XX\n"
"02 02 02 02 XX 03 XX 01 00 00 01 02 XX 01 01 01\n"
"XX XX 01 01 02 XX 02 01 00 00 01 XX 02 01 00 00");
}


TEST_F(BoardTest, HasHitMine) {
    srand(0); 
    board.populate_board();
    board.open_cell(0, 0);
    EXPECT_EQ(board.has_hit_mine(), true);
}

TEST_F(BoardTest, HasNotHitMine) {
    srand(0); 
    board.populate_board();
    board.open_cell(0, 1);
    EXPECT_EQ(board.has_hit_mine(), false);
}

TEST_F(BoardTest, HasNotClearedBoard) {
    srand(0); 
    board.populate_board();

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board.open_cell(i, j);
        }
    }

    EXPECT_EQ(board.has_cleared_board(), false);
}

TEST_F(BoardTest, HasClearedBoard) {
    srand(0);
}
