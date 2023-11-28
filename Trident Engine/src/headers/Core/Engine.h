#pragma once

class CModule;
class CMesh;
class CRenderer;
class CDisplay;
class CLoader;
class CShaderProgram;

#include "Core/UIDataContainer.h"

// ** Classes **

class CEngine : public CModule
{
private:
	CEditorUI& EditorUI;
	CRenderer& EngineRenderer;
	CDisplay& EngineDisplay;
	CLoader& EngineLoader;

	CMesh* EngineMesh;
	CShaderProgram* EngineShaderProgram;

	TUIDataContainer<float*> FloatPointerContainer;

private:
	void ProccessInput(GLFWwindow* Window);
	void InitializeCoreModules(CRenderer& Renderer, CDisplay& Display);

public:
	void InitCore(CRenderer& Renderer, CDisplay& Display);
	void Update(CEditorUI* UI);
	void Close(CEditorUI* UI);

	void MakeUIFloats(CEditorUI* UI);

	TUIDataContainer<float*>* GetFloatPointerContainer();
};