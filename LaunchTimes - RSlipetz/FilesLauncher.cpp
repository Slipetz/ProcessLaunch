#include <fstream>
#include <future>
#include <algorithm>
using namespace std;

#include "FilesLauncher.h"
#include "Results.h"
#include "StringHelpers.h"
using namespace StringHelpers;

//LaunchProcesses - Launches all of the Commands for the corresponding LaunchGroup in an asynchronous fashion
//Accepts - Vector<LaunchCommand> that contains all of the commands to be launched in concurrently
//Returns - Vector<Results> that contains all of the results for the Commands that were executed in this launch group
vector<Results> LaunchProcesses(vector<LauncherCommand>& commands) {
	vector<future<void>> futureCallbacks;

	for (LauncherCommand& command : commands) {
		future<void> callback = async(launch::async, &LauncherCommand::execute, &command);
		futureCallbacks.push_back(move(callback));
	}

	//Wait for the callbacks to all comeback before we proceed to process the data
	for (future<void> &callback : futureCallbacks)
		callback.get();

	vector<Results> processResults;
	for (LauncherCommand& command : commands)
	{
		processResults.push_back(command);
		CloseHandle(command.getProcInfo().hThread);
		CloseHandle(command.getProcInfo().hProcess);
	}
	return processResults;
}

//OutputResults - Handles the output of the Results objects that were generated from the LauncherCommands
//Accepts - Vector<Results> that contains all of the results from each of the LauncherCommands that were executed
//Returns - Nothing. All output is directly to the console
void OutputResults(vector<Results>& results) {
	int launchGroup = 0;
	int totalSuccess = 0;
	vector<Results> errorResults;
	for (Results& output : results) {
		if (output.hasProcessFailed()) {
			errorResults.push_back(output);
			continue;
		}

		if (output.getLaunchGroup() != launchGroup) {
			if (totalSuccess != 0) {
				wcout << L"Processes Launched: " << totalSuccess << endl;
				wcout << endl;
				totalSuccess = 0;
			}

			launchGroup = output.getLaunchGroup();
			wcout << "G" << launchGroup << ":" << endl;
		}
		wcout << output << endl;
		++totalSuccess;
	}

	if (totalSuccess != 0) {
		wcout << L"Processes Launched: " << totalSuccess << endl;
	}

	if (errorResults.size() > 0) {
		wcout << endl;
		wcout << L"Failed Processes - Num Failed: " << errorResults.size() << L"\n" << wstring(25, '*') << endl;
		for (Results& result : errorResults) {
			wcout << result << endl;
		}
	}

}

void FilesLauncher::execute() {
	//Need to parse the file to build what we need to run and when
	ifstream launchFile(absolute(filePath));

	//Based on file input, we need to sort/order them - Sorted with what we are sorting
	//Using a map = Sorted by key, w/ Vector<LauncherCommand> = map<int, LauncherCommand>
	LauncherMap launcher;

	//Need to parse each line, and pass it to the invoke to create the command objects
	string fileLine;
	while (getline(launchFile, fileLine)) {
		try {
			//Comment line - useful for commenting my .txt file!
			if (fileLine[0] == '#')
				continue; 

			GenerateCommand(launcher, fileLine);
		}
		catch (wstring& error) {
			wcout << error << endl;
			wcout << L"Bypassing line. Continuing..." << endl;
			wcout << endl;
		}
	}

	launchFile.close();

	vector<Results> programResults;
	for (LauncherObject sequence : launcher) {
		vector<Results> results = LaunchProcesses(sequence.second);
		programResults.insert(programResults.end(), results.begin(), results.end());
	}

	OutputResults(programResults);
}

void FilesLauncher::GenerateCommand(LauncherMap &map, string &fileLine) {
	wstring parsingLine = wstring(fileLine.begin(), fileLine.end());
	size_t startIndex = 0;

	//Get Launch Group
	size_t commaPos = parsingLine.find_first_of(',');
	if (commaPos == string::npos) { 
		throw L"Invalid line format (Missing Comma): \n" + parsingLine;
	}

	wstring launchNumber = parsingLine.substr(startIndex, commaPos);
	//Need the full size of the string before the trim
	startIndex += launchNumber.size() + 1;
	launchNumber = trim(launchNumber);
	int launchGroup = stoi(launchNumber);

	//Get Executable
	commaPos = parsingLine.find_first_of(',', startIndex);
	if (commaPos == string::npos) {
		throw L"Invalid line format (Missing Comma): \n" + parsingLine;
	}

	wstring test = parsingLine.substr(8, 300);
	wstring executable = parsingLine.substr(startIndex, (commaPos - startIndex));
	//Need the full size of the string before the trim
	startIndex += executable.size() + 1;
	executable = trim(executable);


	//Get Parameters
	wstring parameters = L"";
	if(startIndex < parsingLine.size())
		parameters = parsingLine.substr(startIndex, parsingLine.size() - startIndex);
	parameters = trim(parameters);

	map[launchGroup].push_back(LauncherCommand(launchGroup, executable, parameters));
}


