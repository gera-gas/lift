#include <stdlib.h>
#include <conio.h>  
#include <stdio.h>
#include <regex>
#include <string>
#include "Application.hpp"

namespace lift {

	Application::Application() :
		Command(),
		m_liftPositionStorer(0)
	{ }

	size_t Application::getOptionValue(std::string option)
	{
		std::regex integer("[[:digit:]]+");

		if(regex_match(option, integer)) {
			return std::stoi(option, nullptr, 0);
		}

		return 0;
	}

	void Application::indicateLiftPosition(Lift& lift)
	{
		size_t level = lift.getCurrentLevel();

		if(level != m_liftPositionStorer) {
			m_liftPositionStorer = level;
			std::cout << "Lift position: " << m_liftPositionStorer << std::endl;
		};
	}

	size_t Application::inputLevel(const char* introText)
	{
		std::string userInput;
		std::regex integer("[[:digit:]]+");
		size_t userLevel;

		while(true) {
				std::cout << introText;
				std::cin >> userInput;

				if(regex_match(userInput, integer)) {
					userLevel = std::stoi(userInput, nullptr, 0);

				if(userLevel > 0 && userLevel <= Lift::kLevelsMax) {
					break;
				}
			}
		}

		return userLevel;
	}

	void Application::handler(std::map<std::string, helper::CommandLine::Option>& global_options, helper::StringArray& args)
	{
		size_t numberOfLevels = Lift::kLevelsMin;
		size_t levelHeight = Lift::kLevelHeight;
		size_t liftMoveSpeed = Lift::kLiftMoveSpeedDefault;
		size_t timeDoorsOpen = Lift::kTimeDoorsOpen;

		#define OPTION_ERROR(n)\
			std::cout << "ERROR: incorrectly option value of '";\
			std::cout << n;\
			std::cout << "', see help information." << std::endl;\
			return;

		if (global_options["levels"].present) {
			numberOfLevels = getOptionValue(global_options["levels"].value);

			if(numberOfLevels < Lift::kLevelsMin || numberOfLevels > Lift::kLevelsMax) {
				OPTION_ERROR("levels");
			}
		}

		if (global_options["height"].present) {
			levelHeight = getOptionValue(global_options["height"].value);

			if(levelHeight == 0) {
				OPTION_ERROR("height");
			}
		}

		if (global_options["speed"].present) {
			liftMoveSpeed = getOptionValue(global_options["speed"].value);

			if(liftMoveSpeed < Lift::kLiftMoveSpeedMin || liftMoveSpeed > Lift::kLiftMoveSpeedMax) {
				OPTION_ERROR("speed");
			}
		}

		if (global_options["time"].present) {
			timeDoorsOpen = getOptionValue(global_options["time"].value);

			if(timeDoorsOpen == 0) {
				OPTION_ERROR("time");
			}
		}

		Lift lift(numberOfLevels, levelHeight, liftMoveSpeed, timeDoorsOpen);

		while(true) {

		#if HELPER_PLATROM_WINDOWS
			system("cls");
		#else
			system("clear");
		#endif

			std::cout << "PARAMETERS:" << std::endl;
			std::cout << "  number of levels = " << numberOfLevels << std::endl;
			std::cout << "  level height = " << levelHeight << " meters" << std::endl;
			std::cout << "  lift move speed = " << liftMoveSpeed << " meter per second" << std::endl;
			std::cout << "  time of doors open/close = " << timeDoorsOpen << " seconds" << std::endl;

			std::cout << std::endl << "CONTROLS:" << std::endl;
			std::cout << "  exit -- close application." << std::endl;
			std::cout << "  go   -- start emulation process." << std::endl;

			std::cout << std::endl << "Please, enter command: ";

			std::string userInput;
			std::cin >> userInput;

			if(userInput == "exit") {
				return;
			}

			if(userInput != "go") {
				continue;
			}

			size_t userLevel;

			ArgumentsForLiftMoveStates argumentsForLiftMoveStates = { &lift, 0 };

			std::cout << "Lift current position: " << lift.getCurrentLevel() << std::endl;

			userLevel = inputLevel("Please, enter your level: ");

			argumentsForLiftMoveStates.level = userLevel;

			while(sm_force_start(&liftMoveToLevel, &argumentsForLiftMoveStates, NULL) != SM_STATE_COMPLETED) {
				indicateLiftPosition(lift);
			}

			std::cout << "Lift open doors." << std::endl;
			userLevel = 0;

			while(sm_force_start(&liftDoorsProcessing, &lift, NULL) != SM_STATE_COMPLETED) {
				if(userLevel == 0) {
					userLevel = inputLevel("Please, enter destination level: ");
				}
			}

			std::cout << "Lift close doors." << std::endl;
			std::cout << "For stop lift press any key..." << std::endl;

			argumentsForLiftMoveStates.level = userLevel;

			while(sm_force_start(&liftMoveToLevel, &argumentsForLiftMoveStates, NULL) != SM_STATE_COMPLETED) {
				indicateLiftPosition(lift);

			#if HELPER_PLATROM_WINDOWS
				if(_kbhit() != 0) break;
			#else
				if(kbhit() != 0) break;
			#endif
			}

			std::cout << "Lift open doors." << std::endl;

			while(sm_force_start(&liftDoorsProcessing, &lift, NULL) != SM_STATE_COMPLETED);

			std::cout << "Lift close doors." << std::endl;

			std::cout << std::endl << "Press Enter to continue...";
			while(std::cin.get() != '\n');

			std::fflush(stdin);
			getchar();
		}
	}

}
