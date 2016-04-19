#include "Tetromino.hpp"
#include <stdlib.h>
#include <time.h>
#include <array>

Tetromino::Tetromino(){
    srand(time(NULL));
    init(rand()%7);
    init(ITILE);
}
void Tetromino::init(int type){
	std::array<Position, 4> temp;
	if(type == STILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 - 1, 1)};
		color = Color(RED);
	}
	if(type == ZTILE){
		temp = {Position(WIDTH/2 - 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 + 1, 1)};
		color = Color(BLUE);
	}
	if(type == LTILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 - 1, 1)};
		color = Color(GREEN);
	}
	if(type == ITILE){
		temp = {Position(WIDTH/2 + 2, 0),
				   Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1, 0)};
		color = Color(GREEN);
	}
	if(type == OTILE){
		temp = {Position(WIDTH/2, 1),
				   Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 + 1, 0)};
		color = Color(PURPLE);
	}
	if(type == TTILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1,0),
				   Position(WIDTH/2, 1)};
		color = Color(ORANGE);
	}
	if(type == JTILE){
		temp = {Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1, 0)};
		color = Color(TEAL);
	}
	for(int i = 0; i < 4; i++){
		squares[i] = temp[i];
	}
}

Tetromino::Tetromino(const Tetromino &tet){
	for(int i = 0; i < 4; i++){
		squares[i] = tet.squares[i];
	}
}

Tetromino Tetromino::move(int dir){
	Tetromino tet;
	for(int i = 0; i < 4; i++){
		tet.squares[i].x = squares[i].x + dir;
		tet.squares[i].y = squares[i].y;
	}
	return tet;
}

Tetromino Tetromino::rotate(int dir){
	Tetromino tet;
	Position bottomMost = squares[0];
	for(int i = 1; i < 4; i++){
		if(bottomMost.y > squares[i].y){
			bottomMost = squares[i];
		}
	}
	for(int i = 0; i < 4; i++){
		tet.squares[i].x = dir*(squares[i].y - bottomMost.y) + bottomMost.y;
		tet.squares[i].y = dir*(bottomMost.x - squares[i].x) + bottomMost.y;
	}
	return tet;
}

Tetromino Tetromino::descend(){
	Tetromino tet;
	for(int i = 0; i < 4; i++){
		tet.squares[i].x = squares[i].x;
		tet.squares[i].y = squares[i].y+1;
	}
    return tet;
}
