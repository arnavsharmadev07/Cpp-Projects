#include <iostream>
#include <vector>
#include <string>
#include "Piece.h"
#include "utilityfuncs.h"

using namespace std;

/*       Piece class       */
Piece :: Piece(){}
Piece :: Piece(char playerType){
    this->playerType = playerType;
};
int Piece :: myModulus(int n){
    if(n>=0) return n;
    else{
        return -n;
    }
}
char Piece :: retPlayerType(){
    return playerType;
}
bool Piece :: validateMotion(Piece *board[8][8],int i_c,int j_c,int i_m,int j_m){
    char type1 = this->playerType;
    int rowStep = (i_c==i_m)? 0:(i_c<i_m)? 1:-1;
    int colStep = (j_c==j_m)? 0:(j_c<j_m)? 1:-1;
    if(board[i_m][j_m]!=nullptr){
        char type2 = board[i_m][j_m]->retPlayerType();
        if(type1==type2){
            return false;
        }
    }
    while((i_c != i_m) || (j_c != j_m)){
        i_c+=rowStep;
        j_c+=colStep;
        if(board[i_c][j_c] != nullptr){
            return false;
        }
    }
    return true;
};
Piece :: ~Piece(){}

/*       Rook class       */

Rook :: Rook(){}
Rook :: Rook(char c) : Piece(c){}
bool Rook :: validateMove(Piece* board[8][8],int i,int j,string move){
    vector<int> X_Y = chessCordsTOarrayCords(move);
    int rowDifference = myModulus(X_Y[0]-i),colDifference = myModulus(X_Y[1]-j); 
    if((rowDifference==0 && colDifference>0) || (rowDifference >0 && colDifference==0)){
        if(validateMotion(board,i,j,X_Y[0],X_Y[1])){
            return true;
        }
        return false;
    }
    else{return 0;}
}

/*       Knight class       */

Knight :: Knight(char c) : Piece(c){}
bool Knight :: validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m){return true;}
bool Knight :: validateMove(Piece* board[8][8],int i,int j,string move){
    vector<int> X_Y = chessCordsTOarrayCords(move);
    int colDifference = myModulus(X_Y[1]-j),rowDifference = myModulus(X_Y[0]-i);
    char type1 = this->playerType;
    if((colDifference == 2 && rowDifference ==1) || (colDifference == 1 && rowDifference ==2)){
        if(board[X_Y[0]][X_Y[1]]!= nullptr){
            char type2 = board[X_Y[0]][X_Y[1]]->retPlayerType();
            if(type1!=type2) return true;
            else{ return false;}
        }
        else{
            return true;
        }
    }
    else{return false;}
}

/*       Bishop class       */

Bishop :: Bishop(){}
Bishop :: Bishop(char c) : Piece(c){}
bool Bishop :: validateMove(Piece* board[8][8],int i,int j,string move){
    vector<int> X_Y = chessCordsTOarrayCords(move);
    int colDifference = myModulus(X_Y[1]-j),rowDifference = myModulus(X_Y[0]-i);
    if(colDifference==rowDifference){
        if(validateMotion(board,i,j,X_Y[0],X_Y[1])){
            return true;
        }
        return false;
    }
    else{return false;}
}

/*       Queen class       */

Queen :: Queen(char c) : Piece(c){}
bool Queen :: validateMove(Piece* board[8][8],int i,int j,string move){
    bool rookMove = Rook::validateMove(board,i,j,move);
    bool bishopMove = Bishop::validateMove(board,i,j,move);
    if(rookMove || bishopMove){return true;}
    else{return false;}
}

/*       King class       */

King :: King(char c) : Piece(c){}
bool King :: validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m){
    int rowGap = (i_c<i_m)?1:-1;
    int colGap = (j_c<j_m)?1:-1;
    while(i_c==i_m && j_c==j_m){
        //this needs to be done
    }
}
bool King :: validateMove(Piece* board[8][8],int i,int j,string move){
    vector<int> X_Y = chessCordsTOarrayCords(move);
    int colDifference = myModulus(X_Y[1]-j),rowDifference = myModulus(X_Y[0]-i);
    if(colDifference == 1 || rowDifference == 1){
        
    }
}

/*       Pawn class       */

Pawn ::  Pawn(char c) : Piece(c){}
bool Pawn :: validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_M){return true;}
bool Pawn :: validateMove(Piece* board[8][8],int i,int j,string move){
    vector<int> X_Y = chessCordsTOarrayCords(move);
    int colDifference = X_Y[1]-j,rowDifference = X_Y[0]-i;
    if((this->playerType == 'B' && rowDifference>0) || (this->playerType == 'W' && rowDifference<0)){
        if(myModulus(rowDifference) == 1 && colDifference == 0){
            if(board[X_Y[0]][X_Y[1]] == nullptr){
                return true;
            }
        }
        if(myModulus(rowDifference)== 1 && myModulus(colDifference) == 1 && board[X_Y[0]][X_Y[1]]!=nullptr){
            if(this->playerType != board[X_Y[0]][X_Y[1]]->retPlayerType()){
                return true;
            }
        }
        if(i==1 || i == 6 && myModulus(rowDifference) == 2 && myModulus(colDifference) == 0){
            return true;
        }
    }
    return false;
}

// retPiece name function for all classes
string Rook   :: retName(){return pieceName;}
string Knight :: retName(){return pieceName;}
string Bishop :: retName(){return pieceName;}
string Queen  :: retName(){return pieceName;}
string King   :: retName(){return pieceName;}
string Pawn   :: retName(){return pieceName;}