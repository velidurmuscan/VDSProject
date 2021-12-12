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
    my_ROBDD.createVar("var_1");
    my_ROBDD.createVar("var_2");
    my_ROBDD.createVar("var_3");
    my_ROBDD.print_table();



    return 0;
}
