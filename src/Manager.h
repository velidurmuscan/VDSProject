// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>   // vector type
#include <iomanip>  // setw() and setfill()
#include <unordered_map>
#include <boost/functional/hash.hpp>

namespace ClassProject {

    struct table_line {
        BDD_ID bdd_id;
        std::string label;// = "Default";
        BDD_ID high_id;
        BDD_ID low_id;
        BDD_ID top_var;
    };

    // Input struct for "Computed Table" hashing:
    struct ct_input {
        BDD_ID I;
        BDD_ID T;
        BDD_ID E;
        // Equality operator:
        bool operator == (const ct_input &other) const {
            return (I == other.I) && (T == other.T) && (E == other.E);
        }
    };

    // Input struct for "Inverse Unique Table" hashing:
    struct iut_input {
        BDD_ID Low;
        BDD_ID High;
        BDD_ID TopVar;
        // Equality operator:
        bool operator == (const iut_input &other) const {
            return (Low == other.Low) && (High == other.High) && (TopVar == other.TopVar);
        }
    };

    // Hash function for "Computed Table":
    struct hash_func_ct {
        std::size_t operator () (const ct_input &line) const {
            std::size_t seed = 0;
/*
            boost::hash_combine(seed, boost::hash_value(line.I));
            boost::hash_combine(seed, boost::hash_value(line.T));
            boost::hash_combine(seed, boost::hash_value(line.E));
*/
            boost::hash_combine(seed, std::hash<BDD_ID>{}(line.I));
            boost::hash_combine(seed, std::hash<BDD_ID>{}(line.T));
            boost::hash_combine(seed, std::hash<BDD_ID>{}(line.E));
            return seed;
        }
    };

    // Hash function for "Inverse Unique Table":
    struct hash_func_iut {
        std::size_t operator () (const iut_input &line) const {
            std::size_t seed = 0;
/*
            boost::hash_combine(seed, boost::hash_value(line.Low));
            boost::hash_combine(seed, boost::hash_value(line.High));
            boost::hash_combine(seed, boost::hash_value(line.TopVar));
*/
            boost::hash_combine(seed, std::hash<BDD_ID>{}(line.Low));
            boost::hash_combine(seed, std::hash<BDD_ID>{}(line.High));
            boost::hash_combine(seed, std::hash<BDD_ID>{}(line.TopVar));
            return seed;
        }
    };

   typedef std::tuple<BDD_ID, BDD_ID, BDD_ID> key;

    class Manager : public ManagerInterface {

    public:

        std::vector<table_line> unique_table;
        //std::unordered_map<key, BDD_ID, boost::hash<key>> computed_table;
        //std::unordered_map<key, BDD_ID, boost::hash<key>> inverse_unique_table;
        typedef std::unordered_map<ct_input, BDD_ID, hash_func_ct> computed_table_t;
        computed_table_t computed_table;

        typedef std::unordered_map<iut_input, BDD_ID, hash_func_iut> inverse_unique_table_t;
        inverse_unique_table_t inverse_unique_table;

        // Constructor:
        Manager();

        BDD_ID createVar(const std::string &label);

        const BDD_ID &True();

        const BDD_ID &False();

        bool isConstant(BDD_ID f);

        bool isVariable(BDD_ID x);

        BDD_ID topVar(BDD_ID f);

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);

        BDD_ID coFactorTrue(BDD_ID f);

        BDD_ID coFactorFalse(BDD_ID f);

        BDD_ID neg(BDD_ID a);

        BDD_ID and2(BDD_ID a, BDD_ID b);

        BDD_ID or2(BDD_ID a, BDD_ID b);

        BDD_ID xor2(BDD_ID a, BDD_ID b);

        BDD_ID nand2(BDD_ID a, BDD_ID b);

        BDD_ID nor2(BDD_ID a, BDD_ID b);

        BDD_ID xnor2(BDD_ID a, BDD_ID b);

        std::string getTopVarName(const BDD_ID &root);

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

        size_t uniqueTableSize();

        void print_table();
    };
}

#endif
