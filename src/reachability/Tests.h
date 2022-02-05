//
// Created by tobias on 29.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

//Reachability state machine constructor initialization test  
TEST(ReachConstructorTest, ConstructorTest) {
    ClassProject::Reachability Test_Reach(2);
    //Check if state variables are created and initialized
    for (int i = 2; i < 6 ; i++) {
        EXPECT_EQ(Test_Reach.unique_table[i].bdd_id, i);
        EXPECT_EQ(Test_Reach.unique_table[i].low_id, 0);
        EXPECT_EQ(Test_Reach.unique_table[i].high_id, 1);
        EXPECT_EQ(Test_Reach.unique_table[i].top_var, i);
    }
    //Check if only state variables have been created 
    EXPECT_EQ(Test_Reach.unique_table.size(),6);
    //Check if, after calling the constructor, the only reachable state is the initial state.
    std::vector<bool> QueryState1 = {false,false};
    std::vector<bool> QueryState2 = {false,true};
    std::vector<bool> QueryState3 = {true,false};
    std::vector<bool> QueryState4 = {true,true};
    EXPECT_EQ(true,Test_Reach.isReachable(QueryState1));
    EXPECT_EQ(false,Test_Reach.isReachable(QueryState2));
    EXPECT_EQ(false,Test_Reach.isReachable(QueryState3));
    EXPECT_EQ(false,Test_Reach.isReachable(QueryState4));
}

//Check if the exception std::runtime_error tis thrown if input stateSize to constructor is zero
TEST(ReachZeroStatesException, ZeroStatesException) {
    EXPECT_THROW(ClassProject::Reachability Test_Reach1(0), std::runtime_error);
    EXPECT_NO_THROW(ClassProject::Reachability Test_Reach2(1));
    EXPECT_NO_THROW(ClassProject::Reachability Test_Reach3(2));
    EXPECT_NO_THROW(ClassProject::Reachability Test_Reach4(3));
}

//Testing the getStates function
TEST(ReachGetStateTest, GetStateTest){
    ClassProject::Reachability Test_Reach(5);
    std::vector<BDD_ID> StateVariables = Test_Reach.getStates();
    std::vector<BDD_ID> Expected_States = {2,3,4,5,6};
    EXPECT_EQ(Test_Reach.getStates(), Expected_States);
}

//Testing the isReachable function
TEST(ReachIsReachable, IsReachable){
    ClassProject::Reachability Test_Reach(2);
    std::vector<BDD_ID> transitionFunctions = {Test_Reach.neg(2),Test_Reach.neg(3)};
    Test_Reach.setTransitionFunctions(transitionFunctions);
    std::vector<bool> QueryState1 = {false,false};
    std::vector<bool> QueryState2 = {false,true};
    std::vector<bool> QueryState3 = {true,false};
    std::vector<bool> QueryState4 = {true,true};
    EXPECT_EQ(true,Test_Reach.isReachable(QueryState1));
    EXPECT_EQ(false,Test_Reach.isReachable(QueryState2));
    EXPECT_EQ(false,Test_Reach.isReachable(QueryState3));
    EXPECT_EQ(true,Test_Reach.isReachable(QueryState4));
}

//Check if the exception std::runtime_error tis thrown if size of input state vector does not match with number of state bits
TEST(ReachIsReachableStateSize, IsReachableStateSize) {
    ClassProject::Reachability Test_Reach(2);
    EXPECT_THROW(Test_Reach.isReachable({1,1,1}), std::runtime_error);
    EXPECT_NO_THROW(Test_Reach.isReachable({1,1}));
}

//Testing the setTransitionFunctions function
TEST(ReachSetTransitionFunctions, SetTransitionFunctions){
    ClassProject::Reachability Test_Reach(2);
    std::vector<BDD_ID> transitionFunctions = {Test_Reach.neg(2),Test_Reach.neg(3)};
    Test_Reach.setTransitionFunctions(transitionFunctions);
    EXPECT_EQ(Test_Reach.transitionFunctions,transitionFunctions);
}

//Check if the exception std::runtime_error is thrown if size of input transition function vector does not match with number of state bits
TEST(ReachSetTransitionFunctionsStateSize, SetTransitionFunctionsStateSize) {
    ClassProject::Reachability Test_Reach(2);
    EXPECT_THROW(Test_Reach.setTransitionFunctions({Test_Reach.neg(2),Test_Reach.neg(3),Test_Reach.neg(4)}), std::runtime_error);
    EXPECT_NO_THROW(Test_Reach.setTransitionFunctions({Test_Reach.neg(2),Test_Reach.neg(3)}));
}

//Testing the setInitState function
TEST(ReachSetInitState, SetInitState){
    ClassProject::Reachability Test_Reach(2);
    std::vector<bool> InitialState = {true,false};
    Test_Reach.setInitState(InitialState);
    EXPECT_EQ(Test_Reach.InitStateVector,InitialState);
}

//Check if the exception std::runtime_error is thrown if size of input state vector does not match with number of state bits
TEST(ReachSetInitStateStateSize, SetInitStateStateSize) {
    ClassProject::Reachability Test_Reach(2);
    EXPECT_THROW(Test_Reach.setInitState({true,true,true}), std::runtime_error);
    EXPECT_NO_THROW(Test_Reach.setInitState({true,true}));
}

#endif
