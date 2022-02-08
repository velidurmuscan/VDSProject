//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

using namespace ClassProject;

//Constructor
Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {
    // Exception std::runtime_error to be thrown if stateSize is zero
    if(stateSize == 0){
        throw std::runtime_error("State size cannot be zero");
    }
    
    //Setting the transition function to identity
    for(int i = 0 ; i < stateSize ; i++){
        transitionFunctions.push_back(Reachability::createVar("s" + std::to_string(i))); 
        InitStateVector.push_back(false);
    }

    //Creating the next state variables s'
    for(int i = 0 ; i < stateSize ; i++){
        NextStates.push_back(Reachability::createVar("s" + std::to_string(i) + "'")); 
    }

    //Adding all state bits to a vector
    for(int i = 0; i < stateSize + 2; i++){
        if(Reachability::isVariable(i)){
            StateBits.push_back(i); 
        }
    }

    //Defining the transition function to its default value as identity function
    Reachability::setTransitionFunctions(transitionFunctions);
    //Defining the initial state to its default value as 0
    Reachability::setInitState(InitStateVector);
}

//Destructor
Reachability::~Reachability() {
    ;
}

const std::vector<BDD_ID>& Reachability::getStates() const{
    return StateBits;
}

bool Reachability::isReachable(const std::vector<bool> &stateVector){
    // Exception std::runtime_error to be thrown if size of input state vector does not match with number of state bits
    if(stateVector.size() != StateBits.size()){
        throw std::runtime_error("The number of state variables inserted doesn't match the number of the state variables allowed");
    }

    //Computing the transition function
    BDD_ID Tau = 1;
    for(int i = 0 ; i < StateBits.size() ; i++){
        Tau = and2(Tau,xnor2(NextStates[i],transitionFunctions[i]));
    }

    //Characteristics function of the initial state computation
    BDD_ID  Cs_0 = 1;
    for(int i = 0 ; i < StateBits.size() ; i++){
        Cs_0 = and2(Cs_0, xnor2(InitStateVector[i] ? 1 : 0, StateBits[i]));
    }

     BDD_ID CRit, CR, imgNext, imgCurrent;
     CRit = Cs_0;

    //Computing set of reachable states
     do{
         //Step 6
         CR = CRit;
         //Step 7
         imgNext = and2(CR, Tau);
         for(int i = StateBits.size() - 1 ; i >= 0 ; i--){
             imgNext = or2(coFactorTrue(imgNext,StateBits[i]), coFactorFalse(imgNext,StateBits[i]));
         }
        //Step 8
         imgCurrent = imgNext;
         for(int i = 0 ; i < StateBits.size(); i++) {
             imgCurrent = and2(imgCurrent,xnor2(StateBits[i], NextStates[i]));
         }
         for(int i = NextStates.size() - 1 ; i >= 0 ; i--){
             imgCurrent = or2(coFactorTrue(imgCurrent,NextStates[i]), coFactorFalse(imgCurrent,NextStates[i]));
         }
         //Step 9
        CRit = or2(CR, imgCurrent);
         //step 10
     } while ( CRit != CR);

    //Step 11
        BDD_ID Reachable = CR;
    for(int i = 0; i < StateBits.size(); i++ ){
        if(stateVector[i] == 0){
            Reachable = Reachability::coFactorFalse(Reachable,StateBits[i]);
        }else{
            Reachable = Reachability::coFactorTrue(Reachable,StateBits[i]);
        }
    }

    return Reachable == 1;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){
    // Exception std::runtime_error to be thrown if size of input transition function vector does not match with number of state bits
    if(transitionFunctions.size() != StateBits.size()){
        throw std::runtime_error("The number of transition functions inserted doesn't match the number of the transition functions allowed");
    }   
    // Exception std::runtime_error to be thrown if BDD_ID given in the input transition function vector is not present in the unique table
    for(const auto& value: transitionFunctions) {
        if(value >= uniqueTableSize()){
           throw std::runtime_error("BDD_ID in the given transition function vector is invalid"); 
        }
    }
    this -> transitionFunctions = transitionFunctions;
}

void Reachability::setInitState(const std::vector<bool> &stateVector){  
    // Exception std::runtime_error to be thrown if size of input state vector does not match with number of state bits
    if(stateVector.size() != StateBits.size()){
        throw std::runtime_error("The number of state variables inserted doesn't match the number of the state variables allowed");
    }
    InitStateVector = stateVector;
}