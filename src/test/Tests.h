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
     ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
     ClassProject::BDD_ID NOTa = Test_ROBDD.ite(a,0,1);
     EXPECT_EQ(Test_ROBDD.unique_table[a].high_id, Test_ROBDD.unique_table[NOTa].low_id);
     EXPECT_EQ(Test_ROBDD.unique_table[a].low_id, Test_ROBDD.unique_table[NOTa].high_id);

     ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
     ClassProject::BDD_ID NOTb = Test_ROBDD.ite(b,0,1);
     EXPECT_EQ(Test_ROBDD.unique_table[b].high_id, Test_ROBDD.unique_table[NOTb].low_id);
     EXPECT_EQ(Test_ROBDD.unique_table[b].low_id, Test_ROBDD.unique_table[NOTb].high_id);

     ClassProject::BDD_ID aANDb = Test_ROBDD.and2(a,b);
     ClassProject::BDD_ID NOTaANDb = Test_ROBDD.ite(aANDb,0,1);
     EXPECT_EQ(Test_ROBDD.unique_table[aANDb].high_id, Test_ROBDD.unique_table[NOTaANDb].low_id);
     EXPECT_EQ(Test_ROBDD.unique_table[aANDb].low_id, Test_ROBDD.unique_table[NOTaANDb].high_id);

     EXPECT_EQ(15, Test_ROBDD.ite(1,15,14));
     EXPECT_EQ(14, Test_ROBDD.ite(0,15,14));
     EXPECT_EQ(16, Test_ROBDD.ite(16,1,0));
     EXPECT_EQ(14, Test_ROBDD.ite(16,14,14));

    // @TODO: Check how to create a unique table the same for different functions implementation (negation mainly)


}

//Testing ite not recomputing function
TEST(ROBDDite, iteRecompTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c =Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d =Test_ROBDD.createVar("d");
    Test_ROBDD.and2(a,b);
    Test_ROBDD.or2(c,d);
    Test_ROBDD.and2(a,d);
    Test_ROBDD.and2(a,c);
    EXPECT_EQ(6, Test_ROBDD.ite(a, b, 0));
    EXPECT_EQ(7, Test_ROBDD.ite(c, 1, d));
    EXPECT_EQ(8, Test_ROBDD.ite(a, d, 0));
    EXPECT_EQ(9, Test_ROBDD.ite(a, c, 0));
}

//Testing ite new line function
TEST(ROBDDite, iteNewLineTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c =Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d =Test_ROBDD.createVar("d");
    ClassProject::BDD_ID aORb = Test_ROBDD.or2(a,b);
    ClassProject::BDD_ID cANDd =Test_ROBDD.and2(c,d);
    ClassProject::BDD_ID aORb_AND_cANDd = Test_ROBDD.and2(aORb,cANDd);
    EXPECT_EQ(1, Test_ROBDD.unique_table[6].high_id);
    EXPECT_EQ(b, Test_ROBDD.unique_table[6].low_id);
    EXPECT_EQ(a, Test_ROBDD.unique_table[6].top_var);
    EXPECT_EQ(d, Test_ROBDD.unique_table[7].high_id);
    EXPECT_EQ(0, Test_ROBDD.unique_table[7].low_id);
    EXPECT_EQ(c, Test_ROBDD.unique_table[7].top_var);
    EXPECT_EQ(cANDd, Test_ROBDD.unique_table[8].high_id);
    EXPECT_EQ(0, Test_ROBDD.unique_table[8].low_id);
    EXPECT_EQ(b, Test_ROBDD.unique_table[8].top_var);
    EXPECT_EQ(cANDd, Test_ROBDD.unique_table[8].high_id);
    EXPECT_EQ(0, Test_ROBDD.unique_table[8].low_id);
    EXPECT_EQ(b, Test_ROBDD.unique_table[8].top_var);
    EXPECT_EQ(cANDd, Test_ROBDD.unique_table[9].high_id);
    EXPECT_EQ(8, Test_ROBDD.unique_table[9].low_id);
    EXPECT_EQ(a, Test_ROBDD.unique_table[9].top_var);
}

