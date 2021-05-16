//
//  support.hpp
//  Project_3
//
//  Created by Noa Lehrer on 5/11/21.
//

#ifndef support_hpp
#define support_hpp

#include "provided.h"
#include <iostream>
using namespace std;

const int BIG_NUMBER = 50;
const int INFINITY = 1000;

class Scaffold;

int game_over(const Scaffold& s, int n_in_a_row);

int rating(Scaffold& s, int N, int color);

//ACROSS
bool across_win(const Scaffold& s, int col, int level, int color, int n_in_a_row);
int across_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count);

//VERTICAL
bool vertical_win(const Scaffold& s, int col, int level, int color, int n_in_a_row);
int vertical_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count);

//RIGHT DIAG UP
bool right_diag_up_win(const Scaffold& s, int col, int level, int color, int n_in_a_row);
int right_diag_up_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count);
int right_diag_up_start_position(const Scaffold& s, int col, int level);

//RIGHT DIAG DOWN
bool right_diag_down_win(const Scaffold& s, int col, int level, int color, int n_in_a_row);
int right_diag_down_streak_helper(const Scaffold& s, int col, int level, int color, int count, int max_count);
int right_diag_down_start_position(const Scaffold& s, int col, int level);

#endif /* support_hpp */
