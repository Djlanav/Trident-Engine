// EngineUI.cpp : Defines the exported functions for the DLL.
//

#include "Core/CommonHeaders.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

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

String* CEngineUI::OpenFileDialog(GLFWwindow* window)
{
	OPENFILENAMEA ofn;
	auto* ofnptr = &ofn;
	CHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window(window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(CHAR);
	ofn.lpstrFilter = "Image Files (*.bmp;*.jpg;*.png;*.gif)\0*.bmp;*.jpg;*.png;*.gif\0All Files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		String* fileName = nullptr;

		if (FileRetrieved == nullptr)
		{
			fileName = new String;
			*fileName = ofn.lpstrFile;
			
			return fileName;
		}
		else if (FileRetrieved != nullptr)
		{
			delete FileRetrieved;

			fileName = new String;
			*fileName = ofn.lpstrFile;

			return fileName;
		}
	}
	
	return nullptr;
}

String* CEngineUI::GetFileDialogResult()
{
	return FileRetrieved;
}

void CEngineUI::BeginImGUI(const String& WindowName)
{
	ImGui::Begin(WindowName.c_str());
}

void CEngineUI::EndImGUI()
{
	ImGui::End();
}

void CEngineUI::AddTextIMGUI(const String& Text, ...)
{
	va_list args;
	const char* text_c = Text.c_str();
	ImGui::Text(text_c, args);
}

void CEngineUI::Render(const String& Name, GLFWwindow* window)
{
	ImGui::Begin(Name.c_str());

	// ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	
	ImGui::ColorEdit4("Quad Color", FloatUIElements->at("Color"));
	if (ImGui::Button("Select Texture"))
	{
		FileRetrieved = OpenFileDialog(window);
	}

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

extern "C"
{
	ENGINEUI_API CEngineUI* createUI()
	{
		return new CEngineUI;
	}
}