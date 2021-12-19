//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "gtest/gtest.h"
#include "../Manager.cpp"



//ROBDD initialization test
TEST(ROBDD, ConstructorTest){
    ClassProject::Manager Test_ROBDD;
    //Check if the false node is in the correct position
    EXPECT_EQ(0,Test_ROBDD.unique_table[0].bdd_id);
    //EXPECT_EQ("VarFalse",Test_ROBDD.unique_table[0].label);
    EXPECT_EQ(0,Test_ROBDD.unique_table[0].top_var);
    EXPECT_EQ(0,Test_ROBDD.unique_table[0].high_id);
    EXPECT_EQ(0,Test_ROBDD.unique_table[0].low_id);
    //Check if the true node is in the correct position
    EXPECT_EQ(1,Test_ROBDD.unique_table[1].bdd_id);
    //EXPECT_EQ("VarTrue",Test_ROBDD.unique_table[1].label);
    EXPECT_EQ(1,Test_ROBDD.unique_table[1].top_var);
    EXPECT_EQ(1,Test_ROBDD.unique_table[1].high_id);
    EXPECT_EQ(1,Test_ROBDD.unique_table[1].low_id);
    //Check the size of the unique table if 2
    EXPECT_EQ(2,Test_ROBDD.unique_table.size());
}
//Testing True function
TEST(ROBDD,TrueFuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(1,Test_ROBDD.True());
}

//Testing False function
TEST(ROBDD,FalseFuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(0,Test_ROBDD.False());
}

//Testing isConstant function
TEST(ROBDD, isConstantFuncTest){
    ClassProject::Manager Test_ROBDD;
    // @TODO: Further implementation by checking the unique table in isConstant function
    for(int i = 0 ; i < 2 ; i++) {
        EXPECT_TRUE(Test_ROBDD.isConstant(i));
    }
    for(int i = 2 ; i < 100 ; i++) { // @TODO: Change the 100 later with the size of the ROBDD
        EXPECT_FALSE(Test_ROBDD.isConstant(i));
    }
}

//Testing isVariable function
TEST(ROBDD, isVariableFuncTest){
    ClassProject::Manager Test_ROBDD;
    // @TODO: Further implementation by checking the unique table in isVariable function
    for(int i = 0 ; i < 2 ; i++) {
        EXPECT_FALSE(Test_ROBDD.isVariable(i));
    }
    for(int i = 2 ; i < 100 ; i++) { // @TODO: Change the 100 later with the size of the ROBDD
        EXPECT_TRUE(Test_ROBDD.isVariable(i));
    }
}

//Testing isVariable function
TEST(ROBDD, topVarFuncTest){
    ClassProject::Manager Test_ROBDD;
    for(int i = 0; i < Test_ROBDD.unique_table.size(); i++){
        EXPECT_EQ(Test_ROBDD.topVar(i), Test_ROBDD.unique_table[i].top_var);
    }
}

//Testing CreateVar function
TEST(ROBDD, CreateVarFunTest){
    ClassProject::Manager Test_ROBDD;
    BDD_ID TempID;
    for(int i = 2; i < 100; i++){
        TempID = Test_ROBDD.createVar("TestLabel");
        EXPECT_EQ(TempID, Test_ROBDD.unique_table[i].bdd_id);
        EXPECT_EQ(1, Test_ROBDD.unique_table[i].high_id);
        EXPECT_EQ(0, Test_ROBDD.unique_table[i].low_id);
        EXPECT_EQ(TempID, Test_ROBDD.unique_table[i].top_var);
    }

}

//Testing CreateVar function
TEST(ROBDD, ITETerminalFunTest){
    ClassProject::Manager Test_ROBDD;

    EXPECT_EQ(15, Test_ROBDD.ite(1,15,14));
    EXPECT_EQ(14, Test_ROBDD.ite(0,15,14));
    EXPECT_EQ(16, Test_ROBDD.ite(16,1,0));
    EXPECT_EQ(14, Test_ROBDD.ite(16,14,14) );

}
#endif
