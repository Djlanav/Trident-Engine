#pragma once

// ** Forward Declarations **
class CEngine;
class CModule;
class CSubModule;
class CLoader;
class CShader;
class CShaderProgram;
class CTextureLoader;
class CBufferedReader;
class CMesh;
class CUI;
class CEngineUI;
class CDisplay;
struct SMeshData;
// ** End **

// ** Function Pointer **
typedef String* (*func_ptr_one_arg)(CEngineUI* UI);

class CRenderer : public CModule
{
private:
	SVector DLLNameVector;

private:
	bool isWireframeEnabled;

	CEngineUI* EditorUI;

	CLoader* Loader;
	CShaderProgram ShaderProgram;

	CTextureLoader TextureLoader;
	CBufferedReader BufferedReader;

	SMeshData* MeshData;

	String* VertexShaderCode;
	String* FragmentShaderCode;

	CDisplay* Display;

	CShader VertexShader;
	CShader FragmentShader;

private:
	func_ptr_one_arg getFDResult;

public:
	CRenderer(CDisplay* Display, CLoader* Loader);

	void ClearScreen();

	void InitializeMeshData();
	void InitializeShaders();
	void InitializeTextures();

	void GetFunctionPointers();

	void DynamicTextureLoad();

	void Render(CMesh* mesh);
	void Interface();

	bool GetIsWireframeEnabled();
	void SetIsWireframeEnabled(bool Value);
	void SetUI(CEngineUI* UI);

	CShaderProgram* GetShaderProgram();
	CLoader* GetLoader();
	CShader* GetShader(uint32 GLBasedShader);
	SMeshData* GetMeshData();
	CTextureLoader* GetTextureLoader();
};