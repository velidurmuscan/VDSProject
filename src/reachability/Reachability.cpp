//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

using namespace ClassProject;
//using namespace std;

//Constructor
Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {

    for(int i = 0 ; i < stateSize ; i++){
        transitionFunctions.push_back(Reachability::createVar("s" + std::to_string(i))); //Setting the transition function to identity
        InitStateVector.push_back(false);
    }
    //Defining the transition function to its default value as identity function
    Reachability::setTransitionFunctions(transitionFunctions);
    //Defining the initial state to its default value as 0
    Reachability::setInitState(InitStateVector);
    //@TODO: Hence, after calling the constructor, the only reachable state should be the initial state.

    for(int i = 0; i < Reachability::uniqueTableSize(); i++){
        if(Reachability::isVariable(i)){
            StateBits.push_back(i);
        }
    }
}

Reachability::~Reachability() {
    ;
}

const std::vector<BDD_ID>& Reachability::getStates() const{
    return StateBits;
}

bool Reachability::isReachable(const std::vector<bool> &stateVector){

    
    return false;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){
    this -> transitionFunctions = transitionFunctions;
}

void Reachability::setInitState(const std::vector<bool> &stateVector){
    InitStateVector = stateVector;
}