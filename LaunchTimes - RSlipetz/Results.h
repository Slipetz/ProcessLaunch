#ifndef __RESULTS__
#define __RESULTS__

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

public:
	//Operator Overloading
	friend wostream& operator<<(wostream& out, Results const& result);
};

#endif