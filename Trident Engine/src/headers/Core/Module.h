#pragma once

#include <Windows.h>

// ** Unique Using **
using HINSTMap = std::unordered_map<String, HINSTANCE*>;
using WSVector = std::vector<std::wstring>;
using WString = std::wstring;
using HINSTMap_W = std::unordered_map<WString, HINSTANCE*>;

using HINSTRefNameMap = std::unordered_map<String, WString>; // First is the ordinary name, second is the DLL name (MUST BE WIDE STRING CONTANG WCHAR_T)

class CModule
{
private:
	HINSTMap_W* DLLMap;
	HINSTRefNameMap* DLLNameRefs;

	WSVector DLLNameVector;

public:
	void GetDLL(const String& RefName, const WString& FileName, HINSTANCE* DLL);
	void LoadDLLs();

	void FreeDLL(const String& Name);
	void FreeAll();
};