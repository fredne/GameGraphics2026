#pragma once

namespace F
{
	class Debug
	{
	public:
		static void Log(const char* format, ...);
		static void Log(const wchar_t* format, ...);
	};
}

