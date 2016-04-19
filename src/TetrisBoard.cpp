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
    if(!move(Descend)){
        for(int i = 0; i < 4; i++){
            set_occupied(true, curr.squares[i]);
        }
        clear_lines();
        curr = Tetromino();
        if(!check(curr)){
            return false;
        }	
    }
    return true;
}

void TetrisBoard::clear_lines(){
    int lines_to_clear[5] = {-1, -1, -1, -1, -1};
    int n_lines_to_clear = 0;
    int n_lines_cleared;
    bool clear_this_line = true;

    for(int i = 0; i < HEIGHT; i++){
        clear_this_line = true;
        for(int j = 0; j < WIDTH; j++){
            if(!occupied(j,i)){
                clear_this_line = false;
                break;
            }
        }
        if(clear_this_line){
            for(int j = 0; j < WIDTH; j++){
                is_occupied[j][i] = false;
            }
            lines_to_clear[n_lines_to_clear] = i;
            n_lines_to_clear++;
        }
        if(n_lines_to_clear == 4){
            break;
        }
    }
    //Shift everything down

    n_lines_cleared = 0;
    for(int i = HEIGHT-1; i >= 0; i--){
        if(lines_to_clear[n_lines_cleared] == i){
            n_lines_cleared++;
            continue;
        }
        for(int j = 0; j < WIDTH; j++){
            is_occupied[j][i+n_lines_cleared] = is_occupied[j][i];
        }
    }
    for(int i = 0; i < n_lines_to_clear; i++){
        for(int j = 0; j < WIDTH; j++){
            is_occupied[i][j] = false;
        }
    }

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

bool TetrisBoard::move(Direction dir){
    Tetromino tet;
    if(dir == Left){
       tet = curr.move(-1);
    }
    if(dir == Right){
       tet = curr.move(1);
    }
    if(dir == Descend){
       tet = curr.descend();
    }
    if(dir == Rotate_CC){
        tet = curr.rotate(-1);
    }
    if(check(tet)){
        curr = tet;
        return true;
    }
    return false;
}
