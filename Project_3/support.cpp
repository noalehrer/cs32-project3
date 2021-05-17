//
//  support.cpp
//  Project_3
//
//  Created by Noa Lehrer on 5/11/21.
//

#include "support.h"

int rating(Scaffold& s, int N, int color){
            
    //Example rating table
    //where BIG_NUMBER = 50, for a 4 X 3 scaffold
        
    //                                   TIMING/DEPTH (# empty)
    //                                  early   mid-game  late
    // OUTCOME      EQUATION              12        6       2
    //===================================================================
    // win      BIG_NUMBER + # empty      62       56       52       //earlier wins get a better rating, win is always better than a tie
    // tie      BIG_NUMBER - # empty      38       44       48       //later tie gets a better rating
    // loss   -(BIG_NUMBER + # empty)    -62      -56      -52       //all losses are bad (negative), later ones are slightly better
    
    //if the game is not over
    if(game_over(s,N)==99){
        return 0;
    }
    
    
    //if the game ends, and that player WINS
    if(game_over(s, N)==color){
        //more empty means earlier win, which we want to represent as a higher/better rating
        return BIG_NUMBER + s.numberEmpty();
    }
    //if it's a tie
    if(game_over(s, N)==TIE_GAME){
        //here we want to give later ties a higher rating, so we subtract the number empty
        //this also makes our rating system so that a win is always better that a tie
        return BIG_NUMBER - s.numberEmpty();
    }
    //otherwise, it's a loss for that player
    return -(BIG_NUMBER + s.numberEmpty());
}

int right_diag_down_start_position(const Scaffold& s, int col, int level){
    //given the latest checker's col and level, determine where to start diag checker function
    
    //base case (too far left or down)
    while(col<s.cols() && level>1){
        col++;
        level--;
    }
    return col;
}

int right_diag_down_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count){
    //we are starting at the bottom right of the diagonal, and travelling up and to the left
    //base cases
    //out of bounds to high or too far to the left
    if(level>s.levels() || col>s.cols() || col<1 || level<1){
        return max_count;
    }
    
    if(s.checkerAt(col, level)==color){
        count++;
        if(count>max_count){
            max_count = count;
        }
    }
    
    else if(s.checkerAt(col, level)!=color){
        count = 0; //streak interrupted, set count back to 0
    }
    
    max_count = right_diag_down_streak_helper(s, col-1, level+1, color, count, max_count);
    
    return max_count;
}

bool right_diag_down_win(const Scaffold& s, int col, int level, int color, int n_in_a_row){
    //start at bottom right of the diagonal
    int count = 0, max_count = 0;
    
    int start_col = right_diag_down_start_position(s, col, level);
    
    level = 1;
    
    if(right_diag_down_streak_helper(s, start_col, level, color, count, max_count)<n_in_a_row){
        return false;
    }
    return true;
}


int right_diag_up_start_position(const Scaffold& s, int col, int level){
    //given the latest checker's col and level, determine where to start diag checker function
    
    //base case (too far left or down)
    while(col>1 && level>1){
        col--;
        level--;
    }
    return col;
}

int right_diag_up_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count){
    
    //base case
    //out of bounds, too far right and up
    if(level>s.levels() || col>s.cols() || col<1 || level<1){
        return max_count;
    }
    
    if(s.checkerAt(col, level)==color){
        count++;
        if(count>max_count){
            max_count = count;
        }
    }
    
    else if(s.checkerAt(col, level)!=color){
        count = 0; //streak interrupted, set count back to 0
    }
    
    max_count = right_diag_up_streak_helper(s, col+1, level+1, color, count, max_count);
    
    return max_count;}

bool right_diag_up_win(const Scaffold& s, int col, int level, int color, int n_in_a_row){
    int count = 0, max_count = 0;
    
    int start_col = right_diag_up_start_position(s, col, level);
    
    level = 1;
    
    //we start from the bottom left part of the diag streak
    
    if(right_diag_up_streak_helper(s, start_col, level, color, count, max_count)<n_in_a_row){
        return false;
    }
    return true;
}

