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

//Testing CreateVar function
TEST(ROBDD, CreateVarFunTest){
    ClassProject::Manager Test_ROBDD;
    //100 was chosen arbitrary, and we can use std::rand()
    for(int i = 2; i < 100; i++) {
        Test_ROBDD.createVar("TestLabel");
    }
    for(int i = 2; i < Test_ROBDD.uniqueTableSize(); i++){
        EXPECT_EQ(i, Test_ROBDD.unique_table[i].bdd_id);
        EXPECT_EQ(1, Test_ROBDD.unique_table[i].high_id);
        EXPECT_EQ(0, Test_ROBDD.unique_table[i].low_id);
        EXPECT_EQ(i, Test_ROBDD.unique_table[i].top_var);
    }
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
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c = Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d = Test_ROBDD.createVar("d");
    ClassProject::BDD_ID ORa_b = Test_ROBDD.or2(a,b);
    ClassProject::BDD_ID ANDc_d =  Test_ROBDD.and2(c,d);
    Test_ROBDD.and2(ORa_b,ANDc_d);
    for(int i = 0 ; i < 2 ; i++) {
        EXPECT_TRUE(Test_ROBDD.isConstant(i));
    }
    for(int i = 2 ; i < Test_ROBDD.uniqueTableSize() ; i++) {
        EXPECT_FALSE(Test_ROBDD.isConstant(i));
    }
}

//Testing isVariable function
TEST(ROBDD, isVariableFuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c = Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d = Test_ROBDD.createVar("d");
    ClassProject::BDD_ID ORa_b = Test_ROBDD.or2(a,b);
    ClassProject::BDD_ID ANDc_d =  Test_ROBDD.and2(c,d);
    Test_ROBDD.and2(ORa_b,ANDc_d);
    for(int i = 0 ; i < 2 ; i++) {
        EXPECT_FALSE(Test_ROBDD.isVariable(i));
    }
    for(int i = 2 ; i < Test_ROBDD.uniqueTableSize() ; i++) { //
        EXPECT_TRUE(Test_ROBDD.isVariable(i));
    }
    EXPECT_FALSE(Test_ROBDD.isVariable(Test_ROBDD.uniqueTableSize())); //@TODO: Replace uniqueTableSize with Rand() > size
}

//Testing topVar function
TEST(ROBDD, topVarFuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c = Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d = Test_ROBDD.createVar("d");
    ClassProject::BDD_ID ORa_b = Test_ROBDD.or2(a,b);
    ClassProject::BDD_ID ANDc_d =  Test_ROBDD.and2(c,d);
    Test_ROBDD.and2(ORa_b,ANDc_d);
    for(int i = 0; i < Test_ROBDD.uniqueTableSize(); i++){
        EXPECT_EQ(Test_ROBDD.topVar(i), Test_ROBDD.unique_table[i].top_var);
    }
}

//Testing ite terminal cases function
TEST(ROBDDite, iteTerminalFunTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::Manager Test_ROBDD2;
    /* EXPECT_EQ(15, Test_ROBDD.ite(1,15,14));
     EXPECT_EQ(14, Test_ROBDD.ite(0,15,14));
     EXPECT_EQ(16, Test_ROBDD.ite(16,1,0));
     EXPECT_EQ(14, Test_ROBDD.ite(16,14,14));

     ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
     ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
     ClassProject::BDD_ID c = Test_ROBDD.createVar("c");
     ClassProject::BDD_ID d = Test_ROBDD.createVar("d");
     ClassProject::BDD_ID ORa_b = Test_ROBDD.or2(a,b);
     ClassProject::BDD_ID ANDc_d =  Test_ROBDD.and2(c,d);
     Test_ROBDD.and2(ORa_b,ANDc_d);
     Test_ROBDD.and2(Test_ROBDD.neg(a),Test_ROBDD.neg(b));
     //std::cout << Test_ROBDD.neg(8) << std::endl;
     Test_ROBDD.print_table();
     //EXPECT_EQ(, Test_ROBDD.ite(16,0,1));
     */
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    Test_ROBDD.neg(Test_ROBDD.and2(2,3));
    Test_ROBDD.neg(Test_ROBDD.nand2(2,3));
    Test_ROBDD.neg(Test_ROBDD.or2(2,3));
    Test_ROBDD.neg(Test_ROBDD.nor2(2,3));
    //Test_ROBDD.neg(Test_ROBDD.xor2(2,3));
    //Test_ROBDD.neg(Test_ROBDD.xnor2(2,3));
    Test_ROBDD.print_table();
/*    ClassProject::BDD_ID c = Test_ROBDD2.createVar("c");
    ClassProject::BDD_ID d = Test_ROBDD2.createVar("d");
    Test_ROBDD2.and2(Test_ROBDD2.neg(2),Test_ROBDD2.neg(3));
    Test_ROBDD2.print_table();*/

    // @TODO: Check how to create a unique table the same for different functions implementation (negation mainly)


}

