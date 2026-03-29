#include "pch.h"
export module Debug;
import <source_location>;

export namespace F
{
	class Debug
	{

	private:
		static std::string GetDebugMessage(const std::string& msg, const char* logType, std::source_location& loc);

	public:
		static void Log(const std::string& msg, std::source_location loc = std::source_location::current());
		static void Log(const std::wstring& msg, std::source_location loc = std::source_location::current());
		
		static void LogWarning(const std::string& msg, std::source_location loc = std::source_location::current());
		static void LogWarning(const std::wstring& msg, std::source_location loc = std::source_location::current());
		
		static void LogError(const std::string& msg, std::source_location loc = std::source_location::current());
		static void LogError(const std::wstring& msg, std::source_location loc = std::source_location::current());

	};



}