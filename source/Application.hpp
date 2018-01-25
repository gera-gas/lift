#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "ApplicationHelpers.h"
#include "Lift.hpp"

namespace lift {

	/* Create default CLI command handler. */
	class Application : public helper::CommandLine::Command {
	public:
		Application();

		void handler(std::map<std::string, helper::CommandLine::Option>& global_options, helper::StringArray& args);

	private:
		size_t m_liftPositionStorer;

		size_t getOptionValue(std::string option);
		void indicateLiftPosition(Lift&);
		size_t inputLevel(const char*);
	};

}

#endif
