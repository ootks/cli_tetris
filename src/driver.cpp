#include <ncurses.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Helper.hpp"
#include "Tetromino.hpp"
#include "TetrisBoard.hpp"

void curses_display(TetrisBoard board, int max_row, int max_col, std::ofstream *write);

int main()
{
    //Represents the game state
    TetrisBoard board;
    //IS true if the game is still playing
    bool continuing = true;


    //Initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);

    //Initialize random number generator
    srand(time(NULL));

    //Puts the number of rows and
    //columns in row, col
    int row, col;
    getmaxyx(stdscr, row, col);

    //The starting time of the
    //program
    time_t start_time = time(0);

    //Display starting image
    curses_display(board, row, col, NULL);
    //Prevents the image from being
    //displayed for the first second
    bool display = false;

    //Writes all of the frames
    //to file
    std::ofstream *write;
    std::ofstream log("tet_log.txt");

    //Continue playing until 
    //the player quits or loses
    while(continuing){
        display = false;
        write = NULL;

        //Reads the next character
        //immediately
        timeout(0);

        //Get the next character
        int c = getch();

        //If the user hits <-
        //move the piece to the 
        //left
        if(c == KEY_LEFT){
            board.move(Left);
            display = true;
        }
        //If the user hits ->
        //move the piece to the 
        //right
        else if(c == KEY_RIGHT){
            board.move(Right);
            display = true;
        }
        //If the user hits down,
        //move the piece down
        //one squaree
        else if(c == KEY_DOWN){
            board.move(Descend);
            display = true;
        }
        //If the user hits up,
        //rotate the piece 
        //counter clockwise
        else if(c == KEY_UP){
            board.move(Rotate_CC);
            display = true;
        }
        //If the user hits q,
        //move to the quit option
        //if the user hits yes, 
        //quit
        else if(c == 'q'){
            //Stop the drawing
            timeout(-1);
            if(getch() == 'y'){
                endwin();
                log.close();
                exit(0);
            }
        }
        //If the user hits space,
        //hard drop
        else if(c == ' '){
            board.move(Drop);
            display = true;
            write = &log;
            start_time = time(0);
        }
        //If there has been a timestep
        if(time(NULL) - start_time > .1){
            //Move the board to the 
            //next timestep, 
            //then continue only if
            //the user hasn't lost
            continuing = board.next_frame();
            //redraw only if something
            //changes
            display = true;
            write = &log;
            start_time = time(0);
        }
        if(display){
            clear();
            curses_display(board, row, col, write);
        }
        refresh();
    }

    log.close();

    getch();
    endwin();

    return 0;
}

/**Display the tetris board, which has 
 * max_row rows, and max_col columns
 * to the ofstream.
 */
void curses_display(TetrisBoard board, int max_row, int max_col, std::ofstream *log){
    char row_msg[WIDTH + 1];
    row_msg[WIDTH] = '\0';

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            row_msg[j] = (board.occupied(j, i) ? '#' : ' ');
        }

        mvprintw((max_row-HEIGHT)/2 + i, (max_col-WIDTH)/2-1, "|%s|", row_msg);
        if(log != NULL){
            log->write(row_msg, WIDTH);
            log->write("\n",1);
        }
    }

    if(log != NULL){
        log->write("\n",1);
    }

    for(int j = 0; j < WIDTH; j++){
        row_msg[j] = '-';
    }
    mvprintw((max_row+HEIGHT)/2, (max_col-WIDTH)/2, "%s", row_msg);

    for(int j = 0; j < 4; j++){
        mvprintw((max_row-HEIGHT)/2 + board.get_curr(j).y, (max_col-WIDTH)/2 + board.get_curr(j).x, "%s", "x");
    }
    for(int j = 0; j < 4; j++){
        mvprintw((max_row-HEIGHT)/2 + board.get_next(j).y, (max_col-WIDTH)/2 - 10 + board.get_next(j).x, "%s", "x");
    }

    mvprintw((max_row-HEIGHT)/2, (max_col-WIDTH)/2 + 10, "%d", board.get_score());
}
