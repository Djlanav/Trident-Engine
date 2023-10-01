#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <Windows.h>
#include "Core/Typedefs.h"
#include "Core/Mesh.h"
#include "Core/Loader.h"
#include "Core/Shader.h"
#include "Core/Texturing.h"
#include "Core/FileIO.h"
#include "Plugins/Logger.h"
#include "Core/MainEngineUI.h"
#include "Core/EngineUI/EngineUIFunctionPointers.h"
#include "Core/Display.h"
#include "Core/Rendering.h"
#include "Core/Engine.h"

#define CHECK_FUNCTION_POINTERS 0

void CEngine::GetFunctionPointers()
{
	UIDLL = LoadLibrary(TEXT("EngineUI.dll"));
	ELogStatus uiDllStatus;

	if (UIDLL == NULL)
	{
		std::exit(-1);
	}
	else
	{
		uiDllStatus = SUCCESS;
		CLogger::Log("UI DLL Status:", &uiDllStatus, nullptr);
	}

	createEngineUI = (CreateObjectFn)GetProcAddress(UIDLL, "createUI");

	getFloatElements = (GetFPMapFn)GetProcAddress(UIDLL, "GetFloatUIElements");
	getUnsignedElements = (GetUIPMapFn)GetProcAddress(UIDLL, "GetUnsignedUIElements");

	setFloatElements = (SetFPMapFn)GetProcAddress(UIDLL, "SetFloatUIElements");
	setUnsignedElements = (SetUIPMapFn)GetProcAddress(UIDLL, "SetUnsignedUIElements");

	addFloatElements = (AddFloatElementsFn)GetProcAddress(UIDLL, "AddFloatUIElement");
	addIntegerElements = (AddUnsignedIntElementsFn)GetProcAddress(UIDLL, "AddIntegerUIElement");

#if CHECK_FUNCTION_POINTERS == 1
	ELogStatus functionPointerStatus = SUCCESS;

	if (createEngineUI == NULL)
	{
		functionPointerStatus = FAILURE;
		CLogger::Log("CreateUI Loading Status:", &functionPointerStatus, nullptr);
	}
	else if (getFloatElements == NULL)
	{
		functionPointerStatus = FAILURE;
		CLogger::Log("GetFloatElements Loading Status:", &functionPointerStatus, nullptr);
	}
	else if (getUnsignedElements == NULL)
	{
		functionPointerStatus = FAILURE;
		CLogger::Log("GetUnsignedElements Loading Status:", &functionPointerStatus, nullptr);
	}
	else if (setFloatElements == NULL)
	{
		functionPointerStatus = FAILURE;
		CLogger::Log("SetFloatElements Loading Status:", &functionPointerStatus, nullptr);
	}
	else if (setUnsignedElements == NULL)
	{
		functionPointerStatus = FAILURE;
		CLogger::Log("SetUnsignedElements Loading Status:", &functionPointerStatus, nullptr);
	}
	else if (addFloatElements == NULL)
	{
		functionPointerStatus = FAILURE;
		CLogger::Log("AddFloatElements Loading Status:", &functionPointerStatus, nullptr);
	}
	else if (addIntegerElements == NULL)
	{
		functionPointerStatus = FAILURE;
		CLogger::Log("AddIntegerElemetns Loading Status:", &functionPointerStatus, nullptr);
	}
#else
	std::cout << "\nFunction Pointer Checking Disabled\n\n";
#endif
}

void CEngine::InitializeCoreModules(CRenderer* Renderer, CDisplay* Display, CLoader* Loader)
{
	EngineRenderer = Renderer;
	EngineDisplay = Display;
	EngineLoader = Loader;
}

void CEngine::InitCore(CRenderer* Renderer, CDisplay* Display, CLoader* Loader)
{
	InitializeCoreModules(Renderer, Display, Loader);

	EngineDisplay->CreateDisplay();
	EngineRenderer->SetIsWireframeEnabled(false);
	EngineRenderer->InitializeMeshData();

	EngineMesh = EngineLoader->LoadMeshFromVao(EngineRenderer->GetMeshData());

	EngineRenderer->InitializeShaders();
	EngineRenderer->InitializeTextures();
}

void CEngine::Update(CEngineUI* UI)
{
	ProccessInput();

	UI->CreateUIFrame();
	EngineRenderer->ClearScreen();

	EngineRenderer->GetShaderProgram()->StartShaderProgram();
}

void CEngine::Close()
{
	FreeLibrary(UIDLL);
}