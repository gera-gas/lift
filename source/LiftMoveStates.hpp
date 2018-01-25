#ifndef LIFT_MOVE_STATES_H
#define LIFT_MOVE_STATES_H

#include <iostream>
#include "Lift.hpp"
#include "state_machine.h"

namespace lift {

	struct ArgumentsForLiftMoveStates {
	public:
		void *lift;
		size_t level;
	};

	SM_STATE(setTimerOfMoveStep);
	SM_STATE(waitTimerAndMove);

	extern state_machine_t liftMoveToLevel;
}

#endif
