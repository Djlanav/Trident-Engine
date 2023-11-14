#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "Core/Typedefs.h"
#include "Core/Module.h"
#include "Plugins/Logger.h"

void CModule::GetDLL(const WString& Name, HINSTANCE* DLL)
{
	DLLMap->insert({ Name, DLL });
	DLLNameVector.push_back(Name);
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
			CLogger::Log("FAILED TO LOAD DLL:", &loadStatus, nullptr);
		}
	}
}