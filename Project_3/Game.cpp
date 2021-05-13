//
//  Game.cpp
//  Project_3
//
//  Created by Noa Lehrer on 5/10/21.
//

#include "provided.h"
#include <iostream>
#include <stack>
using namespace std;
class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private:
    //data members
    Scaffold s;
    int m_N;
    Player* first;
    Player* second;
    Player* my_turn;
    int turn_count = 0;
    int winner = 999;
    
    //member functions
    
    bool up_right_diag_win(int col, int level, int color)const;
    int up_right_diag_helper(int col, int level, int color, int count, int max_count)const;
    
    bool down_right_diag_win(int col, int level, int color)const;
    int down_right_diag_helper(int col, int level, int color, int count, int max_count)const;

};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black):s(nColumns, nLevels), m_N(N), first(red), second(black), my_turn(first)
{
    
}

int GameImpl::down_right_diag_helper(int col, int level, int color, int count, int max_count)const{
    //base case
    //out of bounds
    if(level<1){
        return max_count;
    }
    
    if(col>s.cols()){
        return max_count;
    }
    //looking for a streak of the same color
    if(checkerAt(col, level)==color){
        count++;
        if(count>max_count){
            max_count = count; //update with the longest current streak
        }
    }
    else if(checkerAt(col, level)!=color){
        count = 0; //streak interrupted, reset count
    }
    
    max_count = down_right_diag_helper(col+1, level-1, color, count, max_count);
    return max_count;
}

bool GameImpl::down_right_diag_win(int col, int level, int color)const{
    int count = 0, max_count = 0;
    
    //base case
    //start at upper-right corner: proceed left, then down to level 1
    //out of bounds to the left
    if(col<1){
        return false;
    }
    if(level<1){
        return false;
    }
    //if the diag streak from that spot wasn't long enough, move one to the left
    if(down_right_diag_helper(col, level, color, count, max_count)<m_N){
        //if in bounds
        if(col>1){
            //proceed left
            return down_right_diag_win(col-1, level, color);
        }
        //then proceed down
        return down_right_diag_win(col, level-1, color);
    }
    return true;
}


int GameImpl::up_right_diag_helper(int col, int level, int color, int count, int max_count)const{
    //this can prob be optimized...
    
    //base case
    //out of bounds
    if(level>s.levels()){
        return max_count;
    }
    
    if(col>s.cols()){
        return max_count;
    }
    
    //looking for a streak of the same color
    if(checkerAt(col, level)==color){
        count++;
        if(count>max_count){
            max_count = count; //update with the longest current streak
        }
    }
    else if(checkerAt(col, level)!=color){
        count = 0; //streak interrupted, set count back to 0
    }
    
    max_count = up_right_diag_helper(col+1, level+1, color, count, max_count);
    
    return max_count;
    
}

bool GameImpl::up_right_diag_win(int col, int level, int color)const{
    
    int count = 0, max_count = 0;

    //base case
    //starting at upper-left corner: proceed down to level 1, then to the right
    
    //out of bounds to the right
    if(col>s.cols()){
        return false;
    }
    
    //if the diag streak from that spot wasn't long enough, move one to the right
    if(up_right_diag_helper(col, level, color, count, max_count)<m_N){
        if(level>1){
            return up_right_diag_win(col, level-1, color);

        }
        return up_right_diag_win(col+1, level, color);
    }
    
    //if the streak was long enough, then got m_N in a row across for a win
    if(up_right_diag_helper(col, level, color, count, max_count)>=m_N){
        return true;
    }
    
    cerr<<"shouldn't get to here, uh oh"<<endl;
    
    return true;
}


bool GameImpl::completed(int& winner) const
{
    int game_status = game_over(s, m_N);
    
    //if not enough moves have been made, game_over returns 99
    if(game_status == 99){
        return false;
    }
    //otherwise game_over returns an int (either RED, BLACK, or TIE_GAME)
    winner = game_status;
    
    return true;
}

bool GameImpl::takeTurn()
{
    if(completed(winner))
        return false;
    else{
        int color = 99; //i set it as 99 so there is no warning
        
        if(turn_count%2==0){
            my_turn = first;
            color = RED;
        }

        if(turn_count%2!=0){
            my_turn = second;
            color = BLACK;
        }

//        cout<<my_turn->name();
        
        int move = my_turn->chooseMove(s, m_N, color);
        s.makeMove(move, color);

        turn_count++;
        
        return true;
    }
}

void GameImpl::play()
{
    while(!completed(winner)){
        s.display();
        takeTurn();
    }
    s.display();
    if(winner == RED)
        cerr<<"Red ("<<my_turn->name()<<") won!"<<endl;
    
    if(winner == BLACK)
        cerr<<"Black ("<<my_turn->name()<<") won!"<<endl;
    
    if(winner == TIE_GAME)
        cerr<<"Nobody won, it was a tie!"<<endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return s.checkerAt(c, r);
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
