#include <regex>
#include "LaunchtimesValidator.h"

bool LaunchTimesValidator::validate() {
	
	//Run the different validations for the files/program
	//Program should only have two arguments -> exe + filename
	if (argc != 2)
	{
		errorMessage = L"Incorrect number of parameters. Program usage: launchtimes.exe [file.txt]";
		return false;
	}

	//Means we have correct number of arguments. Validate that we have a .txt file next
	string filename = argv[1];
	regex fileExt(R"rgx(.txt$)rgx");
	bool regexMatch = regex_search(filename, fileExt, regex_constants::match_any);

	if (!regexMatch)
	{
		errorMessage = L"Incorrect file type. File must be a .txt extension.";
		return false;
	}

	//Means we have a .txt file. Now we need to verify that the file exists.
	path file(filename);
	if (!exists(file))
	{
		errorMessage = L"File does not exist! Please use an existing .txt file";
		return false;
	}

	//If we hit here, we have a valid .txt file. Validate the formatting?
	return true;
}
