#include <iostream>
#include <vector>
#include "utilityfuncs.h"
vector<int> chessCordsTOarrayCords(string position){
    //-1 is an error!!!!
    //-2 is an exit flag!!!
    vector<int> temp;
    bool noterror1  = 0,noterror2 = 0;
    if(position.length()!=2){
        if(position == "E"){ temp.push_back(-2);}
        else{
            temp.push_back(-1);
        }
        return temp;
    }
    for(char a = 'a'; a<='h';a++){
        if(tolower(position[0])==a){
            noterror1 = 1;
        }
    }
    for(int i = 1;i<=8;i++){
        if((position[1]-'0')==i){
            noterror2 = 1;
        }
    }
    if(!noterror1 && !noterror2){
        temp.push_back(-1);
        return temp;
    }
    int y = tolower(position[0]) - 'a'; // a is a decimal number learn 1
    int x=8-int(position.at(1) - '0');
    if(x <0 || x>7 || y>7 || y <0){
        temp.push_back(-1);
        return temp;  
    } 
    temp.push_back(x);
    temp.push_back(y);
    return temp;
}