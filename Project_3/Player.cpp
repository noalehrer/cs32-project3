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
    pair<int,int> minimax(Scaffold& s, int N, int color, int turn_count);
//    pair<int,int> minimax(Scaffold& s, int N, int color, int turn_count, bool am_i_max);
//    pair<int,int> minimax(Scaffold& s, int N, int color, vector<int,int> collection);

    
    pair<int,int> determineBestMove(Scaffold& s, int N, int color, int turn_count);
//    int chooseMoveHelper(Scaffold& s, int N, int color, bool am_i_max);
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
//
pair<int,int> SmartPlayerImpl::minimax(Scaffold& s, int N, int color, int turn_count){
    //hmmm collection only ever has 1 score in it
    vector<pair<int,int>> collection;
    //base case
    //if the game is over
    if(rating(s, N, init_color)!=0){
        int column = s.undoMove();
        s.makeMove(column, color);
        collection.push_back(make_pair(column,rating(s, N, init_color)));
//        cout<<rating(s, N, init_color)<<endl;
    }
    //max
    if(turn_count%2==0){
        int bestScore = -INFINITY;
        int bestMove;
        for(int i = 1; i<s.cols(); i++){
            //if you can make the move, and the game is still not over
            if(s.makeMove(i, color) && (rating(s, N, init_color)==0)){
                pair<int,int> colScore = minimax(s, N, other(color), turn_count + 1);
    
                s.undoMove();
            }
        }
        for(int i = 0; i<collection.size(); i++){
            if(bestScore<collection[i].second){
                bestScore = collection[i].second;
                bestMove = collection[i].first;
            }
        }
        return make_pair(bestMove, bestScore);
    }
    //min
    else{
        int bestScore = -INFINITY;
        int bestMove;
        for(int i = 1; i<s.cols(); i++){
            //if you can make the move, and the game is still not over
            if(s.makeMove(i, color) && (rating(s, N, init_color)==0)){
                pair<int,int> colScore = minimax(s, N, other(color), turn_count + 1);
                s.undoMove();
            }
        }
        for(int i = 0; i<collection.size(); i++){
            if(bestScore>collection[i].second){
                bestScore = collection[i].second;
                bestMove = collection[i].first;
            }
        }
        return make_pair(bestMove, bestScore);
    }
}

//pair<int,int> SmartPlayerImpl::minimax(Scaffold& s, int N, int color, vector<int,int> collection){
//    int score = rating(s, N, init_color);
//    //terminal state
//    if(score!=0){
//        return make_pair(s.undoMove(), score);
//    }
//    //maximizing player
//    if(am_i_max==true){
//        int bestScore = -INFINITY;
//        int bestMove;
//        for(int i = 1; i<s.cols(); i++){
//            if(s.makeMove(i, color)){
//                pair<int,int> colScore = minimax(s, N, other(color), collection);
////                s.undoMove();
//                if(colScore.second>bestScore){
//                    bestScore = score;
//                    bestMove = i;
//                }
//            }
//        }
//        return make_pair(bestMove, bestScore);
//    }
//
//    //min
//    else{
//        int bestScore = -INFINITY;
//        int bestMove;
//        for(int i = 1; i<s.cols(); i++){
//            if(s.makeMove(i, color)){
//                pair<int,int> colScore = minimax(s, N, other(color), collection);
////                s.undoMove();
//                if(colScore.second<bestScore){
//                    bestScore = colScore.second;
//                    bestMove = i;
//                }
//            }
//        }
//        return make_pair(bestMove, bestScore);
//    }
//}

//pair<int,int> SmartPlayerImpl::determineBestMove(Scaffold& s, int N, int color, int turn_count){
//    //ideas: have a useful return type, instead of am_i_max being true or false, make a turn count tracker to keep track of the depth, and then if the turn count is even then you are max, for example
//    vector<int,int> collection;
//    pair<int,int> colScore;
//    for(int i = 1; i<s.cols();i++){
//        if(s.makeMove(i, color)){
//            colScore = minimax(s, N, other(color), collection);
//            s.undoMove();
//        }
//    }
//    return colScore;
//}
   
pair<int,int> SmartPlayerImpl::determineBestMove(Scaffold& s, int N, int color, int turn_count){
    //ideas: have a useful return type, instead of am_i_max being true or false, make a turn count tracker to keep track of the depth, and then if the turn count is even then you are max, for example
//    int bestScore = -INFINITY;
//    int bestMove;
//    for(int i = 1; i<s.cols();i++){
//        if(s.makeMove(i, color)){
//            pair<int,int> colScore = minimax(s, N, other(color), turn_count+1);
//            s.undoMove();
//            if(colScore.second>bestScore){
//                bestScore = colScore.second;
//                bestMove = i;
//            }
//        }
//    }
    return minimax(s, N, color, turn_count);
}
int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //need to make a copy of the scaffold for it to remain const
    Scaffold copy = s;
    am_i_max = true;
    init_color = color;
    return determineBestMove(copy, N, color, 0).first;
//    int move = chooseMoveHelper(copy, N, color, am_i_max);
//    return move;
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
