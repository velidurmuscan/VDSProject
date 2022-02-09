//
// Created by tobias on 29.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

// Reachability initialization test:
TEST(ReachConstructorTest, ConstructorTest) {
    ClassProject::Reachability Test_Reach(2);
    // Check if state variables are created and initialized:
    for (int i = 2; i < 6 ; i++) {
        EXPECT_EQ(Test_Reach.unique_table[i].bdd_id, i);
        EXPECT_EQ(Test_Reach.unique_table[i].low_id, 0);
        EXPECT_EQ(Test_Reach.unique_table[i].high_id, 1);
        EXPECT_EQ(Test_Reach.unique_table[i].top_var, i);
    }
    // Check if only state variables have been created:
    EXPECT_EQ(Test_Reach.unique_table.size(), 6);
    // Check if the only reachable state is the initial state after calling the constructor:
    std::vector<bool> QueryState1 = {false, false};
    std::vector<bool> QueryState2 = {false, true};
    std::vector<bool> QueryState3 = {true, false};
    std::vector<bool> QueryState4 = {true, true};
    EXPECT_EQ(true, Test_Reach.isReachable(QueryState1));
    EXPECT_EQ(false, Test_Reach.isReachable(QueryState2));
    EXPECT_EQ(false, Test_Reach.isReachable(QueryState3));
    EXPECT_EQ(false, Test_Reach.isReachable(QueryState4));
}

// Testing stateSize exception of constructor:
TEST(ReachZeroStatesException, ZeroStatesException) {
    EXPECT_THROW(ClassProject::Reachability Test_Reach1(0), std::runtime_error);
    EXPECT_NO_THROW(ClassProject::Reachability Test_Reach2(1));
    EXPECT_NO_THROW(ClassProject::Reachability Test_Reach3(2));
    EXPECT_NO_THROW(ClassProject::Reachability Test_Reach4(3));
}

// Testing getStates function:
TEST(ReachGetStateTest, GetStateTest){
    ClassProject::Reachability Test_Reach(5);
    std::vector<BDD_ID> Expected_States = {2, 3, 4, 5, 6};
    EXPECT_EQ(Test_Reach.getStates(), Expected_States);
}

// Testing isReachable function:
TEST(ReachIsReachable, IsReachable){
    ClassProject::Reachability Test_Reach(2);
    std::vector<BDD_ID> transitionFunctions = {Test_Reach.neg(2), Test_Reach.neg(3)};
    Test_Reach.setTransitionFunctions(transitionFunctions);
    std::vector<bool> QueryState1 = {false, false};
    std::vector<bool> QueryState2 = {false, true};
    std::vector<bool> QueryState3 = {true, false};
    std::vector<bool> QueryState4 = {true, true};
    EXPECT_EQ(true, Test_Reach.isReachable(QueryState1));
    EXPECT_EQ(false, Test_Reach.isReachable(QueryState2));
    EXPECT_EQ(false, Test_Reach.isReachable(QueryState3));
    EXPECT_EQ(true, Test_Reach.isReachable(QueryState4));
}

// Testing stateSize exception of isReachable function::
TEST(ReachIsReachableStateSize, IsReachableStateSize) {
    ClassProject::Reachability Test_Reach(2);
    EXPECT_THROW(Test_Reach.isReachable({1, 1, 1}), std::runtime_error);
    EXPECT_NO_THROW(Test_Reach.isReachable({1, 1}));
}

// Testing setTransitionFunctions function:
TEST(ReachSetTransitionFunctions, SetTransitionFunctions){
    ClassProject::Reachability Test_Reach(2);
    std::vector<BDD_ID> transitionFunctions = {Test_Reach.neg(2), Test_Reach.neg(3)};
    Test_Reach.setTransitionFunctions(transitionFunctions);
    EXPECT_EQ(Test_Reach.getTransitionFunctions(), transitionFunctions);
}

// Testing stateSize exception of setTransitionFunctions function:
TEST(ReachSetTransitionFunctionsStateSize, SetTransitionFunctionsStateSize) {
    ClassProject::Reachability Test_Reach(2);
    EXPECT_THROW(Test_Reach.setTransitionFunctions({Test_Reach.neg(2),Test_Reach.neg(3),Test_Reach.neg(4)}), std::runtime_error);
    EXPECT_NO_THROW(Test_Reach.setTransitionFunctions({Test_Reach.neg(2),Test_Reach.neg(3)}));
}

// Testing BDD_ID existence exception of setTransitionFunctions function:
TEST(ReachSetTransitionFunctionsInvBDDID, SetTransitionFunctionsInvBDDID) {
    ClassProject::Reachability Test_Reach(2);
    EXPECT_THROW(Test_Reach.setTransitionFunctions({Test_Reach.neg(2), 7}), std::runtime_error); // Last added BDD_ID to unique table would be 6
    EXPECT_NO_THROW(Test_Reach.setTransitionFunctions({Test_Reach.neg(2), Test_Reach.neg(2)}));
}

// Testing setInitState function:
TEST(ReachSetInitState, SetInitState){
    ClassProject::Reachability Test_Reach(2);
    std::vector<bool> InitialState = {true, false};
    Test_Reach.setInitState(InitialState);
    EXPECT_EQ(Test_Reach.getInitStateVector(), InitialState);
}

// Testing stateSize exception of setInitState function:
TEST(ReachSetInitStateStateSize, SetInitStateStateSize) {
    ClassProject::Reachability Test_Reach(2);
    EXPECT_THROW(Test_Reach.setInitState({true, true, true}), std::runtime_error);
    EXPECT_NO_THROW(Test_Reach.setInitState({true, true}));
}

// Testing getNextStates function:
TEST(ReachGetNextStatesTest, GetNextStatesTest){
    ClassProject::Reachability Test_Reach(5);
    std::vector<BDD_ID> Expected_States = {7, 8, 9, 10, 11};
    EXPECT_EQ(Test_Reach.getNextStates(), Expected_States);
}

// Testing getTransitionFunctions function:
TEST(ReachGetTransitionFunctionsTest, GetTransitionFunctionsTest){
    ClassProject::Reachability Test_Reach(5);
    std::vector<BDD_ID> Expected_States = {2, 3, 4, 5, 6};
    EXPECT_EQ(Test_Reach.getTransitionFunctions(), Expected_States);
}

// Testing getInitStateVector function:
TEST(ReachGetInitStateVectorTest, GetInitStateVectorTest){
    ClassProject::Reachability Test_Reach(5);
    std::vector<bool> Expected_States = {false, false, false, false, false};
    EXPECT_EQ(Test_Reach.getInitStateVector(), Expected_States);
}

#endif
