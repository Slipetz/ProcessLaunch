#ifndef __ICOMMAND__
#define __ICOMMAND__

class ICommand {
protected:
	virtual void execute() = 0;
};

#endif