#include "pch.h"
#include <source_location>
export module Debug;

export namespace F
{
	class Debug
	{
	private:
		static std::string GetOutString(const std::string& logType, const std::string& msg, const std::source_location& loc);
	public:
		static void Log(const std::string& msg, const std::source_location& loc = std::source_location::current());
		static void Log(const std::wstring& msg, const std::source_location& loc = std::source_location::current());
		static void LogWarning(const std::string& msg, const std::source_location& loc = std::source_location::current());
		static void LogWarning(const std::wstring& msg, const std::source_location& loc = std::source_location::current());
		static void LogError(const std::string& msg, const std::source_location& loc = std::source_location::current());
		static void LogError(const std::wstring& msg, const std::source_location& loc = std::source_location::current());

	};
}

