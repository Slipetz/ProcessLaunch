#ifndef __ICOMMAND__
#define __ICOMMAND__

//ICommand - Interface for any class that wishes to act as a Command object that can be executed elsewhere
// Ryan Slipetz - 0663240
// Date: 9/27/2015

class ICommand {
public:
	//Virtual Destructor
	virtual ~ICommand() {}
public:
	virtual void execute() = 0;
};

#endif