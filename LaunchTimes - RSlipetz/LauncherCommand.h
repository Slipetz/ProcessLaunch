#ifndef __LAUNCHERCOMMAND__
#define __LAUNCHERCOMMAND__

#include <iostream>
using namespace std;

#include "ICommand.h"

class LauncherCommand : public ICommand {

	//Data Members
private:
	wstring executable;
	wstring parameters;

public:
	void execute() override;
};

#endif
