#include "Application.hpp"

int main(int argc, char* argv[])
{
	helper::CommandLine::Application app("lift");

	app.about << "Lift simulation program.";
	app.usage << "lift [OPTIONS ...]";

	/* Create global option object. */
	app.addopt(helper::CommandLine::Option("l", "levels", "Set number of levels (default set to 5, range 5-20).", true));
	app.addopt(helper::CommandLine::Option("H", "height", "Set height of levels in meters (default set to 3)", true));
	app.addopt(helper::CommandLine::Option("s", "speed", "Set lift move speed in meter per second (default set to 2, range 1-10)", true));
	app.addopt(helper::CommandLine::Option("t", "time", "Set time between doors open/close in second (default set to 5)", true));
	/* Add default command handler. */
	app.addDefaultCommand(new lift::Application());
	app.start(argc, argv);
	
	return 0;
}
