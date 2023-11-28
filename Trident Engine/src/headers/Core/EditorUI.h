#pragma once

using FPMap = std::unordered_map<String, float*>;
using UIPMap = std::unordered_map<String, uint32*>;


class CEditorUI
{
private:
	FPMap FloatUIElements;
	UIPMap UnsignedIntegerUIElements;
	String FileRetrieved;

public:
	void InitializeIMGUI(GLFWwindow* window);

	void CreateUIFrame();
	void Render();

	void CleanUpUI();

	void AddFloatUIElement(const String& Name, float* Element);
	void AddIntegerUIElement(const String& Name, uint32* Element);

	FPMap& GetFloatUIElements();
	UIPMap& GetUnsignedUIElements();

	void OpenFileDialog(GLFWwindow* window);

	void SetFileRetrieved(std::unique_ptr<String> retrieved);

	String& GetFileDialogResult();

public: // ImGUI interfacing
	void UIBegin(const String& WindowName);
	void UIBeginChild(const String& ChildName);

	bool UIButton(const String& Text);

	void UIEnd();
	void UIEndChild();
};