//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

using namespace ClassProject;

//Constructor
Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {
//Reachability::Reachability(unsigned int stateSize){
//Reachability(unsigned int stateSize){

}

Reachability::~Reachability() {
    ;
}

//const std::vector<BDD_ID> &getStates() const;
const std::vector<BDD_ID> &getStates(){
    const std::vector<BDD_ID> &tempVector = {1,2,3};
    return tempVector;
}

bool Reachability::isReachable(const std::vector<bool> &stateVector){
    return false;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){

}

void Reachability::setInitState(const std::vector<bool> &stateVector){

}