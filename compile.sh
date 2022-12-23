echo "Making ./bin ..."
mkdir bin


echo "Compiling 'tests' ..."
g++ -Wall -std=c++17 -lgtest -lgtest_main -I include/minesweeper tests/*.cpp lib/Board.cpp lib/Cell.cpp -Ofast -o bin/tests
echo "Finished compiling 'tests'"

echo "Compiling 'minesweeper' ..."
g++ -Wall -std=c++17 -lncurses -I include/minesweeper src/*.cpp lib/*.cpp -Ofast -o bin/minesweeper
echo "Finished compiling 'minesweeper'"
