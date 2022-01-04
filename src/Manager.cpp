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

    //std::cout << "An ROBDD has been initialized\r\n";
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
    if(x > uniqueTableSize() - 1){
        return false;
    }
    bool isVariableVar = false;
    if(x > 1){
        isVariableVar = true;
    }
    return isVariableVar;
}

BDD_ID Manager::topVar(BDD_ID f) {
    return unique_table[f].top_var;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    BDD_ID rHigh, rLow, minTopVar;
    //Unique table entry i already exists in the unique table:
    bool Exist = false;
    BDD_ID ExistingID = 0;
    for(int c = 0 ; c <= uniqueTableSize() ; c++){
        if(unique_table[c].high_id == t && unique_table[c].low_id == e){
            Exist = true;
            ExistingID = c;
            break;
        }
    }


    //Check if the unique table has an entry for i,t,e:
    if (Exist) {
        return ExistingID;
    }


    //Check if ite is a terminal case:
    else if ( i == 1 ){                       //ite(1,t,e)
        return t;
    } else if( i == 0){
        return e;                       //ite(0,t,e)
    } else if( t == 1 && e == 0 ){      //ite(i,1,0)
        return i;
    } else if( t == e){                 //ite(i,t,t)
        return t;
    } else if( t == 0 && e == 1){       //ite(i,0,1) = Negation
        struct table_line newLine;
        newLine.bdd_id = uniqueTableSize();
        newLine.high_id = unique_table[i].low_id;
        newLine.low_id = unique_table[i].high_id;
        newLine.top_var = unique_table[i].top_var;
        newLine.label = "!(" +  unique_table[i].label + ")";    // Negation label
        unique_table.push_back(newLine);
        return newLine.bdd_id;
    }

    /*
    //Check if the unique table has an entry for i,t,e:
    else if (Exist) {
        return ExistingID;
    }
    */

    //Create a new entry for i,t,e:
    else{
        //Find the lowest top variable
        if((t == 0 || t == 1) && (e == 0 || e == 1)){
            minTopVar = topVar(i);
        } else if(t == 0 || t == 1 ){
            minTopVar = std::min(topVar(i), topVar(e));
        } else if( e == 0 || e == 1) {
            minTopVar = std::min(topVar(i), topVar(t));
        } else {
            minTopVar = std::min(std::min(topVar(i), topVar(t)), topVar(e));
        }

        ClassProject::BDD_ID ct_i = coFactorTrue(i,minTopVar);
        ClassProject::BDD_ID ct_t = coFactorTrue(t,minTopVar);
        ClassProject::BDD_ID ct_e = coFactorTrue(e,minTopVar);
        rHigh = ite(ct_i, ct_t, ct_e);
        //rHigh = ite(coFactorTrue(i, minTopVar), coFactorTrue(t, minTopVar), coFactorTrue(e, minTopVar));

        ClassProject::BDD_ID cf_i = coFactorFalse(i,minTopVar);
        ClassProject::BDD_ID cf_t = coFactorFalse(t,minTopVar);
        ClassProject::BDD_ID cf_e = coFactorFalse(e,minTopVar);
        rLow = ite(cf_i, cf_t, cf_e);
        //rLow = ite(coFactorFalse(i,minTopVar), coFactorFalse(t,minTopVar), coFactorFalse(e,minTopVar));

        if(rHigh == rLow){
            return rHigh;
        } else {
            struct table_line newLine;
            newLine.bdd_id = uniqueTableSize();
            newLine.high_id = rHigh;
            newLine.low_id = rLow;
            newLine.top_var = minTopVar;
            newLine.label = "TestLabel";
            unique_table.push_back(newLine);
            return newLine.bdd_id;
        }
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x = 0) {

    if(x == 0){
        x = topVar(f);
    }
    if (isConstant(f)){
        return f;
    }
    BDD_ID T,F;
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
    if (isConstant(f)){
        return f;
    }
    BDD_ID T,F;
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
    // Negation label is added inside ite() function
    return ite(a, 0, 1);
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b) {
    BDD_ID and2_ID;
    and2_ID = ite(a, b, 0);
    unique_table[and2_ID].label = "(" +  unique_table[a].label + "*" + unique_table[b].label + ")";
    return and2_ID;
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b) {
    BDD_ID or2_ID;
    or2_ID = ite(a, 1, b);
    unique_table[or2_ID].label = "(" +  unique_table[a].label + "+" + unique_table[b].label + ")";
    return or2_ID;
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) {
    BDD_ID xor2_ID, neg_b;
    neg_b = neg(b);
    xor2_ID = ite(a,neg_b,b);
    unique_table[xor2_ID].label = "(" +  unique_table[a].label + "(+)" + unique_table[b].label + ")";
    return xor2_ID;
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b) {
    BDD_ID nand2_ID;
    nand2_ID = neg(and2(a,b));
    unique_table[nand2_ID].label = "(" +  unique_table[a].label + "!*" + unique_table[b].label + ")";
    return nand2_ID;
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b) {
    BDD_ID nor2_ID;
    nor2_ID = neg(or2(a,b));
    unique_table[nor2_ID].label = "(" +  unique_table[a].label + "!+" + unique_table[b].label + ")";
    return nor2_ID;
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) {
    BDD_ID xnor2_ID;
    xnor2_ID = neg(xor2(a,b));
    unique_table[xnor2_ID].label = "(" +  unique_table[a].label + "!(+)" + unique_table[b].label + ")";
    return xnor2_ID;
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
    const int labelWidth    = 20;
    const int numWidth      = 10;

    std::cout << "\r\nUnique Table:\r\n";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "BDD_ID";
    std::cout << std::left << std::setw(labelWidth) << std::setfill(separator) << "Label";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "High";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "Low";
    std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << "TopVar";
    std::cout << std::endl;

    for (int i=0; i<uniqueTableSize(); i++ ) {
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].bdd_id;
        std::cout << std::left << std::setw(labelWidth) << std::setfill(separator) << unique_table[i].label;
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].high_id;
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].low_id;
        std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << unique_table[i].top_var;
        std::cout << std::endl;
    }
}
