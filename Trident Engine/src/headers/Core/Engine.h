#pragma once

class CModule;
class CMesh;
class CRenderer;
class CDisplay;
class CLoader;
class CShaderProgram;

#include "Core/UIDataContainer.h"

// ** Function Pointers **
typedef void (*func_ptr_three_A)(CEngineUI*, const String&, float*);
typedef void (*func_ptr_two_A)(CEngineUI* UI, FPMap* Map);
typedef CEngineUI* (*func_ptr_empty_ui_ret)();

// ** Classes **

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
	func_ptr_empty_ui_ret createEngineUI;
	func_ptr_two_A setFloatElements;
	func_ptr_three_A addFloatElements;

public:
	void InitCore(CRenderer* Renderer, CDisplay* Display);
	void Update(CEngineUI* UI);
	void Close(CEngineUI* UI);

	void MakeUIFloats(CEngineUI* UI);

	TUIDataContainer<float*>* GetFloatPointerContainer();
};