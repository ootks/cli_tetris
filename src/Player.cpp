#include "Player.hpp"

void Player::get_moves(Tetromino tet){
   std::queue<Tetromino> to_search;
   to_search.push(tet);

   Tetromino neighbors[16];

   while(!to_search.empty()){
       tet = to_search.pop();
       for(int i = 0; i < get_neighbors(tet); i++){
            to_search.push(neighbors[i]);         

           if(!check(tet.descend)){
               available[n_available] = tet;
           }
       }
    }

}

int Player::get_neighbors(Tetromino tet, Tetromino *neighbors){
    int n_neighbors = 0;
    if(board.check(tet);
}
