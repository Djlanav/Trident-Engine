#include "Core/CommonHeaders.h"
#include "Core/Typedefs.h"
#include "Core/Module.h"
#include "Plugins/Logger.h"

// Note to self: The string used to refer to the dll by file name (i.e. EngineUI.dll) must always be a WString.

HINSTMap_W CModule::DLLMap{};
HINSTRefNameMap CModule::DLLNameRefs{};

WSVector CModule::DLLNameVector = {};

void CModule::GetDLL(const String& RefName, const WString& FileName, HMODULE DLL)
{
	DLLNameRefs.insert({ RefName, FileName });
	DLLMap.insert({ FileName, DLL });

	DLLNameVector.push_back(FileName);
}

void CModule::LoadDLLs()
{
	ELogStatus loadStatus;

	for (size_t i = 0; i < DLLMap.size(); i++)
	{
		const wchar_t* dllName = DLLNameVector.at(i).c_str();
		DLLMap.at(DLLNameVector.at(i)) = LoadLibrary(dllName);

		if (DLLMap.at(DLLNameVector.at(i)) == NULL)
		{
			loadStatus = FAILURE;
			CLogger::Log("FAILED TO LOAD DLL! STATUS:", &loadStatus, nullptr);
		}
	}
}

HMODULE* CModule::GetDLLHandle(const String& RefName)
{
	HMODULE* handle = &(DLLMap.at(DLLNameRefs.at(RefName)));
	return handle;
}

void CModule::FreeDLL(const String& Name)
{
	FreeLibrary(DLLMap.at(DLLNameRefs.at(Name)));
}

void CModule::FreeAll()
{
	for (auto& name : DLLNameRefs)
	{
		FreeLibrary(DLLMap.at(DLLNameRefs.at(name.first)));
	}
}