#ifndef LIFT_DOORS_STATES_H
#define LIFT_DOORS_STATES_H

#include <iostream>
#include "Lift.hpp"
#include "state_machine.h"

namespace lift {

	SM_STATE(openDoorsAndSetTimer);
	SM_STATE(waitDoorsTimer);

	extern state_machine_t liftDoorsProcessing;
}

#endif
