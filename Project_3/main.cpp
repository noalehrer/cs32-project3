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
    
    //test cases
    //3 x 5, 5
    
    //4 x 4, 3
    
    //5 x 3, 2
    
    //5 x 2, 5
    
    //6 x 2, 3
    
    //10 x 2, 2
    
    //10 x 1, 4
    
    //computer vs. computer
    
    //computer first

    HumanPlayer noa("Noa");
    SmartPlayer shanthi("Shanthi");
    BadPlayer molly("Molly");
    Game g1(4,3,3, &shanthi, &noa);
//    Game g1(4, 3, 3, &noa, &shanthi);
//    Game g1(3, 2, 3, &noa, &shanthi);
//    Game g1(3,2,3, &noa, &shanthi);
//    Game g1(2,2,2, &noa, &shanthi);
//    Game g1(10, 2, 3, &noa, &shanthi);
//    Game g1(3,5,5, &molly, &shanthi);
//    Game g2(4,4,3, &molly, &shanthi);
//    Game g3(5,3,2, &molly, &shanthi);
//    Game g4(5,2,5, &molly, &shanthi);
//    Game g5(6,2,3, &molly, &shanthi);
//    Game g6(10,2,2, &molly, &shanthi);
//    Game g7(10,1,4, &molly, &shanthi);
//
//    Game g1(3,5,5, &shanthi, &molly);
//    Game g2(4,4,3,&shanthi, &molly);
//    Game g3(5,3,2,&shanthi, &molly);
//    Game g4(5,2,5,&shanthi, &molly);;
//    Game g5(6,2,3,&shanthi, &molly);
//    Game g6(10,2,2,&shanthi, &molly);
//    Game g7(10,1,4, &shanthi, &molly);

    cout<<endl;
    g1.play();
//    cout<<endl;
//    g2.play();
//    cout<<endl;
//    g3.play();
//    cout<<endl;
//    g4.play();
//    cout<<endl;
//    g5.play();
//    cout<<endl;
//    g6.play();
//    cout<<endl;
//    g7.play();
//    cout<<endl;
    cerr<<"Passed all tests"<<endl;




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
