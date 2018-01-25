#include "Lift.hpp"

namespace lift {

	Lift::Lift(size_t numberOfLevels, size_t levelHeight, size_t liftMoveSpeed, size_t timeDoorsOpen) :
		m_numberOfLevels(numberOfLevels),
		m_levelHeight(levelHeight),
		m_liftMoveSpeed(liftMoveSpeed),
		m_timeDoorsOpen(timeDoorsOpen * 1000),
		m_currentLevel(kLevelsMin),
		m_moveTimerPeriod(1000/liftMoveSpeed),
		m_stepDistanceCounter(0)
	{ }

	size_t Lift::getCurrentLevel() const
	{
		return m_currentLevel;
	}

	void Lift::moveStep(int direction)
	{
		m_stepDistanceCounter++;

		if(m_stepDistanceCounter >= m_levelHeight) {
			m_stepDistanceCounter = 0;
			m_currentLevel += direction;
		}
	}

	void Lift::moveStepUp()
	{
		moveStep(1);
	}

	void Lift::moveStepDown()
	{
		moveStep(-1);
	}

	bool Lift::moveStepToLevel(size_t destination)
	{
		if(m_currentLevel == destination) {
			return true;
		}

		if(m_currentLevel > destination) {
			moveStepDown();
		}
		else {
			moveStepUp();
		}

		return false;
	}
}
