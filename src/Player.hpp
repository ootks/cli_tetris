#include "TetrisBoard.hpp"
#include "Tetromino.hpp"
class Player{
private:
    TetrisBoard *board;
    bool available[WIDTH][HEIGHT][4];
public:
    Player(TetrisBoard *my_board);
    void get_moves();
}
