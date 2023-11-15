#pragma once

class CModule;
class CMesh;
class CRenderer;
class CDisplay;
class CLoader;
class CShaderProgram;

#include "Core/UIDataContainer.h"

class CEngine : public CModule
{
private:
	CRenderer* EngineRenderer;
	CDisplay* EngineDisplay;
	CMesh* EngineMesh;
	CShaderProgram* EngineShaderProgram;
	CLoader* EngineLoader;

	TUIDataContainer<float*> FloatPointerContainer;

private:
	void ProccessInput(GLFWwindow* Window);
	void GetFunctionPointers();
	void InitializeCoreModules(CRenderer* Renderer, CDisplay* Display);

private:
	HINSTANCE UIDLL;

public:

	CreateObjectFn createEngineUI;

	GetFPMapFn getFloatElements;
	GetUIPMapFn getUnsignedElements;

	SetFPMapFn setFloatElements;
	SetUIPMapFn setUnsignedElements;

	AddFloatElementsFn addFloatElements;
	AddUnsignedIntElementsFn addIntegerElements;

public:
	void InitCore(CRenderer* Renderer, CDisplay* Display);
	void Update(CEngineUI* UI);
	void Close(CEngineUI* UI);

	void MakeUIFloats(CEngineUI* UI);

	TUIDataContainer<float*>* GetFloatPointerContainer();
};