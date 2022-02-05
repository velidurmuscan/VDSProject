//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"

namespace ClassProject {

    class Reachability : public ReachabilityInterface {

    public:
        // ReachabilityInterface() = delete;
        // virtual ~ReachabilityInterface() = default;

        std::vector<BDD_ID> StateBits;
        std::vector<BDD_ID> transitionFunctions;
        std::vector<bool> InitStateVector;

        Reachability(unsigned int stateSize);

        ~Reachability();

        // Putting const after a function declaration makes the function constant,
        // meaning it cannot alter anything in the object that contains the function.
        const std::vector<BDD_ID> &getStates() const;

        bool isReachable(const std::vector<bool> &stateVector);

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions);

        void setInitState(const std::vector<bool> &stateVector);
    };
}
#endif
