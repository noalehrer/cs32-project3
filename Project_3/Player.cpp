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
    pair<int,int> determineBestMove(Scaffold& s, int N, int color, bool am_i_max);
    int chooseMoveHelper(Scaffold& s, int N, int color, bool am_i_max);
    bool am_i_max = true;
    int init_color;
    
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

pair<int,int> SmartPlayerImpl::determineBestMove(Scaffold& s, int N, int color, bool am_i_max){
    //MAKE IT ACTUALLY RECURSIVE... THINK THRU BASE CASES AND STUFF
    vector<pair<int,int>> collection; //store all the outcomes on one level of a branch
    //for each possible move
    for(int i = 1; i<s.cols(); i++){
        //if you can make the move
//        int score = rating(s, N, init_color);
//        pair<int,int> colScore = make_pair(i, score);
//        if(score!=0){
//            //there's an issue with how the collection is being populated... right now it only gets one pair put in???
//            collection.push_back(colScore);
//        }
        if(s.makeMove(i, color)){
            //rating should always be in terms of init_color (comp's color)
//            int score = rating(s, N, init_color);
//            pair<int,int> colScore = make_pair(i, score);
            //if the game is still in progress
            if(score==0){
                colScore = determineBestMove(s, N, other(color), !am_i_max); //recursive call to determine best move of other player
            }
            if(score!=0){
                //there's an issue with how the collection is being populated... right now it only gets one pair put in???
                collection.push_back(colScore);
            }
            s.undoMove();
        }
    }
    int score = rating(s, N, init_color);
    pair<int,int> colScore = make_pair(i, score);
    if(score!=0){
        //there's an issue with how the collection is being populated... right now it only gets one pair put in???
        collection.push_back(colScore);
    }
    pair<int,int> best;
    //pick best turn from collection
    if(!collection.empty()){
        best = collection[0];
        if(am_i_max){
            for(int i = 0; i<collection.size(); i++){
                if(collection[i].second>best.second){
                    best = collection[i];
                }
            }
        }
        if(!am_i_max){
            for(int i = 0; i<collection.size(); i++){
                if(collection[i].second<best.second){
                    best = collection[i];
                }
            }
        }
    }
    return best;
}
   
int SmartPlayerImpl::chooseMoveHelper(Scaffold& s, int N, int color, bool am_i_max){
    return determineBestMove(s, N, color, am_i_max).first;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //need to make a copy of the scaffold for it to remain const
    Scaffold copy = s;
    am_i_max = true;
    init_color = color;
    int move = chooseMoveHelper(copy, N, color, am_i_max);
    //it skips the comp's turn bc it keeps saying that col 2 is the best move,,, maybe i should make a stack
    return move;
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
