#ifndef _UTILS_H
#define _UTILS_H

#include <sstream>
#include <iomanip>
#include <windows.h>
#include <shellapi.h>

namespace utils
{
	static std::string PadZerosLeft(int value)
	{
		std::stringstream ss;
		ss << std::setw(4) << std::setfill('0') << value;
		return ss.str();
	}

	static void OpenUrl(const char* path)
	{
		ShellExecuteA(GetActiveWindow(), "open", path, NULL, NULL, SW_SHOWNORMAL);
	}
}

#endif // _UTILS_H
