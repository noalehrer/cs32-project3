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
    BadPlayer molly("Molly");
    Game g1(4, 3, 3, &noa, &shanthi);
//    Game g1(3, 2, 3, &noa, &shanthi);
//    Game g1(3,2,3, &noa, &shanthi);
//    Game g1(2,2,2, &noa, &shanthi);

    cout<<endl;
    g1.play();
}
//void doPlayerTests()
//    {
//        HumanPlayer hp("Marge");
//        assert(hp.name() == "Marge"  &&  hp.isInteractive());
//        BadPlayer bp("Homer");
//        assert(bp.name() == "Homer"  &&  !bp.isInteractive());
//        SmartPlayer sp("Lisa");
//        assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
//        Scaffold s(3, 2);
//        s.makeMove(1, RED);
//        s.makeMove(1, BLACK);
//        cout << "=========" << endl;
//        int n = hp.chooseMove(s, 3, RED);
//        cout << "=========" << endl;
//        assert(n == 2  ||  n == 3);
//        n = bp.chooseMove(s, 3, RED);
//        assert(n == 2  ||  n == 3);
//        n = sp.chooseMove(s, 3, RED);
//        assert(n == 2  ||  n == 3);
//    }
//
//    int main()
//    {
//        doPlayerTests();
//        cout << "Passed all tests" << endl;
//    }
//#include "provided.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doGameTests()
//{
//    BadPlayer bp1("Bart");
//    SmartPlayer sp2("Homer");
//    Game g(2, 2, 2, &bp1, &sp2);
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
