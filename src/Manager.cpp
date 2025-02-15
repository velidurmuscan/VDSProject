#include "Manager.h"
#include <iostream>
#include <string.h>
#include <cstring>  // For strcpy()
#include <vector>
#include <iomanip>

//#define include_labels 1

using namespace ClassProject;
//using namespace std;

// Constructor
Manager::Manager() {
    //std::cout << "An ROBDD has been initialized\r\n";
    table_line newLine = {.bdd_id=0, .label="VarFalse", .high_id=0, .low_id=0, .top_var=0};
    unique_table.push_back(newLine);
    newLine = {.bdd_id=1, .label="VarTrue", .high_id=1, .low_id=1, .top_var=1};
    unique_table.push_back(newLine);

    inverse_unique_table.insert({{0, 0, 0}, 0});
    inverse_unique_table.insert({{1, 1, 1}, 1});
}

BDD_ID Manager::createVar(const std::string &label) {
    struct table_line newLine;
    newLine.bdd_id = unique_table.size();
    newLine.label = label;
    newLine.high_id = 1;
    newLine.low_id = 0;
    newLine.top_var = unique_table.size();
    unique_table.push_back(newLine);
    inverse_unique_table.insert({{newLine.low_id, newLine.high_id, newLine.top_var}, newLine.bdd_id});
    return newLine.bdd_id;
}

const BDD_ID &Manager::True() {
    return unique_table[1].bdd_id;
}

const BDD_ID &Manager::False() {
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
    if(x > 1 && unique_table[x].high_id == 1 && unique_table[x].low_id == 0 ){
        isVariableVar = true;
    }
/*
    if(x > 1){
        isVariableVar = true;
    }
*/
    return isVariableVar;
}

BDD_ID Manager::topVar(BDD_ID f) {
    return unique_table[f].top_var;
}

// If-Then-Else algorithm taken from slides:
BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    BDD_ID rHigh, rLow, minTopVar;
    // 1) Check if ite() results in a terminal case:
    if (i == 1){                    //ite(1,t,e)
        return t;
    } else if(i == 0){              //ite(0,t,e)
        return e;
    } else if(t == 1 && e == 0){    //ite(i,1,0)
        return i;
    } else if(t == e){              //ite(i,t,t)
        return t;
    }
/*
    else if( t == 0 && e == 1){   //ite(i,0,1) = Negation
        // Check if the negation of the unique table entry i already exists in the unique table:
        for(int c = 0 ; c <= uniqueTableSize() ; c++){
            if ((unique_table[c].high_id == unique_table[i].low_id) && (unique_table[c].low_id == unique_table[i].high_id)) {
                // Negation of i already exists, do not add it to table.
                return unique_table[c].bdd_id;
            }
        }
        // If not, create the negation of entry i:
        struct table_line newLine;
        newLine.bdd_id = uniqueTableSize();
        newLine.high_id = unique_table[i].low_id;
        newLine.low_id = unique_table[i].high_id;
        newLine.top_var = unique_table[i].top_var;
        newLine.label = "!" +  unique_table[i].label;    // Negation label
        unique_table.push_back(newLine);
        return newLine.bdd_id;
    }
*/

/*
    // 2) Check if unique table entry i already exists in the unique table:
    for(int c = 0 ; c <= uniqueTableSize() ; c++){
        if(unique_table[c].high_id == t && unique_table[c].low_id == e){
            return unique_table[c].bdd_id;
        }
    }
*/

    // 2) Check if "Computed Table" entry 'i' already exists in the "Computed Table":
    // Check I, T and E in the "Computed Table", if we already have an entry, BDD_ID is returned:
    // I + T + E --> BDD_ID
    ct_input ct_inst = {i,t,e};
    //std::unordered_map<ct_input,BDD_ID>::const_iut_iterator ct_iter = computed_table.find(ct_inst);
    auto ct_iter = computed_table.find(ct_inst);
    if ( !(ct_iter == computed_table.end()) )
        return ct_iter->second;
