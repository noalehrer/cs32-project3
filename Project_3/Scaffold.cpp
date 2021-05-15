//
//  Scaffold.cpp
//  Project_3
//
//  Created by Noa Lehrer on 5/10/21.
//

#include "provided.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const; //tells you the number of columns
    int levels() const; //tells you the number of levels
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();

private:
    //data members
    int m_cols, m_levels;
    int level_width, board_height; //tells you the number of chars in each level, column
    vector<vector<char>> board; //contains each level as a vector of chars, contains levels as a vector
    stack<int> moveStack; //keeps track of the column with the latest move
    
    //member functions
    int columnAdjust(int column) const; //given an input of a column number in "human" terms (bottom level is level 1, first col is col 1)
    int levelAdjust(int level) const; //returns the desired location in terms of vector of chars
        
    bool column_isValid(int column) const; //given an input of a location in "human" terms, checks if it is in bounds of number of cols (NOT NUMBER OF CHARS)
    bool level_isValid(int level) const; //given an input of a location in "human" terms, checks if it is in bounds of number of levels
    
    bool inRange(int column, int level) const; //given an input of a location in "human" terms returns if both col and level are valid
    
    bool col_isFull(int column)const;
    
    int lowest_freeLevel(int column)const;


};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels):m_cols(nColumns), m_levels(nLevels)
{
    //0 is not a positive number
    if(m_cols<1||m_levels<1){
        cerr<<"Invalid input for columns and/or levels"<<endl;
        abort();
    }
    
    //scaffolding needs to account for spaces between checkers
    //vector container needs to have enough room for vacant cells and column sides
    level_width= (2 * m_cols) + 1;
    board_height = m_levels+1; //need an additional "level" below level 1 to show joints
    
    //this is the number of levels
    board.resize(board_height);
    
    for(int bi=0; bi<board_height; bi++){
        //this is each level
        board[bi].resize(level_width);
        //the bottom "level" is not a normal level, it should consist of '-' and '+' to represent the joints btwn cols
        if(bi==board_height-1){
            for(int li = 0; li<level_width; li++){
                if(li%2==0){
                    board[bi][li]='+';
                }
                if(li%2!=0){
                    board[bi][li]='-';
                }
            }
        }
        //normal empty level
        else{
            for(int li = 0; li<level_width; li++){
                if(li%2==0){
                    board[bi][li]='|';
                }
                if(li%2!=0){
                    board[bi][li]=' ';
                }
            }
        }
    }
}

int ScaffoldImpl::cols() const
{
    return m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

bool isEmpty(char c)
{
    if(c==' '){
        return true;
    }
    return false;
}

bool isRed(char c)
{
    if(c=='R'){
        return true;
    }
    return false;
}

bool isBlack(char c)
{
    if(c=='B'){
        return true;
    }
    return false;
}

int ScaffoldImpl::numberEmpty() const
{
    int empty_count = 0;
    for(int i = 0; i<levels();i++){
        empty_count += count_if(board[i].begin(),board[i].end(),isEmpty);
    }
    return empty_count;
}

int ScaffoldImpl::columnAdjust(int column) const
{
    return (2*(column - 1)) + 1;
}

int ScaffoldImpl::levelAdjust(int level) const
{
    return (levels() - level );
}

bool ScaffoldImpl::column_isValid(int column) const{
    if(column > cols()|| column<1){
        return false;
    }
    return true;
}

bool ScaffoldImpl::level_isValid(int level) const{
    if(level>levels()|| level<1){
        return false;
    }
    return true;
}

bool ScaffoldImpl::inRange(int column, int level) const{
    return column_isValid(column) && level_isValid(level);
}


int ScaffoldImpl::checkerAt(int column, int level) const
{
    if(!inRange(column, level)){
        cerr<<"Invalid column and/or level"<<endl;
        abort();
    }
    
    int adjusted_column = columnAdjust(column) ;
    int adjusted_level = levelAdjust(level);
    
    char location = board[adjusted_level][adjusted_column];
//    cout<<board[adjusted_level][adjusted_column]<<endl;

    if(isRed(location)){
        return RED;
    }
    if(isBlack(location)){
        return BLACK;
    }

    return VACANT;
}

void ScaffoldImpl::display() const
{
    cout<<endl;
    for(int i = 0; i< board_height; i++){
        for(int j = 0; j<level_width; j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
}

char dropColor(int color){
    if(color==RED){
        return 'R';
    }
    return 'B';
}

bool ScaffoldImpl::col_isFull(int column)const{
    int adjusted_column = columnAdjust(column);
    
    for(int i = board_height-1; i>-1; i--){
        int position = board[i][adjusted_column];
        if(isEmpty(position)){
            return false;
        }
    }
    return true;
}

int ScaffoldImpl::lowest_freeLevel(int column)const{
    int adjusted_column = columnAdjust(column);

    for(int i = board_height-2; i>=0; i--){
        if(isEmpty(board[i][adjusted_column])){
            int low_level = i;
            return low_level;
        }
    }
    cerr<<"Column was full"<<endl;
    return -1;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if(!column_isValid(column)){
        cerr<<column<<" is an invalid column"<<endl;
        return false;
    }
    
    if(col_isFull(column)){
//        cerr<<"Column was full"<<endl;
        return false;
    }
    
    else{
        int adjusted_column = columnAdjust(column);
        int adjusted_lowest_level = lowest_freeLevel(column);
        board[adjusted_lowest_level][adjusted_column] = dropColor(color);
        moveStack.push(adjusted_column);
        return true;
    }
}

int ScaffoldImpl::undoMove()
{
    if(moveStack.empty()){
        return 0;
    }
    int column_latest = moveStack.top();
    for(int i = 0; i<board_height; i++){
        int position = board[i][column_latest];
        if(!isEmpty(position)){
            board[i][column_latest] = ' ';
            moveStack.pop();
            return column_latest;
        }
    }
    return 0;
}


//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}

