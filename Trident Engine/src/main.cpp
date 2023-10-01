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
#include "Core/Rendering.h"
#include "Core/Display.h"

#define CHECK_FUNCTION_POINTERS 0

void process_input(GLFWwindow* window, CRenderer* renderer);

int main()
{
	HINSTANCE uiDLL = LoadLibrary(TEXT("EngineUI.dll"));
	ELogStatus uiDllStatus;

	if (uiDLL == NULL)
	{
		std::exit(-1);
	}
	else
	{
		uiDllStatus = SUCCESS;
		CLogger::Log("UI DLL Status:", &uiDllStatus, nullptr);
	}

	CreateObjectFn createEngineUI = (CreateObjectFn)GetProcAddress(uiDLL, "createUI");
	
	GetFPMapFn getFloatElements = (GetFPMapFn)GetProcAddress(uiDLL, "GetFloatUIElements");
	GetUIPMapFn getUnsignedElements = (GetUIPMapFn)GetProcAddress(uiDLL, "GetUnsignedUIElements");
	
	SetFPMapFn setFloatElements = (SetFPMapFn)GetProcAddress(uiDLL, "SetFloatUIElements");
	SetUIPMapFn setUnsignedElements = (SetUIPMapFn)GetProcAddress(uiDLL, "SetUnsignedUIElements");
	
	AddFloatElementsFn addFloatElements = (AddFloatElementsFn)GetProcAddress(uiDLL, "AddFloatUIElement");
	AddUnsignedIntElementsFn addIntegerElements = (AddUnsignedIntElementsFn)GetProcAddress(uiDLL, "AddIntegerUIElement");

	ELogStatus functionPointerStatus = SUCCESS;

#if CHECK_FUNCTION_POINTERS == 1
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

	CDisplay display("Trident Engine (OpenGL 4.5)", 1024, 780);
	display.CreateDisplay();

	CRenderer renderer(&display);
	renderer.SetIsWireframeEnabled(false);

	CLoader loader;

	renderer.InitializeMeshData();
	CMesh* mesh = loader.LoadMeshFromVao(renderer.GetMeshData());

	CEngineUI* engineUI = createEngineUI();

	engineUI->InitializeIMGUI(display.GetWindow());
	setFloatElements(engineUI, new FPMap);

	float color[] = { 0.4f, 0.6f, 0.3f, 1.0f };
	addFloatElements(engineUI, "Color", color);

	renderer.InitializeShaders();
	renderer.InitializeTextures();

	while (!glfwWindowShouldClose(display.GetWindow()))
	{
		process_input(display.GetWindow(), &renderer);

		engineUI->CreateUIFrame();
		renderer.ClearScreen();

		renderer.GetShaderProgram()->StartShaderProgram();

		renderer.GetShaderProgram()->SetFourVectorUniform("uniform_color", color[0], color[1], color[2], color[3]);
		renderer.Render(mesh);

		renderer.GetShaderProgram()->StopShaderProgram();

		// UI Render
		engineUI->Render("WINDOW");

		glfwSwapBuffers(display.GetWindow());
		glfwPollEvents();
	}
	renderer.GetShaderProgram()->CleanShaderProgram();
	loader.CleanUp();

	engineUI->CleanUpUI();
	delete engineUI;
	FreeLibrary(uiDLL);

	glfwTerminate();
	return 0;
}

void process_input(GLFWwindow* window, CRenderer* renderer)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		renderer->SetIsWireframeEnabled(true);
	}
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		renderer->SetIsWireframeEnabled(false);
	}
}