int vertical_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count){
    //base case
    //we assume we are starting in the bottom level of the latest column, go up
    if(level>s.levels()){return max_count;}
    
    if(s.checkerAt(col, level)==color){
        count++;
        if(count>max_count){
            max_count = count;
        }
    }
    
    else if(s.checkerAt(col, level)!=color){
        count = 0;
    }
    
    max_count = vertical_streak_helper(s, col, level+1, color, count, max_count);
    return max_count;
}

bool vertical_win(const Scaffold& s, int col, int level, int color, int n_in_a_row){
    int count = 0, max_count = 0;
    
    if(vertical_streak_helper(s, col, level, color, count, max_count)<n_in_a_row){
        return false;
    }
    
    return true;
}

int across_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count){
    //base case
    //we assume we are starting from the first column in the latest level, go right
    if(col>s.cols()){return max_count;}
    
    if(s.checkerAt(col, level)==color){ //looking for a streak of the same color
        count++;
        if(count>max_count){
            max_count = count; //update with the longest current streak
        }
    }
    
    else if(s.checkerAt(col, level)!=color){
        count = 0; //streak interrupted, set count back to 0
    }
    
    max_count = across_streak_helper(s, col+1, level, color, count, max_count);
    return max_count;
}

bool across_win(const Scaffold& s, int col, int level, int color, int n_in_a_row){
    int count = 0, max_count = 0;
    
    if(across_streak_helper(s, col, level, color, count, max_count)<n_in_a_row){
        return false;
    }
    
    return true;
}

int game_over(const Scaffold& s, int n_in_a_row){
    
    Scaffold copy = s; //need to make a copy bc can't modify const s
    int col_of_last_move = copy.undoMove(); //need to convert this from char to human aka unadjust
    col_of_last_move = ((col_of_last_move - 1)/2) + 1;
    //no moves have been made yet
    if(col_of_last_move == 0){
        cerr<<"no one has even gone yet, no one won"<<endl;
        return 99;
    }
    
    //optimization
    //if you need n in a row to win, then at least n checkers must be played by one player, and at least n-1 checkers by the other player
    //this makes for a total of at least 2n-1 checkers on the board needed to win
    //therefore, if the number of emtpy is greater than total number of spaces minus 2n-1 checkers, we know that the game isn't over
    
    int total_spaces = s.cols() * s.levels();
    int min_num_of_checkers = (2*n_in_a_row) - 1;
    
    if(s.numberEmpty()>(total_spaces - min_num_of_checkers)){
//        cerr<<"not enough moves made for a win"<<endl;
        return 99;
    }
    
    
    //DETERMINE COLOR AND LOCATION OF LATEST MOVE
    int color = 99; //random number so it will compile
    int level_of_last_move = 99; //random number so it will compile
    int level = s.levels(); //start by looking at the top row
    
    for(int i = level; i>0; i--){
        if(s.checkerAt(col_of_last_move, i)!=VACANT){
            color = s.checkerAt(col_of_last_move, i);
            level_of_last_move = i;
            break;
        };
    }
//    while(level>0){
//        if(s.checkerAt(col_of_last_move, level)!=VACANT){
//            color = s.checkerAt(col_of_last_move, level);
//            level_of_last_move = level;
//        };
//        level--;
//    }
    
    //WAYS TO WIN
    
    //ACROSS
    if(across_win(s, 1, level_of_last_move, color, n_in_a_row)){
        return color;
    }
    
    //VERTICAL
    if(vertical_win(s, col_of_last_move, 1, color, n_in_a_row)){
        return color;
    }
    
    //RIGHT DIAG UP
    if(right_diag_up_win(s, col_of_last_move, level_of_last_move, color, n_in_a_row)){
        return color;
    }
    
    //RIGHT DIAG DOWN
    if(right_diag_down_win(s, col_of_last_move, level_of_last_move, color, n_in_a_row)){
        return color;
    }
    
    if(s.numberEmpty()==0){
        return TIE_GAME;
    }
    
//    cerr<<"game not over"<<endl;
    return 99;

    //see if it produced a win across or diag or whatever
}
