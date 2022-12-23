echo "Making ./bin ..."
mkdir bin

echo "Compiling 'minesweeper' ..."
g++ -Wall -std=c++17 -march=native -lncurses -I include/minesweeper src/*.cpp lib/*.cpp -Ofast -o bin/minesweeper
echo "Finished compiling 'minesweeper'"


echo "Compiling 'tests' ..."
g++ -Wall -std=c++17 -march=native -lgtest -lgtest_main -I include/minesweeper tests/*.cpp lib/Board.cpp lib/Cell.cpp -Ofast -o bin/tests
echo "Finished compiling 'tests'"