//Testing ite not recomputing function
TEST(ROBDDite, iteRecompTest){
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

//Testing ite new line function
TEST(ROBDDite, iteNewLineTest){
    ClassProject::Manager Test_ROBDD;
    Test_ROBDD.createVar("a");
    Test_ROBDD.createVar("b");
    Test_ROBDD.createVar("c");
    Test_ROBDD.createVar("d");
    Test_ROBDD.or2(2,3);
    Test_ROBDD.and2(4,5);
    Test_ROBDD.and2(6,7);
    EXPECT_EQ(1, Test_ROBDD.unique_table[6].high_id);
    EXPECT_EQ(3, Test_ROBDD.unique_table[6].low_id);
    EXPECT_EQ(2, Test_ROBDD.unique_table[6].top_var);
    EXPECT_EQ(5, Test_ROBDD.unique_table[7].high_id);
    EXPECT_EQ(0, Test_ROBDD.unique_table[7].low_id);
    EXPECT_EQ(4, Test_ROBDD.unique_table[7].top_var);
    EXPECT_EQ(7, Test_ROBDD.unique_table[8].high_id);
    EXPECT_EQ(0, Test_ROBDD.unique_table[8].low_id);
    EXPECT_EQ(3, Test_ROBDD.unique_table[8].top_var);
    EXPECT_EQ(7, Test_ROBDD.unique_table[8].high_id);
    EXPECT_EQ(0, Test_ROBDD.unique_table[8].low_id);
    EXPECT_EQ(3, Test_ROBDD.unique_table[8].top_var);
    EXPECT_EQ(7, Test_ROBDD.unique_table[9].high_id);
    EXPECT_EQ(8, Test_ROBDD.unique_table[9].low_id);
    EXPECT_EQ(2, Test_ROBDD.unique_table[9].top_var);
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
    Test_ROBDD.unique_table[6].top_var = 2;
    Test_ROBDD.createVar("c or d");
    Test_ROBDD.unique_table[7].low_id = 5;
    Test_ROBDD.unique_table[7].high_id = 1;
    Test_ROBDD.unique_table[7].top_var = 4;
    Test_ROBDD.createVar("a and d");
    Test_ROBDD.unique_table[8].low_id = 0;
    Test_ROBDD.unique_table[8].high_id = 5;
    Test_ROBDD.unique_table[8].top_var = 2;
    Test_ROBDD.createVar("a and c");
    Test_ROBDD.unique_table[9].low_id = 0;
    Test_ROBDD.unique_table[9].high_id = 4;
    Test_ROBDD.unique_table[9].top_var = 2;
    EXPECT_EQ(1, Test_ROBDD.coFactorTrue(7,4));
    EXPECT_EQ(1, Test_ROBDD.coFactorTrue(7));
}

//Testing coFactorFalse function
TEST(ROBDD, coFactorFalseFuncTest){
    ClassProject::Manager Test_ROBDD;
    Test_ROBDD.createVar("a");
    Test_ROBDD.createVar("b");
    Test_ROBDD.createVar("c");
    Test_ROBDD.createVar("d");
    Test_ROBDD.createVar("a and b");
    Test_ROBDD.unique_table[6].low_id = 0;
    Test_ROBDD.unique_table[6].high_id = 3;
    Test_ROBDD.unique_table[6].top_var = 2;
    Test_ROBDD.createVar("c or d");
    Test_ROBDD.unique_table[7].low_id = 5;
    Test_ROBDD.unique_table[7].high_id = 1;
    Test_ROBDD.unique_table[7].top_var = 4;
    Test_ROBDD.createVar("a and d");
    Test_ROBDD.unique_table[8].low_id = 0;
    Test_ROBDD.unique_table[8].high_id = 5;
    Test_ROBDD.unique_table[8].top_var = 2;
    Test_ROBDD.createVar("a and c");
    Test_ROBDD.unique_table[9].low_id = 0;
    Test_ROBDD.unique_table[9].high_id = 4;
    Test_ROBDD.unique_table[9].top_var = 2;
    EXPECT_EQ(5, Test_ROBDD.coFactorFalse(7,4));
    EXPECT_EQ(5, Test_ROBDD.coFactorFalse(7));
}

//Testing unique table size function
/*TEST(ROBDD, uniqueTableSizeTest){
    ClassProject::Manager Test_ROBDD;
    Test_ROBDD.createVar("a");
    Test_ROBDD.createVar("b");
    Test_ROBDD.createVar("c");
    Test_ROBDD.createVar("d");
    Test_ROBDD.or2(2,3);
    Test_ROBDD.and2(4,5);
    Test_ROBDD.and2(6,7);
    EXPECT_EQ(10, Test_ROBDD.uniqueTableSize());
}
*/

#endif
