#ifndef __IARGUMENTVALIDATOR__
#define __IARGUMENTVALIDATOR__


//IArgumentValidator - Interface for any class that wishes to parse/validate the Command arguments
// Ryan Slipetz - 0663240
// Date: 9/27/2015

#include <iostream>
#include <string>
using namespace std;

class IArgumentValidator {
protected:
	//Data members
	int argc;
	char** argv;
	wstring errorMessage;

protected:
	//Constructor
	IArgumentValidator(int &argc, char** &argv) : argc(argc), argv(argv) { }
public:
	wstring GetErrorMessage() { return errorMessage; }
	virtual bool validate() = 0;

};

#endif
