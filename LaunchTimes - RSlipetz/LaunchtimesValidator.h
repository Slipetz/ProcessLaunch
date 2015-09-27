#ifndef __LAUNCHVALIDATOR__
#define __LAUNCHVALIDATOR__

#include <iostream>
#include <string>
using namespace std;

#include <filesystem>
using namespace tr2::sys;

#include "IArgumentValidator.h"


//LaunchTimes Validator - Implementation of the ArgumentValidator interface for the LaunchTimes program.
//						  Validates that the incoming arguments are correct (Correct number of arguments, correct file ext and file exists)
// Ryan Slipetz - 0663240
// Date: 9/27/2015

class LaunchTimesValidator : public IArgumentValidator {
public:
	//Constructor
	LaunchTimesValidator(int &argc, char** &argv) : IArgumentValidator(argc, argv) { }

	//Data Functions
	bool validate() override;
};


#endif