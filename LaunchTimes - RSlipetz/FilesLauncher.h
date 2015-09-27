#ifndef __LAUNCHER__
#define __LAUNCHER__

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include <filesystem>
using namespace std::tr2::sys;

#include "ILauncher.h"
#include "LauncherCommand.h"

class FilesLauncher : public ILauncher {
public:
	using LauncherMap = map<int, vector<LauncherCommand>>;
	using LauncherObject = pair<int, vector<LauncherCommand>>;

private:
	//Data Members
	path filePath;

public:
	//Constructor
	FilesLauncher(char* &argv) : filePath(path(argv)) { }

	void launch() override;

private:
	void GenerateCommand(LauncherMap&, string&);
};

#endif