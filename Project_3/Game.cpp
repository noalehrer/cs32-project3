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

};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black):s(nColumns, nLevels), m_N(N), first(red), second(black), my_turn(first)
{
    //make sure N for connect_N makes sense
    
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
        if(move==-1){
            return false;
        }
        s.makeMove(move, color);

        turn_count++;
        
        return true;
    }
}

void GameImpl::play()
{
    while(!completed(winner)){
        if(first->isInteractive()==false && second->isInteractive()==false){
            if(turn_count>1 && turn_count%2==0){
                cout<<"press enter to continue";
                cin.ignore(100,'\n');
            }
        }
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
