#ifndef __LAUNCHER__
#define __LAUNCHER__

//FilesLauncher - Concrete Command Class that takes in the file passed in the arguments, parses the data in the file and launches
//				  the individual commands that will create the process in an asynchronous fahion
// Ryan Slipetz - 0663240
// Date: 9/27/2015

#include <string>
#include <map>
#include <vector>
using namespace std;

#include <filesystem>
using namespace std::tr2::sys;

#include "LauncherCommand.h"

class FilesLauncher : public ICommand {
public:
	using LauncherMap = map<int, vector<LauncherCommand>>;
	using LauncherObject = pair<int, vector<LauncherCommand>>;

private:
	//Data Members
	path filePath;

public:
	//Constructor
	FilesLauncher(char* &argv) : filePath(path(argv)) { }

	//Execute - Overriden ICommand method - executes the reading of the file and creating the Command objects that will launch the processes
	//Accepts - Nothing. Overriden base-class method
	//Returns - Nothing. All data generated stays within the class
	void execute() override;

private:
	//GenerateCommand - Parses a line of the passed .txt file to gather the details about what process we will be creating
	//Accepts - LauncherMap - Map that will be filled inside the method with the necessary LauncherCommands and what LaunchGroup they belong to
	//			String - Line read in from the .txt file that will be parsed
	//Returns - Nothing. Places the data into the Map inside the function
	void GenerateCommand(LauncherMap&, string&);
};

#endif