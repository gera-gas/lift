#include <time.h>
#include "LiftDoorsStates.hpp"

#define GET_LIFT\
	Lift *lift = (Lift*)(argin);

namespace lift {

	clock_t liftDoorsTimer;

	SM_CREATE(liftDoorsProcessing, SM_FLAG_NONE, openDoorsAndSetTimer);

	SM_STATE(openDoorsAndSetTimer)
	{
		GET_LIFT;

		liftDoorsTimer = static_cast<clock_t>(lift->m_timeDoorsOpen) + clock();

		return SM_JUMP(waitDoorsTimer);
	}

	SM_STATE(waitDoorsTimer)
	{
		if(liftDoorsTimer > clock()) {
			return SM_HOLD;
		}

		return SM_RESET;
	}

}
