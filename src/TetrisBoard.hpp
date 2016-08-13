#ifndef TETRISBOARD_H
#define TETRISBOARD_H
#define LEFT -1
#define RIGHT 1
#define DESCEND -2
#define ROTATE_CC 2
#define ROTATE_CW 3
#include "Tetromino.hpp"
#include "Helper.hpp"

class TetrisBoard{
public:
    TetrisBoard(bool);
	TetrisBoard();
	void play();
	bool next_frame();
	bool move(Move dir);
    bool check(Tetromino tet);
    bool occupied(int x, int y);
    Position get_curr(int i);
    Position get_next(int i);
    void clear_lines();
    int get_score();
//    friend void curses_display(TetrisBoard board, int max_row, int max_col);
    bool get_valid_moves(Tetromino tet, Tetromino *moves, int *n_moves);
private:
    void init(int type);
	bool is_occupied[WIDTH][HEIGHT];
	Color colors[WIDTH][HEIGHT];
	Tetromino curr, next;
	int frame_time;
    int score;

    void set_occupied(bool on, Position pos);
};
#endif
