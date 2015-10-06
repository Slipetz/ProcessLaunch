#ifndef __RESULTS__
#define __RESULTS__

//Results - Class that holds onto all of the data that has been processed/created during CreateProcess so we can easily output
//			from one class
// Ryan Slipetz - 0663240
// Date: 9/27/2015

#include <iostream>
using namespace std;

#include "LauncherCommand.h"

class Results {
private:
	LauncherCommand results;
	DWORD exitCode = 0;
	SYSTEMTIME kerTime;
	SYSTEMTIME usrTime;

public:
	Results(LauncherCommand& command);
	int getLaunchGroup() const { return results.getLaunchGroup(); }
	SYSTEMTIME getKernelTime() const { return kerTime; }
	SYSTEMTIME getUserTime() const { return usrTime; }
	bool hasProcessFailed() const { return results.hasProcessFailed(); }

public:
	//Operator Overloading
	friend wostream& operator<<(wostream& out, Results const& result);
};

#endif