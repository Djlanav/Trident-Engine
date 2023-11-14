#pragma once

#include <Windows.h>

// ** Using **
using HINSTMap = std::unordered_map<String, HINSTANCE*>;

// ** Unique Using **
using WSVector = std::vector<std::wstring>;
using WString = std::wstring;
using HINSTMap_W = std::unordered_map<WString, HINSTANCE*>;

class CModule
{
private:
	HINSTMap_W* DLLMap;
	WSVector DLLNameVector;

public:
	void GetDLL(const WString& Name, HINSTANCE* DLL);
	void LoadDLLs();
};