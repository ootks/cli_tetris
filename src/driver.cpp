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

    time_t start_time = time(0);

    curses_display(board, row, col);
    bool display = false;

    while(continuing){
        display = false;
        if(time(NULL) - start_time > 1){
            continuing = board.next_frame();
            display = true;
            start_time = time(0);
        }
        if(display){
            clear();
            curses_display(board, row, col);
        }
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
