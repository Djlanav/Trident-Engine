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
	CEditorUI EditorUI;
	CRenderer EngineRenderer;
	
	CDisplay EngineDisplay;
	
	CLoader& EngineLoader;
	CShaderProgram& EngineShaderProgram;

	std::shared_ptr<CMesh> EngineMesh;

	TUIDataContainer<float*> FloatPointerContainer;

private:
	void ProccessInput(GLFWwindow* Window);
	void InitializeCoreModules(std::unique_ptr<CRenderer> Renderer, std::unique_ptr<CDisplay> Display);

public:
	CEngine();

	void InitCore(std::unique_ptr<CRenderer> Renderer, std::unique_ptr<CDisplay> Display);
	void Update();
	void Close();

	void MakeUIFloats();

	TUIDataContainer<float*>* GetFloatPointerContainer();
};