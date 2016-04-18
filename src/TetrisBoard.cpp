#include "TetrisBoard.hpp"
#include <stdio.h>
//TetrisBoard::TetrisBoard(bool test){
//	for(int i = 0; i < HEIGHT; i++){
//		for(int j = 0; j < WIDTH; j++){
//			is_occupied[i][j] = false;
//		}
//	}
//    for(int i = 0; i < 10; i++){
//		for(int j = 0; j < WIDTH; j++){
//			is_occupied[i][j] = true;
//		}
//    }
//}

/* Construct a tetris board*/
TetrisBoard::TetrisBoard(){
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			is_occupied[i][j] = false;
		}
	}
    curr = Tetromino();
}

bool TetrisBoard::next_frame(){
    Tetromino tet = curr.descend();
    if(check(tet)){
      curr = tet;
    }
    else{
        for(int i = 0; i < 4; i++){
            set_occupied(true, curr.squares[i]);
        }
        curr = Tetromino();
        if(!check(curr)){
            return false;
        }	
    }
    return true;
}

bool TetrisBoard::check(Tetromino tet){
	for(int i = 0; i < 4; i++){
		if(is_occupied[tet.squares[i].x][tet.squares[i].y]){
			return false;
		}
        if(tet.squares[i].y < 0 || tet.squares[i].x < 0 || tet.squares[i].y >= HEIGHT || tet.squares[i].x >= WIDTH){
            return false;
        }
	}
	return true;
}

void TetrisBoard::set_occupied(bool on, Position pos){
    is_occupied[(pos.x)][(pos.y)] = true;
}
bool TetrisBoard::occupied(int x, int y){
    return is_occupied[x][y];
}

Position TetrisBoard::get_curr(int i){
    return curr.squares[i];
}
//void TetrisBoard::move(int dir){
//    Tetromino tet;
//    if(dir == T_LEFT){
//       tet = curr.move(-1);
//    }
//    if(dir == T_RIGHT){
//       tet = curr.move(1);
//    }
//    if(dir == DESCEND){
//       tet = curr.descend();
//    }
//    if(dir == ROTATE_CC){
//        tet = curr.rotate(-1);
//    }
//    if(dir == ROTATE_CW){
//        tet = curr.rotate(1);
//    }
//    if(check(tet)){
//        curr = tet;
//    }
//
//}
