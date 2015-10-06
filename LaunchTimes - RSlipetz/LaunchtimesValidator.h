#ifndef __LAUNCHVALIDATOR__
#define __LAUNCHVALIDATOR__

#include "IArgumentValidator.h"

//LaunchTimes Validator - Implementation of the ArgumentValidator interface for the LaunchTimes program.
//						  Validates that the incoming arguments are correct (Correct number of arguments, correct file ext and file exists)
// Ryan Slipetz - 0663240
// Date: 9/27/2015

class LaunchTimesValidator : public IArgumentValidator {
public:
	//Constructor
	LaunchTimesValidator(int &argc, char** &argv) : IArgumentValidator(argc, argv) { }

	//Validate - Validates the Arugments for the LaunchTimes program
	//Parameters - None - overridden base method that uses the base classes data members
	//Returns - bool value stating whether or not the data is valid - true = valid
	bool validate() override;
};


#endif