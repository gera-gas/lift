#ifndef LIFT_H
#define LIFT_H

#include <iostream>
#include "state_machine.h"
#include "ApplicationHelpers.h"
#include "LiftMoveStates.hpp"
#include "LiftDoorsStates.hpp"

namespace lift {

	class Lift {
	public:
		Lift(size_t numberOfLevels, size_t levelHeight, size_t liftMoveSpeed, size_t timeDoorsOpen);

		enum DefaultParameters {
			kLevelsMin = 5,
			kLevelsMax = 20,
			kLevelHeight = 3,
			kLiftMoveSpeedMin = 1,
			kLiftMoveSpeedMax = 10,
			kLiftMoveSpeedDefault = 2,
			kTimeDoorsOpen = 5
		};

		size_t getCurrentLevel() const;
		bool moveStepToLevel(size_t destination);

	private:
		size_t m_numberOfLevels;
		size_t m_levelHeight;
		size_t m_liftMoveSpeed;
		size_t m_timeDoorsOpen;
		size_t m_currentLevel;
		size_t m_moveTimerPeriod;
		size_t m_stepDistanceCounter;

		void moveStep(int direction);
		void moveStepUp();
		void moveStepDown();

		friend SM_STATE(setTimerOfMoveStep);
		friend SM_STATE(waitTimerAndMove);
		friend SM_STATE(openDoorsAndSetTimer);
		friend SM_STATE(waitDoorsTimer);
		//friend void* setTimerOfMoveStep(const void *argin, void *argout);
		//friend void* waitTimerAndMove(const void *argin, void *argout);
	};

}

#endif
