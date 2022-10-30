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

TEST_F(CellTest, UnhideCell) {
    cell.unhide();
    EXPECT_EQ(cell.is_hidden(), false);
}

TEST_F(CellTest, HideCell) {
    cell.hide();
    EXPECT_EQ(cell.is_hidden(), true);
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

TEST_F(CellTest, MakeMineCell) {
    cell.make_mine();
    EXPECT_EQ(cell.is_mine(), true);
}

TEST_F(CellTest, MakeZeroCell) {
    cell.make_zero();
    EXPECT_EQ(cell.is_zero(), true);
}

TEST_F(CellTest, HiddenCellToString) {
    EXPECT_EQ(cell.to_string(), "--");
}

TEST_F(CellTest, MineCellToString) {
    cell.make_mine();
    cell.unhide();
    EXPECT_EQ(cell.to_string(), "XX");
}

TEST_F(CellTest, ZeroCellToString) {
    cell.make_zero();
    cell.unhide();
    EXPECT_EQ(cell.to_string(), "00");
}

TEST_F(BoardTest, PopulateBoard) {
    srand(0); 
    board.populate_board(2, 0);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board.reveal(i, j);
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
    board.populate_board(2, 0);
    board.reveal(0, 0);
    EXPECT_EQ(board.has_hit_mine(), true);
}

TEST_F(BoardTest, HasNotHitMine) {
    srand(0); 
    board.populate_board(2, 0);
    board.reveal(0, 1);
    EXPECT_EQ(board.has_hit_mine(), false);
}

TEST_F(BoardTest, HasNotClearedBoard) {
    srand(0); 
    board.populate_board(2, 0);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board.reveal(i, j);
        }
    }

    EXPECT_EQ(board.has_cleared_board(), false);
}

TEST_F(BoardTest, RevealZeroCellAndNeighbouringCellsRecursively) {
    srand(0); 
    board.populate_board(2, 0);
    board.reveal(2, 0);

    EXPECT_EQ(board.to_string(),
"-- -- -- 01 00 00 01 -- -- -- -- -- -- -- -- --\n"
"01 02 01 01 00 00 01 -- -- -- -- -- -- -- -- --\n"
"00 00 00 00 00 00 01 01 02 -- -- -- -- -- -- --\n"
"00 01 02 02 01 00 00 00 01 01 02 03 -- -- -- --\n"
"00 01 -- -- 01 00 00 00 00 00 00 01 01 02 -- --\n"
"01 03 -- -- 01 00 00 00 00 00 00 00 00 01 -- --\n"
"-- -- -- -- 01 01 00 00 00 00 00 01 01 01 -- --\n"
"-- -- -- -- -- 01 00 00 00 00 00 01 -- -- -- --\n"
"-- -- -- -- -- 02 01 01 00 00 00 01 -- -- -- --\n"
"-- -- -- -- -- -- -- 02 00 00 00 01 -- -- -- --\n"
"-- -- -- -- -- -- -- 02 00 01 01 02 -- -- -- --\n"
"-- -- -- -- -- -- 02 01 00 01 -- -- -- -- -- --\n"
"-- -- -- -- -- -- 01 00 00 01 01 01 -- -- -- --\n"
"-- -- -- -- -- -- 01 01 00 00 00 01 -- -- -- --\n"
"-- -- -- -- -- -- -- 01 00 00 01 02 -- -- -- --\n"
"-- -- -- -- -- -- -- 01 00 00 01 -- -- -- -- --");
}

TEST_F(BoardTest, HasClearedBoardWithoutHittingMine) {
    srand(0);
    board.populate_board(2, 0);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (!(i == 0 && j == 0) &&
                !(i == 0 && j == 2) &&
                !(i == 0 && j == 14) &&
                !(i == 1 && j == 7) &&
                !(i == 2 && j == 9) &&
                !(i == 2 && j == 11) &&
                !(i == 2 && j == 12) &&
                !(i == 3 && j == 12) &&
                !(i == 4 && j == 2) &&
                !(i == 4 && j == 3) &&
                !(i == 4 && j == 14) &&
                !(i == 6 && j == 1) &&
                !(i == 6 && j == 2) &&
                !(i == 7 && j == 4) &&
                !(i == 7 && j == 12) &&
                !(i == 7 && j == 15) &&
                !(i == 8 && j == 15) &&
                !(i == 9 && j == 1) &&
                !(i == 9 && j == 6) &&
                !(i == 10 && j == 0) &&
                !(i == 10 && j == 1) &&
                !(i == 10 && j == 4) &&
                !(i == 10 && j == 6) &&
                !(i == 10 && j == 12) &&
                !(i == 10 && j == 13) &&
                !(i == 11 && j == 1) &&
                !(i == 11 && j == 5) &&
                !(i == 11 && j == 10) &&
                !(i == 11 && j == 15) &&
                !(i == 12 && j == 0) &&
                !(i == 12 && j == 1) &&
                !(i == 13 && j == 3) &&
                !(i == 13 && j == 15) &&
                !(i == 14 && j == 4) &&
                !(i == 14 && j == 6) &&
                !(i == 14 && j == 12) &&
                !(i == 15 && j == 0) &&
                !(i == 15 && j == 1) &&
                !(i == 15 && j == 5) &&
                !(i == 15 && j == 11)) {
                board.reveal(i, j);
            }
        }
    }

    EXPECT_EQ(board.has_cleared_board(), true);
}
