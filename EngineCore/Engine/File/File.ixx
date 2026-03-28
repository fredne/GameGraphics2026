#include "pch.h"
#include <fstream>

export module File;

export namespace F
{
	template<typename T>
	concept PrimitiveType = std::is_trivially_copyable_v<T>;

	class File
	{
	private:

	public:

		template<PrimitiveType T>
		static void Write(std::ofstream& out, const T& data)
		{
			out.write((char*)&data, sizeof(T));
		}
		static void WriteString(std::ofstream& out, const std::string& str)
		{
			size_t len = str.size();
			out.write((char*)&len, sizeof(len));
			out.write(str.data(), len);
		}
		static void WriteString(std::ofstream& out, const std::wstring& wstr)
		{
			WriteString(out, WStringToString(wstr));
		}

		template<PrimitiveType T>
		static void Read(std::ifstream& in, const T& data)
		{
			in.read((char*)&data, sizeof(T));
		}
		static void ReadString(std::ifstream& in, std::string& str)
		{
			size_t len; in.read((char*)&len, sizeof(len));
			str.resize(len); in.read(&str[0], len);
		}
		static void ReadString(std::ifstream& in, std::wstring& str)
		{
			std::string temp;
			ReadString(in, temp);
			str = StringToWString(temp);
		}

		static std::wstring StringToWString(const std::string& str)
		{
			if (str.empty()) return { };
			int size = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
			std::wstring result(size, 0);
			MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), result.data(), size);
			return result;
		}
		static std::string WStringToString(const std::wstring& wstr)
		{
			if (wstr.empty()) return { };
			int size = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
			std::string result(size, 0);
			WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), result.data(), size, nullptr, nullptr);
			return result;
		}

	};

}
