#include <process.h>
#include <string>
#include <iostream>
using namespace std;

#include "LauncherCommand.h"

//GetErrorMessage - Uses the "GetLastError" code and renders it as a readable string as opposed to a code
//Accepts - Nothing. Data is gathered from within the function
//Returns - wstring containing the "human-readable" error code message
wstring GetErrorMessage() {
	wchar_t buf[256];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
	return wstring(buf);
}

void LauncherCommand::execute() {
	wstring command = executable + L" " + parameters;
	
	//Load and deploy the executable
	try {
		wchar_t* commandLine = new wchar_t[CP_MAX_COMMANDLINE];
		wcsncpy_s(commandLine, CP_MAX_COMMANDLINE, command.c_str(), command.size() + 1);
		processFailed = CreateProcess(NULL, commandLine, NULL, //No Higher Security
			NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &sInfo, &pi);

		//If CreateProcess returns 0, an error has occurred within the program
		if (processFailed == 0)
			errorMsg = GetErrorMessage();
		
		delete[] commandLine;
	}
	catch (std::bad_alloc)
	{
		processFailed = 0;
		errorMsg = L"Insufficient memory to launch this application!";
	}
	catch (std::exception)
	{
		processFailed = 0;
		errorMsg = L"Error occured during LauncherCommand::execute with Command: " + command;
	}
	
	//Wait for the Process to finish before we return
	WaitForSingleObject(pi.hProcess, INFINITE);
}
