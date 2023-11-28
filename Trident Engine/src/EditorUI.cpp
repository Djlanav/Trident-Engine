#include "Core/CommonHeaders.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "Core/Typedefs.h"
#include "Core/EditorUI.h"

FPMap& CEditorUI::GetFloatUIElements()
{
	return FloatUIElements;
}

UIPMap& CEditorUI::GetUnsignedUIElements()
{
	return UnsignedIntegerUIElements;
}

void CEditorUI::InitializeIMGUI(GLFWwindow* window)
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

void CEditorUI::CreateUIFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void CEditorUI::AddFloatUIElement(const String& Name, float* Element)
{
	FloatUIElements.insert({ Name, Element });
}

void CEditorUI::AddIntegerUIElement(const String& Name, uint32* Element)
{
	UnsignedIntegerUIElements.insert({ Name, Element });
}

void CEditorUI::OpenFileDialog(GLFWwindow* window)
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
		if (FileRetrieved.empty())
		{
			FileRetrieved = ofn.lpstrFile;
		}
		else if (!FileRetrieved.empty())
		{
			FileRetrieved.clear();
			FileRetrieved = ofn.lpstrFile;
		}
	}
}

void CEditorUI::SetFileRetrieved(std::unique_ptr<String> retrieved)
{
	FileRetrieved = *retrieved;
}

String& CEditorUI::GetFileDialogResult()
{
	return FileRetrieved;
}

void CEditorUI::UIBegin(const String& WindowName)
{
	ImGui::Begin(WindowName.c_str());
}

void CEditorUI::UIBeginChild(const String& ChildName)
{
	ImGui::BeginChild(ChildName.c_str());
}

bool CEditorUI::UIButton(const String& Text)
{
	return ImGui::Button(Text.c_str());
}

void CEditorUI::UIEnd()
{
	ImGui::End();
}

void CEditorUI::UIEndChild()
{
	ImGui::EndChild();
}

void CEditorUI::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CEditorUI::CleanUpUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}