//Testing neg function
TEST(ROBDD, negFuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID NOTa =Test_ROBDD.neg(a);
    EXPECT_EQ(1, Test_ROBDD.neg(0));
    EXPECT_EQ(0, Test_ROBDD.neg(1));
    EXPECT_EQ(Test_ROBDD.unique_table[a].high_id, Test_ROBDD.unique_table[NOTa].low_id);
    EXPECT_EQ(Test_ROBDD.unique_table[a].low_id, Test_ROBDD.unique_table[NOTa].high_id);
}

//Testing and2 function
TEST(ROBDD, and2FuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aANDb =Test_ROBDD.and2(a,b);
    EXPECT_EQ(0, Test_ROBDD.and2(0,1));
    EXPECT_EQ(0, Test_ROBDD.and2(1,0));
    EXPECT_EQ(0, Test_ROBDD.and2(0,0));
    EXPECT_EQ(1, Test_ROBDD.and2(1,1));
    EXPECT_EQ(Test_ROBDD.unique_table[aANDb].top_var, a);
    EXPECT_EQ(Test_ROBDD.unique_table[aANDb].high_id, b);
    EXPECT_EQ(Test_ROBDD.unique_table[aANDb].low_id, 0);

}

//Testing nand2 function
TEST(ROBDD, nand2FuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aNANDb =Test_ROBDD.nand2(a,b);
    EXPECT_EQ(1, Test_ROBDD.nand2(0,1));
    EXPECT_EQ(1, Test_ROBDD.nand2(1,0));
    EXPECT_EQ(1, Test_ROBDD.nand2(0,0));
    EXPECT_EQ(0, Test_ROBDD.nand2(1,1));
    EXPECT_EQ(Test_ROBDD.unique_table[aNANDb].top_var, a);
    EXPECT_EQ(Test_ROBDD.unique_table[aNANDb].high_id, 0);
    EXPECT_EQ(Test_ROBDD.unique_table[aNANDb].low_id, b);
}

//Testing or2 function
TEST(ROBDD, or2FuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aORb =Test_ROBDD.or2(a,b);
    EXPECT_EQ(1, Test_ROBDD.or2(0,1));
    EXPECT_EQ(1, Test_ROBDD.or2(1,0));
    EXPECT_EQ(0, Test_ROBDD.or2(0,0));
    EXPECT_EQ(1, Test_ROBDD.or2(1,1));
    EXPECT_EQ(Test_ROBDD.unique_table[aORb].top_var, a);
    EXPECT_EQ(Test_ROBDD.unique_table[aORb].high_id, 1);
    EXPECT_EQ(Test_ROBDD.unique_table[aORb].low_id, b);
}

//Testing nor2 function
TEST(ROBDD, nor2FuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aNORb =Test_ROBDD.nor2(a,b);
    EXPECT_EQ(0, Test_ROBDD.nor2(0,1));
    EXPECT_EQ(0, Test_ROBDD.nor2(1,0));
    EXPECT_EQ(1, Test_ROBDD.nor2(0,0));
    EXPECT_EQ(0, Test_ROBDD.nor2(1,1));
    EXPECT_EQ(Test_ROBDD.unique_table[aNORb].top_var, a);
    EXPECT_EQ(Test_ROBDD.unique_table[aNORb].high_id, b);
    EXPECT_EQ(Test_ROBDD.unique_table[aNORb].low_id, 1);
}

//Testing xor2 function
TEST(ROBDD, xor2FuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aXORb =Test_ROBDD.xor2(a,b);
    EXPECT_EQ(1, Test_ROBDD.xor2(0,1));
    EXPECT_EQ(1, Test_ROBDD.xor2(1,0));
    EXPECT_EQ(0, Test_ROBDD.xor2(0,0));
    EXPECT_EQ(0, Test_ROBDD.xor2(1,1));
    EXPECT_EQ(Test_ROBDD.unique_table[aXORb].top_var, a);
    EXPECT_EQ(Test_ROBDD.unique_table[aXORb].high_id, Test_ROBDD.neg(b));
    EXPECT_EQ(Test_ROBDD.unique_table[aXORb].low_id, b);

}

