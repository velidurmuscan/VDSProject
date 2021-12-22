#include "Manager.h"
#include <iostream>
#include <string.h>
#include <cstring>  // For strcpy()
#include <vector>
#include <iomanip>

using namespace ClassProject;
//using namespace std;

// Constructor
Manager::Manager() {

    std::cout << "An ROBDD has been initialized\r\n";
    table_line newLine = {.bdd_id=0, .label="VarFalse", .high_id=0, .low_id=0, .top_var=0};
    unique_table.push_back(newLine);
    newLine = {.bdd_id=1, .label="VarTrue", .high_id=1, .low_id=1, .top_var=1};
    unique_table.push_back(newLine);

}

BDD_ID Manager::createVar(const std::string &label) {
    struct table_line newLine;
    newLine.bdd_id = unique_table.size();
    newLine.label = label;
    newLine.high_id = 1;
    newLine.low_id = 0;
    newLine.top_var = unique_table.size();
    unique_table.push_back(newLine);
    return newLine.bdd_id;
}

const BDD_ID& Manager::True() {
    return unique_table[1].bdd_id;
}

const BDD_ID& Manager::False() {
    return unique_table[0].bdd_id;
}

bool Manager::isConstant(BDD_ID f) {
  bool isConstantVar = false;
    if(f == 1 || f == 0){
        isConstantVar = true;
    }
    return isConstantVar;
}

bool Manager::isVariable(BDD_ID x) {
    /*if(x > uniqueTableSize() - 1){
        return false;
    }
    bool isVariableVar = false;
    if(x > 1){
        isVariableVar = true;
    }
    return isVariableVar;*/ return false;
}

BDD_ID Manager::topVar(BDD_ID f) {
//  @TODO: Check again after all functions are ready
    return unique_table[f].top_var;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e) {
    BDD_ID rHigh, rLow;
    //Unique table i already exists in the unique table
    bool Exist = false;
    int ExistingID = 0;
    for(int c = 0 ; c <= unique_table.size() ; c++){
        if(unique_table[c].high_id == t && unique_table[c].low_id == e){
            Exist = true;
            ExistingID = c;
            break;
        }
    }
   if ( i == 1 ){
        return t;
    } else if( i == 0){
        return e;
    } else if( t == 1 && e == 0 ){
        return i;
    } else if( t == e){
        return t;
    } else if( t == 0 && e == 1){
        return !i;
    } else if (Exist){
        return ExistingID;
    } else{
        rHigh = ite(coFactorTrue(i, topVar(i)), coFactorTrue(t, topVar(i)), coFactorTrue(e, topVar(i)));
        rLow = ite(coFactorFalse(i,topVar(i)), coFactorFalse(t,topVar(i)), coFactorFalse(e,topVar(i)));
        if(rHigh == rLow){
            return rHigh;
        } else {
            struct table_line newLine;
            newLine.bdd_id = unique_table.size();
            newLine.high_id = rHigh;
            newLine.low_id = rLow;
            newLine.top_var = topVar(i);
            unique_table.push_back(newLine);
            return newLine.bdd_id;
        }
   }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x = 0) {

    if(x == 0){
        x = topVar(f);
    }
    BDD_ID T,F;
    if (isConstant(f)){
        return f;
    }
    if(topVar(f) == x){
        return unique_table[f].high_id;
    } else {
        T = coFactorTrue(unique_table[f].high_id, x);
        F = coFactorTrue(unique_table[f].low_id, x);
        return  ite(unique_table[f].top_var,T,F);
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x = 0) {
   if(x == 0){
        x = topVar(f);
    }

    BDD_ID T,F;
    if (isConstant(f)){
        return f;
    }
    if(topVar(f) == x){
        return unique_table[f].low_id;
    } else {
        T = coFactorFalse(unique_table[f].high_id, x);
        F = coFactorFalse(unique_table[f].low_id, x);
        return   ite(unique_table[f].top_var,T,F);
    }
}
/*
BDD_ID Manager::coFactorTrue(BDD_ID f) {
//  @TODO: Implement the function !!!
    BDD_ID tmp = 0;
    return tmp;
}

BDD_ID Manager::coFactorFalse(BDD_ID f) {
//  @TODO: Implement the function !!!
    BDD_ID tmp = 0;
    return tmp;
}
*/
BDD_ID Manager::neg(BDD_ID a) {
    return ite(a, 0, 1);
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b) {
    return ite(a, b, 0);
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b) {
    return ite(a,1, b);
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) {
    return ite(a,neg(b),b);
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b) {
    return neg(and2(a,b));
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b) {
    return neg(or2(a,b));
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) {
    return neg(xor2(a,b));
}

std::string Manager::getTopVarName(const BDD_ID &root) {
//  @TODO: Implement the function !!!
    std::string tmp = "Hello";
    return tmp;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
//  @TODO: Implement the function !!!
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
//  @TODO: Implement the function !!!
}

size_t Manager::uniqueTableSize() {
    return unique_table.size();
}

// Print out the unique table in a table format for debug purposes.
void Manager::print_table() {
    const char separator    = ' ';
    const int labelWidth    = 12;
    const int numWidth      = 10;

    std::cout << "\r\nUnique Table:\r\n";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "BDD_ID";
    std::cout << std::left << std::setw(labelWidth) << std::setfill(separator) << "Label";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "High";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "Low";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "TopVar";
    std::cout << std::endl;

    for (int i=0; i<unique_table.size(); i++ ) {
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].bdd_id;
        std::cout << std::left << std::setw(labelWidth) << std::setfill(separator) << unique_table[i].label;
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].high_id;
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].low_id;
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].top_var;
        std::cout << std::endl;
    }
}
