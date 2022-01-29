//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"
#include <iostream>

namespace ClassProject {

    class Reachability : public ReachabilityInterface {

    public:
        // ReachabilityInterface() = delete;
        // virtual ~ReachabilityInterface() = default;

        Reachability(unsigned int stateSize);

        ~Reachability();

        // const std::vector<BDD_ID> &getStates() const;
        const std::vector<BDD_ID> &getStates();

        bool isReachable(const std::vector<bool> &stateVector);

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions);

        void setInitState(const std::vector<bool> &stateVector);
    };
}
#endif
