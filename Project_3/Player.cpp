//
//  Player.cpp
//  Project_3
//
//  Created by Noa Lehrer on 5/10/21.
//


#include "provided.h"
#include <string>
#include <iostream>
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
    int determineBestMove(Scaffold& s, int N, int color, bool am_i_max);
    bool am_i_max = true;
//    pair<int,int> last_colScore = make_pair(0, 0);
    pair<int,int> best;

    vector<pair<int,int>> colScore_v;
    
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

int SmartPlayerImpl::determineBestMove(Scaffold& s, int N, int color, bool am_i_max){
    for(int i = 1; i<s.cols(); i++){
        if(s.makeMove(i, color)){
            int score = rating(s, N, color);
            pair<int,int> colScore;
            
            //if the game isn't over
            if(score==0){
                //switch colors
                //wait do i actually need to switch colors...
                determineBestMove(s, N, color, !am_i_max);
            }
            if(score!=0){
                colScore = make_pair(i, score);
                colScore_v.push_back(colScore);
            }
            
            s.undoMove();
        }
    }
        //FIRST IS THE COL, SECOND IS THE SCORE
        
        if(am_i_max==true && !colScore_v.empty()){
            //return the max
            best = colScore_v[0];
            for(int i = 0; i<colScore_v.size(); i++){
                if(best.second<colScore_v[i].second){
                    best.second = colScore_v[i].second;
                    best.first = colScore_v[i].first;
                }
            }
        }
        if(am_i_max==false&& !colScore_v.empty()){
            //return the min
            best = colScore_v[0];
            for(int i = 0; i<colScore_v.size(); i++){
                if(best.second>colScore_v[i].second){
                    best.second = colScore_v[i].second;
                    best.first = colScore_v[i].first;
                }
            }
        }
        
//        //HOW AND WHEN DO I COMPARE THE SCORES
//        if(am_i_max==true){
//            //return the max
//            if(colScore.second > last_colScore.second){
//                last_colScore.first = colScore.first;
//                last_colScore.second = colScore.second;
//            }
//        }
//        if(am_i_max==false){
//            //return the min
//            if(colScore.second < last_colScore.second){
//                last_colScore.first = colScore.first;
//                last_colScore.second = colScore.second;
//            }
//        }
    return best.first;
}
   

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //need to make a copy of the scaffold for it to remain const
    Scaffold copy = s;
    am_i_max = true;
    int move = determineBestMove(copy, N, color, am_i_max);
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
