SRCDIR = src
OBJDIR = obj
BINDIR = bin
DOCDIR = doc

CC = g++
LD = g++
CFLAGS = 
CPPFLAGS = -std=c++0x -g
LDFLAGS = ``
BINS = $(CLIENT_BINS) $(SERVER_BINS) $(TESTSUITE_BINS)

driver: game.o board.o tetromino.o
	$(CC) -o tetris $(OBJDIR)/game.o $(OBJDIR)/board.o $(OBJDIR)/tetromino.o -lncurses

game.o: src/driver.cpp 
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/driver.cpp -o $(OBJDIR)/game.o

board.o: src/TetrisBoard.cpp src/TetrisBoard.hpp 
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/TetrisBoard.cpp -o $(OBJDIR)/board.o 

tetromino.o: src/Tetromino.cpp src/Tetromino.hpp src/Helper.hpp
	$(CC) $(CPPFLAGS) -c $(SRCDIR)/Tetromino.cpp -o $(OBJDIR)/tetromino.o 

client0 : $(addprefix $(OBJDIR)/,$(CLIENT0_OBJS))
	$(LD) -o $(BINDIR)/$@ $^ $(LDFLAGS)

clean:
	rm $(addprefix $(BINDIR)/,$(BINS)) $(OBJDIR)/*.o

clean-docs:
	rm -r $(DOCDIR)/*
