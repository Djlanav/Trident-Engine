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
#include "Core/Module.h"
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
}

void CEngine::InitializeCoreModules(CRenderer* Renderer, CDisplay* Display)
{
	EngineRenderer = Renderer;
	EngineDisplay = Display;

	EngineLoader = EngineRenderer->GetLoader();
	EngineShaderProgram = EngineRenderer->GetShaderProgram();
}

void CEngine::InitCore(CRenderer* Renderer, CDisplay* Display)
{
	InitializeCoreModules(Renderer, Display);
	GetFunctionPointers();

	EngineDisplay->CreateDisplay();
	EngineRenderer->SetIsWireframeEnabled(false);
	EngineRenderer->InitializeMeshData();

	EngineMesh = EngineRenderer->GetLoader()->LoadMeshFromVao(EngineRenderer->GetMeshData());

	EngineRenderer->InitializeShaders();
	EngineRenderer->InitializeTextures();
}

void CEngine::MakeUIFloats(CEngineUI* UI)
{
	UI->InitializeIMGUI(EngineDisplay->GetWindow());
	setFloatElements(UI, new FPMap);

	float* color = new float[4];
	color[0] = 0.4f;
	color[1] = 0.6f;
	color[2] = 0.3f;
	color[3] = 1.0f;

	FloatPointerContainer.AddToBuffer("ColorData", color);
	addFloatElements(UI, "Color", color);
}

TUIDataContainer<float*>* CEngine::GetFloatPointerContainer()
{
	return &FloatPointerContainer;
}

void CEngine::ProccessInput(GLFWwindow* Window)
{
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, true);
	}
	else if (glfwGetKey(Window, GLFW_KEY_R) == GLFW_PRESS)
	{
		EngineRenderer->SetIsWireframeEnabled(true);
	}
	else if (glfwGetKey(Window, GLFW_KEY_T) == GLFW_PRESS)
	{
		EngineRenderer->SetIsWireframeEnabled(false);
	}
}

void CEngine::Update(CEngineUI* UI)
{
	float* color = FloatPointerContainer.GetDataFromBuffer("ColorData");

	ProccessInput(EngineDisplay->GetWindow());

	UI->CreateUIFrame();
	EngineRenderer->ClearScreen();

	EngineShaderProgram->StartShaderProgram();
	EngineShaderProgram->SetFourVectorUniform("uniform_color",
			color[0],
			color[1],
			color[2],
			color[3]
		);
	
	EngineRenderer->Render(EngineMesh);
	UI->Render("WINDOW", EngineDisplay->GetWindow());

	EngineShaderProgram->StopShaderProgram();
}

void CEngine::Close(CEngineUI* UI)
{
	EngineRenderer->GetShaderProgram()->CleanShaderProgram();
	EngineLoader->CleanUp();

	UI->CleanUpUI();
	delete UI;

	FreeLibrary(UIDLL);
}