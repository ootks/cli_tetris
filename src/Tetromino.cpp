#include "Tetromino.hpp"
#include <stdlib.h>
#include <time.h>
#include <array>

Tetromino::Tetromino(){
    init(rand()%7);
}
void Tetromino::init(int my_type){
	std::array<Position, 4> temp;
	if(my_type == STILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 - 1, 1)};
        barycenter = Position(WIDTH+1, 1);
		color = Color(RED);
        n_orient = 2;        
	}
	if(my_type == ZTILE){
		temp = {Position(WIDTH/2 - 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 + 1, 1)};
        barycenter = Position(WIDTH+1, 1);
		color = Color(BLUE);
        n_orient = 2;        
	}
	if(my_type == LTILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2, 1),
				   Position(WIDTH/2 - 1, 1)};
        barycenter = Position(WIDTH, 2);
		color = Color(GREEN);
        n_orient = 4;        
	}
	if(my_type == ITILE){
		temp = {Position(WIDTH/2 + 2, 0),
				   Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1, 0)};
        barycenter = Position(WIDTH + 2, 0);
		color = Color(GREEN);
        n_orient = 2;        
	}
	if(my_type == OTILE){
		temp = {Position(WIDTH/2, 1),
				   Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 + 1, 0)};
        barycenter = Position(WIDTH + 1, 1);
		color = Color(PURPLE);
        n_orient = 1;        
	}
	if(my_type == TTILE){
		temp = {Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1,0),
				   Position(WIDTH/2, 1)};
        barycenter = Position(WIDTH, 0);
		color = Color(ORANGE);
        n_orient = 4;        
	}
	if(my_type == JTILE){
		temp = {Position(WIDTH/2 + 1, 1),
				   Position(WIDTH/2 + 1, 0),
				   Position(WIDTH/2, 0),
				   Position(WIDTH/2 - 1, 0)};
        barycenter = Position(WIDTH, 0);
		color = Color(TEAL);
        n_orient = 4;        
	}
	for(int i = 0; i < 4; i++){
		squares[i] = temp[i];
	}
}

Tetromino::Tetromino(const Tetromino *tet){
	for(int i = 0; i < 4; i++){
		squares[i] = tet->squares[i];
	}
    barycenter = tet->barycenter;
    orient = tet->orient;
    n_orient = tet->n_orient;
}

Tetromino::Tetromino(const Tetromino &tet){
	for(int i = 0; i < 4; i++){
		squares[i] = tet.squares[i];
	}
    barycenter = tet.barycenter;
}

Tetromino Tetromino::translate(int dir){
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
	Tetromino tet(this);	
	for(int i = 0; i < 4; i++){
		tet.squares[i].x = (int)(dir*(squares[i].y - barycenter.y/2.0) + barycenter.x/2.0);
		tet.squares[i].y = (int)(dir*(barycenter.x/2.0 - squares[i].x) + barycenter.y/2.0);
	}
    tet.orient = (tet.orient + 1) % n_orient;
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
    orient = 0;
    return tet;
}

int Tetromino::get_orient(){
    return orient;
}
int Tetromino::get_n_orient(){
    return n_orient;
}

Tetromino Tetromino::move(Move dir){
    switch(dir){
        case Left:
            return translate(-1);
            break;
        case Right:
            return translate(1);
            break;
        case Descend:
           return descend();
           break;
        case Rotate_CC:
           return rotate(-1);
           break;
        default:
           return descend();
    }
}
