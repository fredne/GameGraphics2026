#include "pch.h"
import Debug;
import File;

namespace F
{
	std::string Debug::GetDebugMessage(const std::string& msg, const char* logType, std::source_location& loc)
	{
		return std::format("File {0}: line {1}\n{2}: {3}\n", loc.file_name(), loc.line(), logType, msg);
	}

	void Debug::Log(const std::string& msg, std::source_location loc)
	{
		OutputDebugStringA(GetDebugMessage(msg, "Log", loc).c_str());
	}

	void Debug::Log(const std::wstring& msg, std::source_location loc)
	{
		Log(File::WStringToString(msg), loc);
	}

	void Debug::LogWarning(const std::string& msg, std::source_location loc)
	{
		OutputDebugStringA(GetDebugMessage(msg, "Warning", loc).c_str());
	}

	void Debug::LogWarning(const std::wstring& msg, std::source_location loc)
	{
		LogWarning(File::WStringToString(msg), loc);
	}

	void Debug::LogError(const std::string& msg, std::source_location loc)
	{
		OutputDebugStringA(GetDebugMessage(msg, "Error", loc).c_str());
	}

	void Debug::LogError(const std::wstring& msg, std::source_location loc)
	{
		LogError(File::WStringToString(msg), loc);
	}
}