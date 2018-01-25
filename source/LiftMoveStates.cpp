#include <time.h>
#include "LiftMoveStates.hpp"

#define GET_LIFT\
	Lift *lift = (Lift*)(((ArgumentsForLiftMoveStates*)(argin))->lift);

#define GET_LEVEL\
	size_t level = ((ArgumentsForLiftMoveStates*)(argin))->level;

namespace lift {

	clock_t liftStepTimer;

	SM_CREATE(liftMoveToLevel, SM_FLAG_NONE, setTimerOfMoveStep);

	SM_STATE(setTimerOfMoveStep)
	{
		GET_LIFT;

		liftStepTimer = static_cast<clock_t>(lift->m_moveTimerPeriod) + clock();

		return SM_JUMP(waitTimerAndMove);
	}

	SM_STATE(waitTimerAndMove)
	{
		GET_LIFT;
		GET_LEVEL;

		if(liftStepTimer > clock()) {
			return SM_HOLD;
		}

		if(lift->moveStepToLevel(level)) {
			return SM_RESET;
		}

		return SM_JUMP(setTimerOfMoveStep);
	}

}
