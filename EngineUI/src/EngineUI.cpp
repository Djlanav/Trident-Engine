// EngineUI.cpp : Defines the exported functions for the DLL.
//

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include <windows.h>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Core/Typedefs.h"
#include "Core/MainEngineUI.h"

FPMap* CEngineUI::GetFloatUIElements()
{
	return FloatUIElements;
}

UIPMap* CEngineUI::GetUnsignedUIElements()
{
	return UnsignedIntegerUIElements;
}

void CEngineUI::SetFloatUIElements(FPMap* Map)
{
	FloatUIElements = Map;
}

void CEngineUI::SetUnsignedUIElements(UIPMap* Map)
{
	UnsignedIntegerUIElements = Map;
}

void CEngineUI::InitializeIMGUI(GLFWwindow* window)
{
	if (!glfwInit())
	{
		std::exit(-1);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();  (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void CEngineUI::CreateUIFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void CEngineUI::AddFloatUIElement(const String& Name, float* Element)
{
	FloatUIElements->insert({ Name, Element });
}

void CEngineUI::AddIntegerUIElement(const String& Name, uint32* Element)
{
	UnsignedIntegerUIElements->insert({ Name, Element });
}

void CEngineUI::Render(const String& Name)
{
	ImGui::Begin(Name.c_str());

	ImGui::Text("TESTING");
	
	ImGui::ColorEdit4("Quad Color", FloatUIElements->at("Color"));

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CEngineUI::CleanUpUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

// ** Normal Functions **
extern "C"
{
	CEngineUI* createUI()
	{
		return new CEngineUI();
	}

	FPMap* GetFloatUIElements(CEngineUI* UI)
	{
		return UI->GetFloatUIElements();
	}

	UIPMap* GetUnsignedUIElements(CEngineUI* UI)
	{
		return UI->GetUnsignedUIElements();
	}

	void SetFloatUIElements(CEngineUI* UI, FPMap* Map)
	{
		UI->SetFloatUIElements(Map);
	}

	void SetUnsignedUIElements(CEngineUI* UI, UIPMap* Map)
	{
		UI->SetUnsignedUIElements(Map);
	}

	void AddFloatUIElement(CEngineUI* UI, const String& Name, float* Element)
	{
		UI->AddFloatUIElement(Name, Element);
	}

	void AddIntegerUIElement(CEngineUI* UI, const String& Name, uint32* Element)
	{
		UI->AddIntegerUIElement(Name, Element);
	}
}