#include "StringHelpers.h"

namespace StringHelpers {

	string trim(string &s)
	{
		//No point in trying to trim
		if (s.length() == 0)
			return s;

		int startIndex = 0;
		//Need to get rid of whitespace from the front and the back of the string
		for (char t : s) {
			if (t == ' ')
				++startIndex;
			else
				break;
		}

		//Means that it's entirely "spaces". Return blank string
		if (s.length() - startIndex == 0)
			return string();

		s = s.substr(startIndex, s.length() - startIndex);

		//Now check the back
		int substringLength = 0;
		for (int i = s.length(); i >= 0; --i) {
			if (s[i] == ' ')
				++substringLength;
			else
				break;
		}

		s = s.substr(0, s.length() - substringLength);

		return s;
	}

	wstring trim(wstring& s) {
		//No point in trying to trim
		if (s.length() == 0)
			return s;

		int startIndex = 0;
		//Need to get rid of whitespace from the front and the back of the string
		for (wchar_t t : s) {
			if (t == ' ')
				++startIndex;
			else
				break;
		}

		//Means that it's entirely "spaces". Return blank string
		if (s.length() - startIndex == 0)
			return wstring();

		s = s.substr(startIndex, s.length() - startIndex);

		//Now check the back
		int substringLength = 0;
		for (int i = s.length() - 1; i >= 0; --i) {
			if (s[i] == ' ')
				++substringLength;
			else
				break;
		}

		s = s.substr(0, s.length() - substringLength);

		return s;
	}

}

