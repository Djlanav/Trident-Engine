#pragma once

class CMesh;
class CRenderer;
class CDisplay;
class CLoader;

class CEngine
{
private:
	CRenderer* EngineRenderer;
	CDisplay* EngineDisplay;
	CLoader* EngineLoader;
	CMesh* EngineMesh;

private:
	void ProccessInput();
	void GetFunctionPointers();
	void InitializeCoreModules(CRenderer* Renderer, CDisplay* Display, CLoader* Loader);

public:
	HINSTANCE UIDLL;

	CreateObjectFn createEngineUI;

	GetFPMapFn getFloatElements;
	GetUIPMapFn getUnsignedElements;

	SetFPMapFn setFloatElements;
	SetUIPMapFn setUnsignedElements;

	AddFloatElementsFn addFloatElements;
	AddUnsignedIntElementsFn addIntegerElements;

public:
	void InitCore(CRenderer* Renderer, CDisplay* Display, CLoader* Loader);
	void Update(CEngineUI* UI);
	void Close();
};