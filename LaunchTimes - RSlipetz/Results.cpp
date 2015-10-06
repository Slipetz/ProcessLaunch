#include <string>
#include <iomanip>
#include "Results.h"

Results::Results(LauncherCommand & command) : results(command)
{
	GetExitCodeProcess(results.getProcInfo().hProcess, &exitCode);
	FILETIME creationTime, exitTime, kernelTime, userTime;
	GetProcessTimes(results.getProcInfo().hProcess, &creationTime, &exitTime, &kernelTime, &userTime);
	FileTimeToSystemTime(&kernelTime, &kerTime);
	FileTimeToSystemTime(&userTime, &usrTime);
}

wostream& operator<<(wostream & out, Results const& result)
{
	if (result.hasProcessFailed())
	{
		out << "LG:" << setw(2) << left << result.getLaunchGroup();
		out << " PN:" << result.results.getExecutable();
		out << " PM:" << result.results.getParameters();
		out << " Error: " << result.results.getErrorMsg();
		return out;
	}
	out << "LG:" << setw(2) << left << result.getLaunchGroup();
	out << " K:" << internal << setfill(L'0') << setw(2) << result.kerTime.wMinute << "." << setw(2) << result.kerTime.wSecond << "." <<  setw(3) << result.kerTime.wMilliseconds;
	out << " U:" << setw(2) << result.usrTime.wMinute << "." << setw(2) << result.usrTime.wSecond << "." << setw(3) << result.usrTime.wMilliseconds;
	out << " E:" << setfill(L' ') << setw(3) << left << result.exitCode;
	out << " PN:" << result.results.getExecutable();
	out << " PM:" << result.results.getParameters();
	return out;
}
