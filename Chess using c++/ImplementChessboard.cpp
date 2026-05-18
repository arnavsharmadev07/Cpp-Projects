#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include "Chessboard.h"
#include "utilityfuncs.h"

using namespace std;

void ChessBoard :: setPieces(){
    char out;
    for(int i = 0;i < 8; i++){
        if(i == 0 || i == 1) out = 'B';
        if(i == 6 || i == 7) out = 'W';
        for(int j = 0; j < 8;j++){
            if(i == 0 || i ==7){
                if(j==0 || j==7) board[i][j] = new Rook(out);
                else if(j==1 || j==6) board[i][j] = new Knight(out);
                else if(j==2 || j==5) board[i][j] = new Bishop(out);
                else if(j == 3) board[i][j] = new Queen(out);
                else{board[i][j] = new King(out);}
            }
            else if(i == 1 || i ==6){
                board[i][j] = new Pawn(out);
            }
            else{
                board[i][j] = nullptr;
            }
        }
    }
}

ChessBoard :: ChessBoard(){setPieces();}

void ChessBoard ::game(){
    int choice;
    cout<<endl<<endl
        <<"--- Welcome to the CONSOLE CHESS ---\n\t"<<"1. Enter (1) to Play Chess.\n\t2. Enter (2) to Fetch Past games. \n\t3. Enter (3) to Quit\n\nChoice-->";
    cin>>choice;
    switch(choice){
        case 1:
            runGame();
        break;
        case 2:
            system("cls");
            fetchPastGame();
            game();
            break;
        case 3:
            cout<<"Exiting..";
            return;
            break;
        default:
            do{
                cout<<"Invalid number entered,please try again!\n";
                cin>>choice;
            } while(choice != 1 || choice != 2 || choice != 3);
    }
}
void ChessBoard :: printBoard(){
    system("cls");
    int totalPadding = 8*(cellX.length()) + 9;
    int left_Padding2 = (totalPadding - player2.length())/2;
    int left_Padding1 = (totalPadding - player1.length())/2;
    cout<<string(left_Padding2,' ')<<player2<<endl;
    int gap = 2+int(cellX.length()/2);
    int boardY = 8;
    cout<<setw(gap);
    for(int i = 0; i < 8;i++){
        cout<<boardX[i];
        if(i!=7) cout<<setw(cellX.length()+1);
    }
    cout<<endl;
    for(int i = 0;i<9;i++){
        cout<<cellCorner;
        for(int j = 0;j<8;j++){
            cout<<cellX<<cellCorner;
        }
        if(i!=8) cout<<endl;
        for(int m = 0;m <3 && i!=8;m++){
            cout<<cellY;
            for(int k = 0; (k < 8 );k++){
                if(board[i][k]!=nullptr && m==1){
                    string fullPeice = board[i][k]->retName() + "[" + board[i][k]->retPlayerType() + "]";
                    int totalPadding = 11 - fullPeice.length();
                    int leftPadding = totalPadding/2;
                    int rightPadding = totalPadding - leftPadding; 
                    cout<<string(leftPadding,' ')<<fullPeice<<string(rightPadding,' ')<<cellY;
                }
                else{
                    cout<<setw(12)<<cellY;
                }
            }
            if(m == 1) cout<<setw(2)<<boardY;
            cout<<endl;
        }
        boardY--;
    }
    cout<<endl<<string(left_Padding1,' ')<<player1<<endl;
}
void ChessBoard :: loopAction1(vector<int> & vec,string & position,int & exitCode){
    if(vec[0]==-2){exitCode = -2; return;}
    if(vec[0]==-1){
        vec.clear();
        cout<<"Invalid format!please try again--> ";
        cin>>position;
        vector<int> temp = chessCordsTOarrayCords(position);
        vec.push_back(temp[0]);
        vec.push_back(temp[1]);
        if(vec[0] == -2){exitCode =-2;return;}
        if(vec[0] == -1){exitCode =-1;return;}
    }
    exitCode  = 1;
    return;
};
void ChessBoard :: kill_MovePiece(int x,int y,vector<int> move){
    if(board[move[0]][move[1]] != nullptr){
        delete board[move[0]][move[1]];
    }
    board[move[0]][move[1]] = board[x][y];
    board[x][y] = nullptr;
}
int ChessBoard :: gameLoop(){
    //-2 means exit -1 means invalid input and 1 means correct validation + move and 2 means fails coz of check 
    int exitCode;
    string chance,position_current,position_move;
    bool moveVerified;
    char playerType;
    if(chance_count%2 == 0){ chance = player1;playerType = 'W';}
    else{chance = player2; playerType = 'B';}
    cout<<chance<<" is now Playing!(press E to exit game)...\n";
    cout<<"Current position of the piece --> ";
    cin>>position_current;
    vector<int> cPlace = chessCordsTOarrayCords(position_current);
    loopAction1(cPlace,position_current,exitCode);
    if(board[cPlace[0]][cPlace[1]]->retPlayerType() != playerType){
        cPlace.clear();
        cout<<chance<<"'s move!try again -->";
        cin>>position_current;
        vector<int> temp = chessCordsTOarrayCords(position_current);
        cPlace.push_back(temp[0]);
        cPlace.push_back(temp[1]);
        if(board[cPlace[0]][cPlace[1]]->retPlayerType() != playerType) return -1;
    }
    switch(exitCode){
        case -2:
            return -2;
            break;
        case -1:
            return -1;
            break;
        default:break;
    }
    if(exitCode == 1){
        string pieece = board[cPlace[0]][cPlace[1]]->retName() + '[' + chance.at(0) + ']';
        cout<<"Enter you move for "<<pieece<<" --> ";
        cin>>position_move;
        if(position_current==position_move){
            cout<<"Invalid move!please try again -->";
            cin>>position_move;
            if(position_current == position_move){exitCode = -1; return exitCode;}
        }
        vector<int> mPlace = chessCordsTOarrayCords(position_move);
        loopAction1(mPlace,position_move,exitCode);
        switch(exitCode){
            case -2:
                return -2;
                break;
            case -1:
                return -1;
                break;
            default:break;
        }
        if(exitCode == 1){
            bool moveVerified = board[cPlace[0]][cPlace[1]]->validateMove(board,cPlace[0],cPlace[1],position_move);
            if(moveVerified){
                kill_MovePiece(cPlace[0],cPlace[1],mPlace);
                cPlace.clear();
                chance_count++;
                return 1;
            }
            return moveVerified;
        }
    }
    return -2;
}
void ChessBoard :: runGame(){
    int repeat;
    cout<<"Enter the name of player 1 (White) --> ";
    cin>>player1;
    cout<<"\nEnter the name of player 2 (Black) --> ";
    cin>>player2;
    player2+="(Black)";
    player1+="(White)";
    do{
        this->printBoard();
        repeat = gameLoop();
        system("cls");
    }while(repeat == 1 && repeat !=-2 || repeat==-1);
    cout<<repeat;
}
void ChessBoard :: fetchPastGame(){
    int exit;
    cout<<"\n Press 0 to exit game record.\n";
    do{
        cin>>exit;
        if(exit != 0) cout<<"Invalid key pressed! Please try again -->";
    } while(exit!=0);
    system("cls");
}