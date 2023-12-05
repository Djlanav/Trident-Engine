#pragma once

class CModule;
class CMesh;
class CDisplay;
class CLoader;
class CShaderProgram;
class CRenderer;

#include "Core/UIDataContainer.h"

// ** Classes **

class CEngine : public CModule
{
private:
	CEditorUI EditorUI;

	CRenderer& EngineRenderer;
	
	CDisplay& EngineDisplay;
	
	CLoader& EngineLoader;
	CShaderProgram& EngineShaderProgram;

	std::shared_ptr<CMesh> EngineMesh;
	TUIDataContainer<std::shared_ptr<float[]>> FloatPointerContainer;

private:
	void ProccessInput(GLFWwindow* Window);

public:
	CEngine(CRenderer& Renderer);
	void Update();
	void Close();

	void MakeUIFloats();

	TUIDataContainer<std::shared_ptr<float[]>>& GetFloatPointerContainer();
};