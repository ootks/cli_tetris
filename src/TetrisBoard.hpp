#ifndef TETRISBOARD_H
#define TETRISBOARD_H
#define T_LEFT -1
#define T_RIGHT 1
#define DESCEND -2
#define ROTATE_CC 2
#define ROTATE_CW 3
#include "Tetromino.hpp"

class TetrisBoard{
public:
    TetrisBoard(bool);
	TetrisBoard();
	void play();
	bool next_frame();
	void move(int dir);
	bool check(Tetromino tet);
    bool occupied(int x, int y);
    Position get_curr(int i);
//    friend void curses_display(TetrisBoard board, int max_row, int max_col);
private:
    void init(int type);
	bool is_occupied[WIDTH][HEIGHT];
	Color colors[WIDTH][HEIGHT];
	Tetromino curr;
	int frame_time;

    void set_occupied(bool on, Position pos);
};
#endif