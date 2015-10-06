#ifndef __LAUNCHERCOMMAND__
#define __LAUNCHERCOMMAND__

#include <iostream>
#include <Windows.h>
using namespace std;

#include "ICommand.h"
#include "IThreadable.h"

class LauncherCommand : public ICommand {

	//Data Members
private:
	wstring executable;
	wstring parameters;
	int launchGroup;

	//FailState Data for the Process:
	BOOL processFailed;

	//Disposable Data Members
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pi;
	long CP_MAX_COMMANDLINE;

public:
	//Constructor
	LauncherCommand(int &launchGroup, wstring &executable, wstring &params) : launchGroup(launchGroup), executable(executable), parameters(params), sInfo({ 0 }), pi({ 0 }), CP_MAX_COMMANDLINE(32768) {
		sInfo.cb = sizeof(STARTUPINFO);
	}

public:
	void execute() override;
public:
	//Getters
	PROCESS_INFORMATION& getProcInfo() { return pi; }
	wstring getExecutable() const { return executable; }
	wstring getParameters() const { return parameters; }
	int getLaunchGroup() const { return launchGroup; }
	bool hasProcessFailed() const { return processFailed == 0; }
};

#endif
