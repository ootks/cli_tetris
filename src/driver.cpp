#include <ncurses.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include "Helper.hpp"
#include "Tetromino.hpp"
#include "TetrisBoard.hpp"

void curses_display(TetrisBoard board, int max_row, int max_col);

int main()
{
    TetrisBoard board;
    bool continuing = true;

    initscr();

    int row, col;
    getmaxyx(stdscr, row, col);

    while(continuing){
        clear();
        
        curses_display(board, row, col);
        continuing = board.next_frame();
        
        timeout(1000);
        getch();
        refresh();
    }

    getch();
    endwin();

    return 0;
}

void curses_display(TetrisBoard board, int max_row, int max_col){
    char row_msg[WIDTH + 1];
    row_msg[WIDTH] = '\0';

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            row_msg[j] = (board.occupied(j, i) ? '*' : '_');
        }

        mvprintw((max_row-HEIGHT)/2 + i, (max_col-WIDTH)/2, "%s", row_msg);
    }

    for(int j = 0; j < 4; j++){
        mvprintw((max_row-HEIGHT)/2 + board.get_curr(j).y, (max_col-WIDTH)/2 + board.get_curr(j).x, "%s", "x");
    }
}
