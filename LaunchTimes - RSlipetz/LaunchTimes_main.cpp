//LaunchTimes_Main - Entry point for the program. Validates the input first to see its a correct file, and then will pass the data
//					 onto the FileRunner which will run the programs.
// Ryan Slipetz - 0663240
// Date: 9/27/2015

#include "LaunchtimesValidator.h"
#include "FilesLauncher.h"
using namespace std;

int main(int argc, char** argv) {

	LaunchTimesValidator validator(argc, argv);

	if (!validator.validate())
	{
		cout << validator.GetErrorMessage() << endl;
		return 1;
	}
	
	FilesLauncher launcher(argv[1]);
	launcher.launch();
}