#include "TetrisBoard.hpp"
#include <stdio.h>

/* Construct a tetris board*/
TetrisBoard::TetrisBoard(){
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			is_occupied[i][j] = false;
		}
	}
    curr = Tetromino();
    next = Tetromino();
    score = 0;
}

bool TetrisBoard::next_frame(){
    if(!move(Descend)){
        for(int i = 0; i < 4; i++){
            set_occupied(true, curr.squares[i]);
        }
        clear_lines();
        curr = next;
        next = Tetromino();
        if(!check(curr)){
            return false;
        }	
    }
    return true;
}

void TetrisBoard::clear_lines(){
    //List of lines to clear
    //from top to bottom
    int lines_to_clear[4] = {-1, -1, -1, -1};
    int n_lines_to_clear = 0;
    int n_lines_cleared;
    bool clear_this_line = true;

    for(int i = HEIGHT-1; i >= 0; i--){
        //Assume the line should be cleared
        clear_this_line = true;
        //If you find an unoccupied square,
        //then the line shouldn't be deleted
        for(int j = 0; j < WIDTH; j++){
            if(!occupied(j,i)){
                clear_this_line = false;
                break;
            }
        }
        //If the line should be cleared
        if(clear_this_line){
            //The nth line to clear
            //is i
            lines_to_clear[n_lines_to_clear] = i;
            //Increment the number of lines to clear
            n_lines_to_clear++;
        }
        if(n_lines_to_clear == 4){
            break;
        }
    }
    
    if(n_lines_to_clear == 1){
        score += 40;
    }
    if(n_lines_to_clear == 2){
        score += 100;
    }
    if(n_lines_to_clear == 3){
        score += 300;
    }
    if(n_lines_to_clear == 4){
        score += 1200;
    }
    //Shift everything down
    n_lines_cleared = 0;
    for(int i = HEIGHT-1; i >= 0; i--){
        //If the next line should be cleared 
        //just don't move it, and it will be 
        //overwritten
        if(lines_to_clear[n_lines_cleared] == i){
            n_lines_cleared++;
            continue;
        }
        for(int j = 0; j < WIDTH; j++){
            is_occupied[j][i+n_lines_cleared] = is_occupied[j][i];
        }
    }

    //Clear top rows
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

Position TetrisBoard::get_next(int i){
    return next.squares[i];
}

Position TetrisBoard::get_curr(int i){
    return curr.squares[i];
}

bool TetrisBoard::move(Move dir){
    Tetromino tet = curr.descend();
    
    if(dir == Drop){
        while(check(tet)){
            curr = tet;
            tet = curr.descend();
            score += 1;
        }
         for(int i = 0; i < 4; i++){
            set_occupied(true, curr.squares[i]);
        }
        clear_lines();
        curr = next;
        next = Tetromino();

        return check(curr);
    }

    else{
        if(dir == DESCEND){
            score += 1;
        }
        tet = curr.move(dir);
    }

    if(check(tet)){
        curr = tet;
        return true;
    }
    return false;
}

bool TetrisBoard::get_valid_moves(Tetromino tet, Tetromino *moves, int *n_moves){
    Tetromino temp;
    int n_valid_moves = 0;
    for(int move = Left; move < Drop; move++){
        temp = tet.move((Move)move);
        if(check(temp)){
            moves[n_valid_moves] = temp;
            n_valid_moves++;
        }
    }
    temp = tet.move(Rotate_CC);
    if(check(temp)){
        moves[n_valid_moves] = temp;
        n_valid_moves++;
    }
    temp = temp.move(Rotate_CC);
    if(check(temp)){
        moves[n_valid_moves] = temp;
        n_valid_moves++;
    }
    temp = temp.move(Rotate_CC);
    if(check(temp)){
        moves[n_valid_moves] = temp;
        n_valid_moves++;
    }
    temp = tet.move(Descend);
    if(check(temp)){
        moves[n_valid_moves] = temp;
        n_valid_moves++;
        *n_moves = n_valid_moves;
        return true;
    }
    else{
        *n_moves = n_valid_moves;
        return false;
    }
}

int TetrisBoard::get_score(){
    return score;
}
