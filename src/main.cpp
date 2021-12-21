//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

//using namespace std;
//using namespace ClassProject;

int main(int argc, char* argv[])
{
    std::cout << "\r\nHello World !!!\r\n";
    ClassProject::Manager my_ROBDD;
    my_ROBDD.createVar("a");
    my_ROBDD.createVar("b");
    my_ROBDD.createVar("c");
    my_ROBDD.createVar("d");
    my_ROBDD.or2(2,3);
    my_ROBDD.and2(4,5);
    my_ROBDD.and2(6,7);
    my_ROBDD.print_table();
    return 0;
}
