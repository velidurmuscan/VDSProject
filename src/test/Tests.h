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

/*
TEST(Test1,Subttest_1){

    ASSERT_TRUE(1 == 1);
}

TEST(Test1,Subttest_2){

    ASSERT_TRUE(1 == 1);
}*/
#endif
