//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include <iostream>
#include "Reachability.h"

using namespace ClassProject;

//Constructor
Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {
    // Exception std::runtime_error to be thrown if stateSize is zero:
    if(stateSize == 0){
        throw std::runtime_error("stateSize cannot be zero !!!");
    }
    
    // Initially, set the transition function (delta) of all state variables to identity:
    // Initially, set the states to 0 (initial state):
    for(int i = 0 ; i < stateSize ; i++){
        transitionFunctions.push_back(Reachability::createVar("s" + std::to_string(i))); 
        InitStateVector.push_back(false);
    }

    // Initially, set the next states (s') of all state variables to identity:
    for(int i = 0 ; i < stateSize ; i++){
        NextStates.push_back(Reachability::createVar("s" + std::to_string(i) + "'")); 
    }

    // Keep all state variables in a vector:
    for(int i = 0; i < stateSize + 2; i++){
        if(Reachability::isVariable(i)){
            StateBits.push_back(i); 
        }
    }

    /*
    // Initially, set the transition function (delta) of all state variables to identity:
    Reachability::setTransitionFunctions(transitionFunctions);
    // Initially, set the states to 0 (initial state):
    Reachability::setInitState(InitStateVector);
    */
}

// Destructor:
Reachability::~Reachability() {
    ;
}

const std::vector<BDD_ID> &Reachability::getStates() const{
    return StateBits;
}

bool Reachability::isReachable(const std::vector<bool> &stateVector){
    // Exception std::runtime_error to be thrown if the size of stateVector does not match with number of state bits:
    if(stateVector.size() != StateBits.size()){
        throw std::runtime_error("The size of stateVector does not match with number of state bits !!!");
    }

    // Compute the transition function:
    BDD_ID Tau = 1;
    for(int i = 0 ; i < StateBits.size() ; i++){
        Tau = and2(Tau,xnor2(NextStates[i],transitionFunctions[i]));
    }

    // Compute the characteristics function of the initial state:
    BDD_ID  Cs_0 = 1;
    for(int i = 0 ; i < StateBits.size() ; i++){
        Cs_0 = and2(Cs_0, xnor2(InitStateVector[i] ? 1 : 0, StateBits[i]));
    }

    // Compute the set of reachable states:
    BDD_ID CRit, CR, imgNext, imgCurrent;
    CRit = Cs_0;
    do{
        // Step 6:
        CR = CRit;
        // Step 7:
        imgNext = and2(CR, Tau);
        for(int i = StateBits.size() - 1 ; i >= 0 ; i--){
            imgNext = or2(coFactorTrue(imgNext,StateBits[i]), coFactorFalse(imgNext,StateBits[i]));
        }
        // Step 8:
        imgCurrent = imgNext;
        for(int i = 0 ; i < StateBits.size(); i++) {
            imgCurrent = and2(imgCurrent,xnor2(StateBits[i], NextStates[i]));
        }
        for(int i = NextStates.size() - 1 ; i >= 0 ; i--){
            imgCurrent = or2(coFactorTrue(imgCurrent,NextStates[i]), coFactorFalse(imgCurrent,NextStates[i]));
        }
        // Step 9:
        CRit = or2(CR, imgCurrent);
        // Step 10:
    } while ( CRit != CR);

    // Step 11:
    BDD_ID Reachable = CR;
    for(int i = 0; i < StateBits.size(); i++ ){
        if(stateVector[i] == 0)
            Reachable = Reachability::coFactorFalse(Reachable,StateBits[i]);
        else
            Reachable = Reachability::coFactorTrue(Reachable,StateBits[i]);
    }
    return Reachable == 1;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){
    // Exception std::runtime_error to be thrown if the size of transitionFunctions does not match with number of state bits:
    if(transitionFunctions.size() != StateBits.size()){
        throw std::runtime_error("The size of transitionFunctions does not match with number of state bits !!!");
    }   
    // Exception std::runtime_error to be thrown if BDD_ID given in the transitionFunctions vector is not present in the unique table:
    for(const auto& value: transitionFunctions) {
        if(value >= uniqueTableSize()){
           throw std::runtime_error("BDD_ID in the given transitionFunctions does not exist !!!");
        }
    }
    this -> transitionFunctions = transitionFunctions;
}

void Reachability::setInitState(const std::vector<bool> &stateVector){  
    // Exception std::runtime_error to be thrown if the size of stateVector does not match with number of state bits:
    if(stateVector.size() != StateBits.size()){
        throw std::runtime_error("The size of stateVector does not match with number of state bits !!!");
    }
    InitStateVector = stateVector;
}

const std::vector<BDD_ID> &Reachability::getNextStates() const{
    return NextStates;
}

const std::vector<BDD_ID> &Reachability::getTransitionFunctions() const{
    return transitionFunctions;
}

const std::vector<bool> &Reachability::getInitStateVector() const{
    return InitStateVector;
}