//Testing xnor2 function
TEST(ROBDD, xnor2FuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aXNORb =Test_ROBDD.xnor2(a,b);
    EXPECT_EQ(0, Test_ROBDD.xnor2(0,1));
    EXPECT_EQ(0, Test_ROBDD.xnor2(1,0));
    EXPECT_EQ(1, Test_ROBDD.xnor2(0,0));
    EXPECT_EQ(1, Test_ROBDD.xnor2(1,1));
    EXPECT_EQ(Test_ROBDD.unique_table[aXNORb].top_var, a);
    EXPECT_EQ(Test_ROBDD.unique_table[aXNORb].high_id, b);
    EXPECT_EQ(Test_ROBDD.unique_table[aXNORb].low_id, Test_ROBDD.neg(b));
}

//Testing coFactorTrue function
TEST(ROBDD, coFactorTrueFuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c =Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d =Test_ROBDD.createVar("d");
    ClassProject::BDD_ID aANDb =Test_ROBDD.and2(a,b);
    EXPECT_EQ(b, Test_ROBDD.coFactorTrue(aANDb,a));
    ClassProject::BDD_ID cXORd =Test_ROBDD.xor2(c,d);
    EXPECT_EQ(Test_ROBDD.neg(d), Test_ROBDD.coFactorTrue(cXORd,c));
    ClassProject::BDD_ID cORd =Test_ROBDD.or2(c,d);
    EXPECT_EQ(1, Test_ROBDD.coFactorTrue(cORd));
}

//Testing coFactorFalse function
TEST(ROBDD, coFactorFalseFuncTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c =Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d =Test_ROBDD.createVar("d");
    ClassProject::BDD_ID aANDb =Test_ROBDD.and2(a,b);
    EXPECT_EQ(0, Test_ROBDD.coFactorFalse(aANDb,a));
    ClassProject::BDD_ID cXORd =Test_ROBDD.xor2(c,d);
    EXPECT_EQ(d, Test_ROBDD.coFactorFalse(cXORd,c));
    ClassProject::BDD_ID cORd =Test_ROBDD.or2(c,d);
    EXPECT_EQ(d, Test_ROBDD.coFactorFalse(cORd));

}

//Testing unique table size function
TEST(ROBDD, uniqueTableSizeTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c =Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d =Test_ROBDD.createVar("d");
    ClassProject::BDD_ID aANDb =Test_ROBDD.and2(a,b);
    ClassProject::BDD_ID aORb =Test_ROBDD.or2(a,b);
    ClassProject::BDD_ID aXORb =Test_ROBDD.xor2(a,b);
    EXPECT_EQ(10, Test_ROBDD.uniqueTableSize());
}

//Testing getTopVarName function
TEST(ROBDDTopVarName, getTopVarNameTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c =Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d =Test_ROBDD.createVar("d");
    ClassProject::BDD_ID aANDb =Test_ROBDD.and2(a,b);
    EXPECT_EQ("a", Test_ROBDD.getTopVarName(aANDb));
    ClassProject::BDD_ID bANDc =Test_ROBDD.and2(b,c);
    ClassProject::BDD_ID bANDc_ORd =Test_ROBDD.or2(bANDc,d);
    EXPECT_EQ("b", Test_ROBDD.getTopVarName(bANDc_ORd));
}

//Testing findNodes function
TEST(ROBDDFindNodes, findNodesTest){
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b =Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c =Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d =Test_ROBDD.createVar("d");
    ClassProject::BDD_ID aORb =Test_ROBDD.or2(a,b);
    ClassProject::BDD_ID cANDd =Test_ROBDD.and2(c,d);
    ClassProject::BDD_ID aORb_AND_cANDd =Test_ROBDD.and2(aORb,cANDd);
    std::set<BDD_ID> nodes_of_root, PreDef_nodes_of_root;
    PreDef_nodes_of_root = {0, 1, 3};
    Test_ROBDD.findNodes(d, nodes_of_root);
    EXPECT_EQ(PreDef_nodes_of_root, nodes_of_root);
}


#endif
