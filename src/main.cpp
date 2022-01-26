//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"
#include <unordered_map>

//using namespace std;
//using namespace ClassProject;

int main(int argc, char* argv[])
{
    ClassProject::Manager my_ROBDD;
    ClassProject::BDD_ID a = my_ROBDD.createVar("a");
    ClassProject::BDD_ID b = my_ROBDD.createVar("b");
    ClassProject::BDD_ID c = my_ROBDD.createVar("c");
    ClassProject::BDD_ID d = my_ROBDD.createVar("d");
    ClassProject::BDD_ID ORa_b = my_ROBDD.or2(a,b);
    ClassProject::BDD_ID ANDc_d =  my_ROBDD.and2(c,d);
    my_ROBDD.and2(ORa_b,ANDc_d);
    my_ROBDD.print_table();
   /* for (auto &kv : my_ROBDD.mapping) {
        std::cout << "I:" << kv.first
             << " T:" << kv.first
                << " E:" << kv.first
             << " BDD_ID:" << kv.second << std::endl;
    }*/

/*
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");

    Test_ROBDD.neg(Test_ROBDD.and2(2,3));
    std::cout << std::endl << "After neg(and2):";
    Test_ROBDD.print_table();

    Test_ROBDD.neg(Test_ROBDD.nand2(2,3));
    std::cout << std::endl << "After neg(nand2):";
    Test_ROBDD.print_table();

    Test_ROBDD.neg(Test_ROBDD.or2(2,3));
    std::cout << std::endl << "After neg(or2):";
    Test_ROBDD.print_table();

    Test_ROBDD.neg(Test_ROBDD.nor2(2,3));
    std::cout << std::endl << "After neg(nor2):";
    Test_ROBDD.print_table();

    Test_ROBDD.neg(Test_ROBDD.xor2(2,3));
    std::cout << std::endl << "After neg(xor2):";
    Test_ROBDD.print_table();

    Test_ROBDD.neg(Test_ROBDD.xnor2(2,3));
    std::cout << std::endl << "After neg(xnor2):";
    Test_ROBDD.print_table();
*/
    return EXIT_SUCCESS;;
}
