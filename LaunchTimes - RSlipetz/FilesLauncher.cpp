#include <fstream>
#include <thread>
#include <algorithm>
using namespace std;

#include "FilesLauncher.h"
#include "Results.h"

vector<Results> LaunchThread(vector<LauncherCommand>& commands) {
	vector<HANDLE> threadHandles;
	vector<Results> processResults;
	for (LauncherCommand& command : commands)
	{
		command.execute();
		threadHandles.push_back(command.getProcInfo().hProcess);
	}
	WaitForMultipleObjects(threadHandles.size(), threadHandles.data(), TRUE, INFINITE);
	for (LauncherCommand& command : commands)
	{
		processResults.push_back(command);
		CloseHandle(command.getProcInfo().hThread);
		CloseHandle(command.getProcInfo().hProcess);
	}
	return processResults;
}

void OutputResults(vector<Results>& results) {
	int launchGroup = 0;
	for (Results& output : results) {
		if (output.getLaunchGroup() != launchGroup) {
			wcout << endl;
			launchGroup = output.getLaunchGroup();
			wcout << "G" << launchGroup << ":" << endl;
		}
		wcout << output << endl;
	}
}

void FilesLauncher::launch() {
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
		vector<Results> results = LaunchThread(sequence.second);
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


