//
//  main.cpp
//  Project_3
//
//  Created by Noa Lehrer on 5/10/21.
//

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    HumanPlayer noa("Noa");
    SmartPlayer shanthi("Shanthi");
//    BadPlayer molly("Molly");
//    Game g1(4, 3, 3, &noa, &shanthi);
    Game g1(3, 2, 2, &noa, &shanthi);

    cout<<endl;
    g1.play();
}

//#include "provided.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doGameTests()
//{
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Game g(2, 2, 2, &bp1, &bp2);
//    int winner;
//    assert(!g.completed(winner));
//    g.takeTurn();  // Red's first move
//    assert(!g.completed(winner)  &&
//                (g.checkerAt(1, 1) == RED  ||  g.checkerAt(2, 1) == RED));
//    g.takeTurn();  // Black's first move
//    assert(!g.completed(winner));
//    g.takeTurn();  // Red's second move; Red must win
//    assert(g.completed(winner)  &&  winner == RED);
//}
//
//int main()
//{
//    doGameTests();
//    cout << "Passed all tests" << endl;
//}
