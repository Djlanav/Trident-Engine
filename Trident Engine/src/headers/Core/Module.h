#pragma once

// ** Unique Using **
using HINSTMap = std::unordered_map<String, HMODULE>;
using WSVector = std::vector<std::wstring>;
using WString = std::wstring;
using HINSTMap_W = std::unordered_map<WString, HMODULE>;

using HINSTRefNameMap = std::unordered_map<String, WString>; // First is the ordinary name, second is the DLL name (MUST BE WIDE STRING CONTANG WCHAR_T)

class CModule
{
private:
	static HINSTMap_W DLLMap;
	static HINSTRefNameMap DLLNameRefs;

	static WSVector DLLNameVector;

public:
	void GetDLL(const String& RefName, const WString& FileName, HMODULE DLL);
	void LoadDLLs();
	HMODULE* GetDLLHandle(const String& RefName);

	void FreeDLL(const String& Name);
	void FreeAll();
};