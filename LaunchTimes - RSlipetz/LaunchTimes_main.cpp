//LaunchTimes_Main - Entry point for the program. Validates the input first to see its a correct file, and then will pass the data
//					 onto the FileRunner which will run the programs.
// Ryan Slipetz - 0663240
// Date: 9/27/2015

#include <memory>
#include <iostream>
using namespace std;

#include "LaunchtimesValidator.h"
#include "FilesLauncher.h"

int main(int argc, char** argv) {
	cout << "LaunchTimes - Ryan Slipetz - Fanshawe Student 6th Semester" << endl;

	unique_ptr<IArgumentValidator> validator(new LaunchTimesValidator(argc, argv));

	if (!validator->validate())
	{
		cout << validator->GetErrorMessage() << endl;
		return EXIT_FAILURE;
	}
	
	unique_ptr<ICommand> launcher(new FilesLauncher(argv[1]));
	launcher->execute();
}