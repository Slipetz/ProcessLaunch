#include <fstream>
#include <future>
#include <algorithm>
using namespace std;

#include "FilesLauncher.h"
#include "Results.h"

//LaunchThread - Launches all of the Commands for the corresponding LaunchGroup in an asynchronous fashion
//Accepts - Vector<LaunchCommand> that contains all of the commands to be launched in concurrently
//Returns - Vector<Results> that contains all of the results for the Commands that were executed in this launch group
vector<Results> LauncheProcesses(vector<LauncherCommand>& commands) {
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
	vector<Results> errorResults;
	for (Results& output : results) {
		if (output.hasProcessFailed()) {
			errorResults.push_back(output);
			continue;
		}

		if (output.getLaunchGroup() != launchGroup) {
			wcout << endl;
			launchGroup = output.getLaunchGroup();
			wcout << "G" << launchGroup << ":" << endl;
		}
		wcout << output << endl;
	}

	if (errorResults.size() > 0) {
		wcout << endl;
		wcout << L"Failed Processes\n" << wstring(16, '*') << endl;
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
		GenerateCommand(launcher, fileLine);
	}

	vector<Results> programResults;
	for (LauncherObject sequence : launcher) {
		vector<Results> results = LauncheProcesses(sequence.second);
		programResults.insert(programResults.end(), results.begin(), results.end());
	}

	OutputResults(programResults);
}

void FilesLauncher::GenerateCommand(LauncherMap &map, string &fileLine) {
	wstring parsingLine = wstring(fileLine.begin(), fileLine.end());
	size_t startIndex = 0;

	//Get Launch Group
	wstring launchNumber = parsingLine.substr(startIndex, parsingLine.find_first_of(','));
	startIndex += launchNumber.size() + 1;
	int launchGroup = stoi(launchNumber);

	//Get Executable
	wstring executable = parsingLine.substr(startIndex, parsingLine.find_first_of(',', startIndex) - 2);
	startIndex += executable.size() + 1;

	//Get Parameters
	wstring parameters = L"";
	if(startIndex < parsingLine.size())
		parameters = parsingLine.substr(startIndex, parsingLine.size() - startIndex);

	map[launchGroup].push_back(LauncherCommand(launchGroup, executable, parameters));
}


