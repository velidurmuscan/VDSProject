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

//Testing topVar function
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

//Testing ite terminal cases function
TEST(ROBDD, iteTerminalFunTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(15, Test_ROBDD.ite(1,15,14));
    EXPECT_EQ(14, Test_ROBDD.ite(0,15,14));
    EXPECT_EQ(16, Test_ROBDD.ite(16,1,0));
    EXPECT_EQ(14, Test_ROBDD.ite(16,14,14) );
}

//Testing ite not recomputing function
TEST(ROBDD, iteRecompTest){
    ClassProject::Manager Test_ROBDD;
    Test_ROBDD.createVar("a");
    Test_ROBDD.createVar("b");
    Test_ROBDD.createVar("c");
    Test_ROBDD.createVar("d");
    // @TODO: Use and,or, ...etc functions
    Test_ROBDD.createVar("a and b");
    Test_ROBDD.unique_table[6].low_id = 0;
    Test_ROBDD.unique_table[6].high_id = 3;
    Test_ROBDD.createVar("c or d");
    Test_ROBDD.unique_table[7].low_id = 5;
    Test_ROBDD.unique_table[7].high_id = 1;
    Test_ROBDD.createVar("a and d");
    Test_ROBDD.unique_table[8].low_id = 0;
    Test_ROBDD.unique_table[8].high_id = 5;
    Test_ROBDD.createVar("a and c");
    Test_ROBDD.unique_table[9].low_id = 0;
    Test_ROBDD.unique_table[9].high_id = 4;
    EXPECT_EQ(7, Test_ROBDD.ite(4, 1, 5));
}

//Testing neg function
TEST(ROBDD, negFuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(1, Test_ROBDD.neg(0));
    EXPECT_EQ(0, Test_ROBDD.neg(1));
}

//Testing and2 function
TEST(ROBDD, and2FuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(0, Test_ROBDD.and2(0,1));
    EXPECT_EQ(0, Test_ROBDD.and2(1,0));
    EXPECT_EQ(0, Test_ROBDD.and2(0,0));
    EXPECT_EQ(1, Test_ROBDD.and2(1,1));
}

//Testing nand2 function
TEST(ROBDD, nand2FuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(1, Test_ROBDD.nand2(0,1));
    EXPECT_EQ(1, Test_ROBDD.nand2(1,0));
    EXPECT_EQ(1, Test_ROBDD.nand2(0,0));
    EXPECT_EQ(0, Test_ROBDD.nand2(1,1));
}

//Testing or2 function
TEST(ROBDD, or2FuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(1, Test_ROBDD.or2(0,1));
    EXPECT_EQ(1, Test_ROBDD.or2(1,0));
    EXPECT_EQ(0, Test_ROBDD.or2(0,0));
    EXPECT_EQ(1, Test_ROBDD.or2(1,1));
}

//Testing nor2 function
TEST(ROBDD, nor2FuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(0, Test_ROBDD.nor2(0,1));
    EXPECT_EQ(0, Test_ROBDD.nor2(1,0));
    EXPECT_EQ(1, Test_ROBDD.nor2(0,0));
    EXPECT_EQ(0, Test_ROBDD.nor2(1,1));
}

//Testing xor2 function
TEST(ROBDD, xor2FuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(1, Test_ROBDD.xor2(0,1));
    EXPECT_EQ(1, Test_ROBDD.xor2(1,0));
    EXPECT_EQ(0, Test_ROBDD.xor2(0,0));
    EXPECT_EQ(0, Test_ROBDD.xor2(1,1));
}

//Testing xnor2 function
TEST(ROBDD, xnor2FuncTest){
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(0, Test_ROBDD.xnor2(0,1));
    EXPECT_EQ(0, Test_ROBDD.xnor2(1,0));
    EXPECT_EQ(1, Test_ROBDD.xnor2(0,0));
    EXPECT_EQ(1, Test_ROBDD.xnor2(1,1));
}

//Testing coFactorTrue function
TEST(ROBDD, coFactorTrueFuncTest){
    ClassProject::Manager Test_ROBDD;
    Test_ROBDD.createVar("a");
    Test_ROBDD.createVar("b");
    Test_ROBDD.createVar("c");
    Test_ROBDD.createVar("d");
    Test_ROBDD.createVar("a and b");
    Test_ROBDD.unique_table[6].low_id = 0;
    Test_ROBDD.unique_table[6].high_id = 3;
    Test_ROBDD.createVar("c or d");
    Test_ROBDD.unique_table[7].low_id = 5;
    Test_ROBDD.unique_table[7].high_id = 1;
    Test_ROBDD.createVar("a and d");
    Test_ROBDD.unique_table[8].low_id = 0;
    Test_ROBDD.unique_table[8].high_id = 5;
    Test_ROBDD.createVar("a and c");
    Test_ROBDD.unique_table[9].low_id = 0;
    Test_ROBDD.unique_table[9].high_id = 4;
    EXPECT_EQ(5, Test_ROBDD.coFactorTrue(7,4));
    EXPECT_EQ(5, Test_ROBDD.coFactorTrue(7));
}


#endif
