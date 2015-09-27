#include <fstream>
using namespace std;

#include "FilesLauncher.h"

void FilesLauncher::launch() {
	//Need to parse the file to build what we need to run and when
	ifstream launchFile(absolute(filePath));

	//Based on file input, we need to sort/order them - Sorted with what we are sorting
	//Using a map = Sorted by key, w/ Vector<CommandObjects> = map<int, vector<ICommand>>
	LauncherMap launcher;

	//Need to parse each line, and pass it to the invoke to create the command objects
	string fileLine;
	while (getline(launchFile, fileLine)) {
		GenerateCommand(launcher, fileLine);
	}

	for (LauncherObject sequence : launcher) {
		//Don't need to worry about the number. It's job is done as it's sorted and provided us a common point
		//To attach all the objects to one vector
		for (LauncherCommand command : sequence.second)
		{
			command.execute();
		}
	}
}

void FilesLauncher::GenerateCommand(LauncherMap &map, string &fileLine) {

}
