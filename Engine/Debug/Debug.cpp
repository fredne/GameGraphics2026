#include "pch.h"
#include <iostream>
#include <string>
import Debug;
import File;

namespace F
{
	std::string Debug::GetOutString(const std::string& logType, const std::string& msg, const std::source_location& loc)
		{ return std::format("[{0} {1}:\n{3}: {2}\n", loc.file_name(), loc.line(), msg, logType); }

	void Debug::Log(const std::string& msg, const std::source_location& loc)
		{ OutputDebugStringA(GetOutString("Log", msg, loc).c_str()); }
	void Debug::Log(const std::wstring& msg, const std::source_location& loc)
		{ Log(File::WStringToString(msg), loc);}

	void Debug::LogWarning(const std::string& msg, const std::source_location& loc)
		{ OutputDebugStringA(GetOutString("Warning", msg, loc).c_str()); }
	void Debug::LogWarning(const std::wstring& msg, const std::source_location& loc)
		{ LogWarning(File::WStringToString(msg), loc); }

	void Debug::LogError(const std::string& msg, const std::source_location& loc)
		{ OutputDebugStringA(GetOutString("Error", msg, loc).c_str()); }
	void Debug::LogError(const std::wstring& msg, const std::source_location& loc)
		{ LogError(File::WStringToString(msg), loc); }

}