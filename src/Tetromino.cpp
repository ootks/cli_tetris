#include "Tetromino.hpp"
#include <stdlib.h>
#include <time.h>
#include <array>

Tetromino::Tetromino(){
    srand(time(NULL));
    init(rand()%7);
}
void Tetromino::init(int type){
	std::array<Position, 4> temp;
	if(type == STILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 - 1, 1)};
        barycenter = Position(WIDTH+1, 1);
		color = Color(RED);
	}
	if(type == ZTILE){
		temp = {Position(WIDTH/2 - 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 + 1, 1)};
        barycenter = Position(WIDTH+1, 1);
		color = Color(BLUE);
	}
	if(type == LTILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 - 1, 1)};
        barycenter = Position(WIDTH, 2);
		color = Color(GREEN);
	}
	if(type == ITILE){
		temp = {Position(WIDTH/2 + 2, 0),
				   Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1, 0)};
        barycenter = Position(WIDTH + 2, 0);
		color = Color(GREEN);
	}
	if(type == OTILE){
		temp = {Position(WIDTH/2, 1),
				   Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 + 1, 0)};
        barycenter = Position(WIDTH + 1, 1);
		color = Color(PURPLE);
	}
	if(type == TTILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1,0),
				   Position(WIDTH/2, 1)};
        barycenter = Position(WIDTH, 0);
		color = Color(ORANGE);
	}
	if(type == JTILE){
		temp = {Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1, 0)};
        barycenter = Position(WIDTH, 0);
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
        tet.barycenter.x = barycenter.x + 2*dir;
        tet.barycenter.y = barycenter.y;
	}
	return tet;
}

Tetromino Tetromino::rotate(int dir){
	Tetromino tet;
	for(int i = 0; i < 4; i++){
		tet.squares[i].x = (int)(dir*(squares[i].y - barycenter.y/2.0) + barycenter.x/2.0);
		tet.squares[i].y = (int)(dir*(barycenter.x/2.0 - squares[i].x) + barycenter.y/2.0);
        tet.barycenter.x = barycenter.x;
        tet.barycenter.y = barycenter.y;
	}
	return tet;
}

Tetromino Tetromino::descend(){
	Tetromino tet;
	for(int i = 0; i < 4; i++){
		tet.squares[i].x = squares[i].x;
		tet.squares[i].y = squares[i].y+1;
        tet.barycenter.x = barycenter.x;
		tet.barycenter.y = barycenter.y+2;
	}
    return tet;
}
