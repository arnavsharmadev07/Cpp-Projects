#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include "piece.h"

using namespace std;
class ChessBoard{
    Piece* board[8][8];
    bool play = true;
    char boardX[8] = {'A','B','C','D','E','F','G','H'};
    char cellCorner = '+',cellY = '|';
    int chance_count = 0;
    string cellX = "-----------",player1,player2;
    void setPieces();
    void loopAction1(vector<int> & vec,string & position,int & exitCode);
    void kill_MovePiece(int x,int y,vector<int> move);
    int gameLoop();
    void runGame();
    void fetchPastGame();
    public:
        ChessBoard();
        void game();
        void printBoard();
};
#endif