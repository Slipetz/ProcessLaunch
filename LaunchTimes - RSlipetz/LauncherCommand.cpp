#include <process.h>
#include "LauncherCommand.h"

void LauncherCommand::execute() {
	wstring command = executable + L" " + parameters;
	
	//Load and deploy the executable
	try {
		wchar_t* commandLine = new wchar_t[CP_MAX_COMMANDLINE];
		wcsncpy_s(commandLine, CP_MAX_COMMANDLINE, command.c_str(), command.size() + 1);
		processFailed = CreateProcess(NULL, commandLine, NULL, //No Higher Security
			NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &sInfo, &pi);
		
		delete[] commandLine;
	}
	catch (std::bad_alloc)
	{
		wcerr << "Insufficient memory to launch this application!" << endl;
		processFailed = 0;
	}
	catch (std::exception)
	{
		wcerr << "Error occured during execute()!" << endl;
		processFailed = 0;
	}

	if (GetLastError() != 0)
	{
		throw L"Failed to launch process: " + executable + L" with parameters: " + parameters;
	}
}
