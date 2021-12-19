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
    my_ROBDD.createVar("a and b");
    my_ROBDD.unique_table[6].low_id = 0;
    my_ROBDD.unique_table[6].high_id = 3;
    my_ROBDD.createVar("c or d");
    my_ROBDD.unique_table[7].low_id = 5;
    my_ROBDD.unique_table[7].high_id = 1;
    my_ROBDD.print_table();
    std::cout << my_ROBDD.ite(2, 3, 0) << std::endl;



    return 0;
}
