#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "Core/Typedefs.h"
#include "Core/Module.h"
#include "Plugins/Logger.h"

void CModule::GetDLL(const String& FileName, const WString& RefName, HINSTANCE* DLL)
{
	DLLMap->insert({ RefName, DLL });
	DLLNameVector.push_back(RefName);
}

void CModule::LoadDLLs()
{
	ELogStatus loadStatus;

	for (size_t i = 0; i < DLLMap->size(); i++)
	{
		const wchar_t* dllName = DLLNameVector.at(i).c_str();
		*DLLMap->at(DLLNameVector.at(i)) = LoadLibrary(dllName);

		if (*DLLMap->at(DLLNameVector.at(i)) == NULL)
		{
			loadStatus = FAILURE;
			CLogger::Log("FAILED TO LOAD DLL! STATUS:", &loadStatus, nullptr);
		}
	}
}

void CModule::FreeDLL(const String& Name)
{

}