//
//  Player.cpp
//  Project_3
//
//  Created by Noa Lehrer on 5/10/21.
//


#include "provided.h"
#include <string>
#include <iostream>
#include <stack>
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
    int determineBestMove(Scaffold& s, int N, int color);
    int top_move(int color);

    int best_score_red = 0;
    int best_score_black = 0;
    
    int top_move_red = 0;
    int top_move_black = 0;

    int comp_color = 0;
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

int SmartPlayerImpl::determineBestMove(Scaffold& s, int N, int color){
    //need to iterate thru all possible moves, maybe a for loop for each column?
    //or a while loop
    //my make move function will return true if a move was able to be made...
    //maybe i could have a private variable in smartplayer impl to store the rating and best move so far...
    for(int i = 1; i<=s.cols(); i++){
        //if you are able to make the move (ex: col is not full...)
        if(s.makeMove(i, color)){
            int score = rating(s, N, color);
            //if the game isn't over
            if(score==0){
                //call determineBestMove for the OTHER player... aka switch colors
                if(color == RED){
                    top_move_red = i;
                    color = BLACK;
                }
                else if(color==BLACK){
                    top_move_black = i;
                    color = RED;
                }
                determineBestMove(s, N, color);
            }
            //we only want to remember the score if it caused a win or a tie.. aka greater than 0
            if(score>0){
                //might need a diff best_score and best_move for the two diff players...
                if(color==RED){
                    if(best_score_red<score){
                        best_score_red = score;
                        top_move_red = s.undoMove();
                    }
                }
                else if(color==BLACK){
                    if(best_score_black<score){
                        best_score_black = score;
                        top_move_black = s.undoMove();
                    }
                }
            }
        }
    }
    return top_move(color);
}

int SmartPlayerImpl::top_move(int color){
    if(color==BLACK){
        return top_move_black;
    }
    if(color==RED){
        return top_move_red;
    }
    cerr<<"something went wrong in best_move"<<endl;
    return 0;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //need to make a copy of the scaffold for it to remain const
    Scaffold copy = s;
    comp_color = color;
    int move = determineBestMove(copy, N, color);
    //it skips the comp's turn bc it keeps saying that col 2 is the best move,,, maybe i should make a stack
    return move;
    //functions that i have to work with        parameters needed
    //=============================================================================
    //rating                                    Scaffold& s, int N, int color
        //returns 0 if the game is not yet over!!!
    //game_over                                 const Scaffold& s, int n_in_a_row
        //returns 99 if game is not over
        //if game is over, returns game outcome
            //RED win, BLACK win, or TIE_GAME
    
        
    //determineBestMove()                   int color (to see what best move for that color is)
    //                                      Scaffold& s (to eventually call game_over and rating, also to make hypothetical moves)
    //                                      int n_in_a_row (rating and game_over both need this info)

    //when would i compare rating... in choose move, in determine best move, or in a diff helper fxn????
    //this function is supposed to return TWO NUMBERS: one int to indicate col of best move, one int for the rating
    
    //pseudocode
    //when it is smart players's turn to move (when choose move has been called)
    //determine best move will iterate thru all possible moves that the smart player can make
    //for each "possible" move (ex: col is not full, game is not over)
        //make the move, updating scaffold appropriately
        //use rating function to rate the resulting scaffold
            //if rating function indicates that the computer won, or there was a tie, REMBMER THE RESULT OF THE MOVE/STORE IN A COLLECTION FOR LATER
            //otherwise, call determine best move for the other player, and get its return value, and record the result of the best move function
        //undo the trial move
    
    //determine best move will choose the best move (the one that ended in the best rating)
    //return col of move that should be made, and its ratingrating
    return 0;
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
