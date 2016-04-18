#ifndef TETROMINO_H
#define TETROMINO_H
#define STILE 0
#define ZTILE 1
#define LTILE 2
#define ITILE 3
#define OTILE 4
#define TTILE 5

#define JTILE 6
#define RED 255, 0, 0
#define BLUE 0, 255, 0
#define GREEN 0, 0, 255
#define ORANGE 255, 125, 0
#define PURPLE 255, 100, 100
#define TEAL 0, 255, 255

#include "Helper.hpp"

class TetrisBoard;

class Tetromino{
friend class TetrisBoard;
public:
	Tetromino();
//	Tetromino();
	Tetromino(const Tetromino &tet);
	Tetromino rotate(int dir);
	Tetromino move(int dir);
	Tetromino drop();
	Tetromino descend();
    friend void curses_display(TetrisBoard board, int max_row, int max_col);
private:
	Position squares[4];
    void init(int type);
	Color color;
};
#endif
