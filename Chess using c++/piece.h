#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Piece{
    protected:
        char playerType;
        int myModulus(int n);
        bool checkFriend(Piece* board[8][8],int i_m,int j_M);
    public:
        Piece();
        Piece(char playerType);
        char retPlayerType();
        virtual bool validateMotion(Piece *board[8][8],int i_c = 0,int j_c = 0,int i_m = 0,int j_m = 0);
        virtual bool validateMove(Piece* board[8][8],int, int,int,int) = 0;
        virtual string retName() = 0;
        virtual ~Piece();
};
class Rook : virtual public Piece{
    string pieceName="Rook";
    public:
        Rook();
        Rook(char c);
        bool validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m);
        string retName();
};
class Knight : public Piece{
    string pieceName="Knight";
    bool validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m);
    public:
        Knight(char c);
        bool validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m);
        string retName();
};
class Bishop : virtual public Piece{
    string pieceName = "Bishop";
    public:
        Bishop();
        Bishop(char c);
        bool validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m);
        string retName();
};
class Queen : public Bishop,public Rook{
    string pieceName = "Queen";
    public:
        Queen(char c);
        bool validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m);
        string retName();
};
class King : public Piece{
    string pieceName="King";
    bool validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m);
    public:
        King(char c);
        bool validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m);
        string retName();
};
class Pawn : public Piece{
    string pieceName="Pawn";
    bool validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_M);
    public:
        Pawn(char c);
        bool validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m);
        string retName();
};
#endif