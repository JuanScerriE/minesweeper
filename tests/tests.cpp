// gtest
#include <gtest/gtest.h>

// minesweeper
#include <Cell.hpp>

class CellTest : public ::testing::Test {
protected:
    minesweeper::Cell cell;   
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

TEST_F(CellTest, SetCellState) {
    cell.set_state(minesweeper::Cell::State::MINE);
    EXPECT_EQ(cell.get_state(), minesweeper::Cell::State::MINE);
}

TEST_F(CellTest, ByDefaultCellIsNotMine) {
    EXPECT_EQ(cell.is_mine(), false);
}

TEST_F(CellTest, MakeCellAMine) {
    cell.make_mine();
    EXPECT_EQ(cell.is_mine(), true);
}
