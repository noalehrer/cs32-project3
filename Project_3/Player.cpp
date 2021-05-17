//
//  Player.cpp
//  Project_3
//
//  Created by Noa Lehrer on 5/10/21.
//


#include "provided.h"
#include <string>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
private:
    
    pair<int,int> determineBestMove(Scaffold& s, int N, int color, bool am_i_max, int turn_count);
//    bool am_i_max = true;
    int init_color;
//    pair<int,int> minimax(Scaffold& s, int N, int color, int turn_count);
////    pair<int,int> minimax(Scaffold& s, int N, int color, int turn_count, bool am_i_max);
////    pair<int,int> minimax(Scaffold& s, int N, int color, vector<int,int> collection);
//
//
//    pair<int,int> determineBestMove(Scaffold& s, int N, int color, int turn_count);
////    int chooseMoveHelper(Scaffold& s, int N, int color, bool am_i_max);
//    bool am_i_max = true;
//    int init_color;
    
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if(s.numberEmpty()==0){
        cerr<<"Game is full, no moves available."<<endl;
        return 0;
    }
    cerr << "Where would you like to drop a checker?  ";
    int column;
    cin>>column;
    
    if(column<1 || column>s.cols()){
        cerr<<"That's an invalid column, silly! Try again. "<<endl;
        return chooseMove(s, N, color);
    }
    
    for(int i = 1; i<=s.levels();i++){
        if(s.checkerAt(column, i)==VACANT){
            return column;
        }
    }
    
    cerr<<"That column was full, try a different one!"<<endl;
    return chooseMove(s, N, color);
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int columns = s.cols();
    int levels = s.levels();
    
    //starting at "human" column 1 (the leftmost column)
    for(int i = 1; i<=columns; i++){
        //starting at "human" level 1 (the bottom level)
        for(int j = 1; j<=levels; j++)
            //if there is a free space, bad player will put their checker in this column
            //the checkerAt function adjusts levels and cols for us, makes sure it is in range :)
            if(s.checkerAt(i, j)==VACANT){
                return i;
            }
    }
    return 0;  //  no move was possible
}

int other(int color){
    if(color == RED){
        return BLACK;
    }
    return RED;
}
pair<int,int> SmartPlayerImpl::determineBestMove(Scaffold& s, int N, int color, bool am_i_max, int turn_count){
    vector<pair<int,int>> collection;
    pair<int,int> best;

    for(int i = 1; i<=s.cols(); i++){
        if(s.makeMove(i, color)){
            int score = rating(s, N, init_color);
            if(score==0){
                return determineBestMove(s, N, other(color), !am_i_max, turn_count+1);
            }
            score = rating(s, N, init_color);
            if(score!=0){
                best = make_pair(i,rating(s,N,init_color));
                collection.push_back(best);
            }
            s.undoMove();
        }
    }
    
    if(am_i_max==true){
        for(int i = 0; i<collection.size(); i++){
            if(best.second<collection[i].second){
                best = collection[i];
            }
        }
    }
    if(am_i_max==false){
        for(int i = 0; i<collection.size(); i++){
            if(best.second>collection[i].second){
                best = collection[i];
            }
        }
    }
    
    return best;
}
   
int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    Scaffold copy = s;
    bool am_i_max = true;
    init_color = color;
    return determineBestMove(copy, N, color, am_i_max,0).first;
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
