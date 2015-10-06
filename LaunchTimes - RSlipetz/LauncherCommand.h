#ifndef __LAUNCHERCOMMAND__
#define __LAUNCHERCOMMAND__

//LauncherCommand - Concrete Command class that contains all of the necessary to create/launch a process and hold the results of the process
// Ryan Slipetz - 0663240
// Date: 9/27/2015

#include <Windows.h>
#include "ICommand.h"

class LauncherCommand : public ICommand {
private:
	//Data Members
	wstring executable;
	wstring parameters;
	int launchGroup;

	//FailState Data if CreateProcess fails
	BOOL processFailed;
	wstring errorMsg;

	//Disposable Data Members/One-time use Data Members for Create Process
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pi;
	long CP_MAX_COMMANDLINE;

public:
	//Constructor
	LauncherCommand(int &launchGroup, wstring &executable, wstring &params) : launchGroup(launchGroup), executable(executable), parameters(params), sInfo({ 0 }), pi({ 0 }), CP_MAX_COMMANDLINE(32768) {
		sInfo.cb = sizeof(STARTUPINFO);
	}

public:
	//Execute - Overriden ICommand method - executes the launch of the Process and handles all the necessary information regarding it's creation and deployment
	//Accepts - Nothing. Overriden base-class method
	//Returns - Nothing. All data generated stays within the class
	void execute() override;
public:
	//Getters
	PROCESS_INFORMATION& getProcInfo() { return pi; }
	wstring getExecutable() const { return executable; }
	wstring getParameters() const { return parameters; }
	int getLaunchGroup() const { return launchGroup; }
	bool hasProcessFailed() const { return processFailed == 0; }
	wstring getErrorMsg() const { return errorMsg; }
};

#endif
