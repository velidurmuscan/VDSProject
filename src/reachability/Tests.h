//
// Created by tobias on 29.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

TEST(ReachConstTest, ConstTest) {
    ClassProject::Reachability Test_Reach(5);
    for (int i = 2; i < 7 ; i++) {
        EXPECT_EQ(Test_Reach.unique_table[i].bdd_id, i);
        EXPECT_EQ(Test_Reach.unique_table[i].low_id, 0);
        EXPECT_EQ(Test_Reach.unique_table[i].high_id, 1);
        EXPECT_EQ(Test_Reach.unique_table[i].top_var, i);
    }
    EXPECT_EQ(Test_Reach.unique_table.size(),7);
}

TEST(ReachgetStateTest, getStateTest){
    ClassProject::Reachability Test_Reach(5);
    std::vector<BDD_ID> StateVariables = Test_Reach.getStates();
    std::vector<BDD_ID> Expected_States = {2,3,4,5,6};
    EXPECT_EQ(Test_Reach.getStates(), Expected_States);
}

TEST(ReachsetInitState, setInitState){
    ClassProject::Reachability Test_Reach(2);
    std::vector<bool> InitialState = {true,false};
    Test_Reach.setInitState(InitialState);
    EXPECT_EQ(Test_Reach.InitStateVector,InitialState);
}

TEST(ReachsetTransitionFunctions, setTransitionFunctions){
    ClassProject::Reachability Test_Reach(2);
    std::vector<BDD_ID> transitionFunctions = {Test_Reach.neg(2),Test_Reach.neg(3)};
    Test_Reach.setTransitionFunctions(transitionFunctions);
    EXPECT_EQ(Test_Reach.transitionFunctions,transitionFunctions);
    Test_Reach.print_table();
}

TEST(ReachisReachable, isReachable){
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

    Test_Reach.print_table();
}

#endif