/*
    key ct_inst = {i,t,e};
    std::unordered_map<key,BDD_ID>::const_iut_iterator ct_iter = computed_table.find (ct_inst);
    if ( !(ct_iter == computed_table.end()) )
        return ct_iter->second;
*/

    // 3) Create a new entry for i,t,e:
    // 3.1) Find the lowest top variable:
    if((t == 0 || t == 1) && (e == 0 || e == 1)){
        minTopVar = topVar(i);
    } else if(t == 0 || t == 1 ){
        minTopVar = std::min(topVar(i), topVar(e));
    } else if( e == 0 || e == 1) {
        minTopVar = std::min(topVar(i), topVar(t));
    } else {
        minTopVar = std::min(std::min(topVar(i), topVar(t)), topVar(e));
    }
    // 3.2) In order to add a new entry into unique table, calculate the high and low successors of the new entry:
    //rHigh = ite(coFactorTrue(i, minTopVar), coFactorTrue(t, minTopVar), coFactorTrue(e, minTopVar));
    ClassProject::BDD_ID ct_i = coFactorTrue(i,minTopVar);
    ClassProject::BDD_ID ct_t = coFactorTrue(t,minTopVar);
    ClassProject::BDD_ID ct_e = coFactorTrue(e,minTopVar);
    rHigh = ite(ct_i, ct_t, ct_e);  // High Successor
    computed_table.insert({{ct_i,ct_t,ct_e},rHigh});
    //rLow = ite(coFactorFalse(i,minTopVar), coFactorFalse(t,minTopVar), coFactorFalse(e,minTopVar));
    ClassProject::BDD_ID cf_i = coFactorFalse(i,minTopVar);
    ClassProject::BDD_ID cf_t = coFactorFalse(t,minTopVar);
    ClassProject::BDD_ID cf_e = coFactorFalse(e,minTopVar);
    rLow = ite(cf_i, cf_t, cf_e);   // Low Successor
    computed_table.insert({{cf_i,cf_t,cf_e},rLow});

    // 3.3) Check if reduction is possible:
    if(rHigh == rLow){
        // Both high and low successors are same. Thus, creation of a new node is unnecessary. Return the current node:
        return rHigh;
    }

/*
    // 3.4) Check if unique table entry i already exists in the unique table:
    for(int c = 0 ; c < uniqueTableSize() ; c++){
        if(unique_table[c].high_id == rHigh && unique_table[c].low_id == rLow && unique_table[c].top_var == minTopVar ){
            return unique_table[c].bdd_id;
        }
    }
*/

    // 3.4) Check if "Inverse Unique Table" entry 'i' already exists in the "Inverse Unique Table":
    // "Inverse Unique Table" should be checked here instead of the original unique table checking algorithm:
    // LOW + HIGH + TOP --> BDD_ID
    iut_input iut_inst = {rLow, rHigh, minTopVar};
    // std::unordered_map<iut_input,BDD_ID>::const_iut_iterator iut_iter = inverse_unique_table.find(iut_inst);
    auto iut_iter = inverse_unique_table.find(iut_inst);
    if ( !(iut_iter == inverse_unique_table.end()) )
        return iut_iter->second;
