#include "pch.h"
#include "Debug.h"
#include <iostream>
#include <string>
#include <cstdio>

namespace F
{
	void Debug::Log(const char* format, ...)
	{
		char buffer[1024];
		va_list args;
		va_start(args, format);
		vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);
		va_end(args);
		
		OutputDebugStringA(buffer);
		OutputDebugStringA("\n");
	}
	void Debug::Log(const wchar_t* format, ...)
	{
		wchar_t buffer[1024];
		va_list args;
		va_start(args, format);
		swprintf_s(buffer, (size_t)(sizeof(buffer) * 0.5f), format, args);
		va_end(args);

		OutputDebugStringW(buffer);
		OutputDebugStringW(L"\n");

	}
}