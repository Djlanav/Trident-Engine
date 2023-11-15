#pragma once

#include <Windows.h>

// ** Unique Using **
using HINSTMap = std::unordered_map<String, HINSTANCE*>;
using WSVector = std::vector<std::wstring>;
using WString = std::wstring;
using HINSTMap_W = std::unordered_map<WString, HINSTANCE*>;

class CModule
{
private:
	HINSTMap_W* DLLMap;
	WSVector DLLNameVector;

public:
	void GetDLL(const String& FileName, const WString& RefName, HINSTANCE* DLL);
	void LoadDLLs();

	void FreeDLL(const String& Name);
	void FreeAll();
};