/*
    key iut_inst = {rLow, rHigh, minTopVar};
     std::unordered_map<key,BDD_ID>::const_iut_iterator iut_iter = inverse_unique_table.find (iut_inst);
     if ( !(iut_iter == inverse_unique_table.end()) )
         return iut_iter->second;
*/

    // 3.5) Create and add a new entry to the unique table:
    struct table_line newLine;
    newLine.bdd_id = uniqueTableSize();
    newLine.high_id = rHigh;
    newLine.low_id = rLow;
    newLine.top_var = minTopVar;
    // newLine.label = "TempLabel";
    // newLine.label = "!" +  unique_table[i].label;
    unique_table.push_back(newLine);
    /*********************/
    // computed_table_t computed_table{{{i,t,e},newLine.bdd_id}};
    computed_table.insert({{i, t, e}, newLine.bdd_id});
    inverse_unique_table.insert({{rLow, rHigh, minTopVar}, newLine.bdd_id});
    /********************/
    //computed_table[i,t,e] = newLine.bdd_id;
    return newLine.bdd_id;
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x) {
    // Check if this is a terminal case:
    // @TODO: Check if we really cover checking all terminal cases.
    if(isConstant(f) || isConstant(x) || topVar(f) > x){
        return f;
    }
    BDD_ID T,F;
    // Check if x is already the top variable of f:
    if(topVar(f) == x){
        return unique_table[f].high_id;
    } else {
        // Calculate ite() with respect to variable x:
        T = coFactorTrue(unique_table[f].high_id, x);
        F = coFactorTrue(unique_table[f].low_id, x);
        return  ite(unique_table[f].top_var,T,F);
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x) {
    // Check if this is a terminal case:
    // @TODO: Check if we really cover checking all terminal cases.
    if(isConstant(f) || isConstant(x) || topVar(f) > x){
        return f;
    }
    BDD_ID T,F;
    // Check if x is already the top variable of f:
    if(topVar(f) == x){
        return unique_table[f].low_id;
    } else {
        // Calculate ite() with respect to variable x:
        T = coFactorFalse(unique_table[f].high_id, x);
        F = coFactorFalse(unique_table[f].low_id, x);
        return   ite(unique_table[f].top_var,T,F);
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f) {
    return coFactorTrue(f, topVar(f));
}

BDD_ID Manager::coFactorFalse(BDD_ID f) {
    return coFactorFalse(f, topVar(f));
}

BDD_ID Manager::neg(BDD_ID a) {
    BDD_ID neg_ID;
    neg_ID = ite(a, 0, 1);
    // Negation label is added inside ite() function
    #ifdef include_labels
        std::string label = unique_table[neg_ID].label;
        if (label.front() == '!') {
            unique_table[neg_ID].label = label.substr(2,label.size()-3);
        }
        else {
            unique_table[neg_ID].label = "!(" + unique_table[a].label + ")";
        }

        //unique_table[neg_ID].label = "!(" + unique_table[a].label + ")";
    #endif
    return neg_ID;
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b) {
    BDD_ID and2_ID;
    and2_ID = ite(a, b, 0);
    #ifdef include_labels
        if(!(a < 2 || b < 2))
            unique_table[and2_ID].label = "(" + unique_table[a].label + "*" + unique_table[b].label + ")";
    #endif
    return and2_ID;
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b) {
    BDD_ID or2_ID;
    or2_ID = ite(a, 1, b);
    #ifdef include_labels
        if(!(a < 2 || b < 2))
            unique_table[or2_ID].label = "(" + unique_table[a].label + "+" + unique_table[b].label + ")";
    #endif
    return or2_ID;
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) {
    BDD_ID xor2_ID, neg_b;
    neg_b = neg(b);
    xor2_ID = ite(a,neg_b,b);
    #ifdef include_labels
        if(!(a < 2 || b < 2))
            unique_table[xor2_ID].label = "(" + unique_table[a].label + "(+)" + unique_table[b].label + ")";
    #endif
    return xor2_ID;
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b) {
    BDD_ID nand2_ID;
    nand2_ID = neg(and2(a,b));
    #ifdef include_labels
        if(!(a < 2 || b < 2))
            unique_table[nand2_ID].label = "!(" + unique_table[a].label + "*" + unique_table[b].label + ")";
    #endif
    return nand2_ID;
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b) {
    BDD_ID nor2_ID;
    nor2_ID = neg(or2(a,b));
    #ifdef include_labels
        if(!(a < 2 || b < 2))
        unique_table[nor2_ID].label = "!(" + unique_table[a].label + "+" + unique_table[b].label + ")";
    #endif
    return nor2_ID;
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) {
    BDD_ID xnor2_ID;
    xnor2_ID = neg(xor2(a,b));
    #ifdef include_labels
        if(!(a < 2 || b < 2))
            unique_table[xnor2_ID].label = "!(" + unique_table[a].label + "(+)" + unique_table[b].label + ")";
    #endif
    return xnor2_ID;
}

std::string Manager::getTopVarName(const BDD_ID &root) {
    return unique_table[topVar(root)].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    if(unique_table[root].bdd_id < 2 ){
        return;
    }
    nodes_of_root.insert(unique_table[root].high_id);
    nodes_of_root.insert(unique_table[root].low_id);
    nodes_of_root.insert(unique_table[root].bdd_id);
    findNodes(unique_table[root].high_id, nodes_of_root);
    findNodes(unique_table[root].low_id, nodes_of_root);
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
    std::set<BDD_ID> nodes_of_root;
    findNodes(root, nodes_of_root);
    std::set<BDD_ID>::iterator iter = nodes_of_root.begin();
    for(int i = 0; i < nodes_of_root.size(); i++) {
        if(!(topVar(*iter) == 1 || topVar(*iter) == 0)) {
            vars_of_root.insert(topVar(*iter));
        }
        iter++;
    }
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
