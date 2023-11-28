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
class CEditorUI;
class CDisplay;
struct SMeshData;
// ** End **

class CRenderer : public CModule
{
private:
	SVector DLLNameVector;

private:
	bool isWireframeEnabled;

	CEditorUI& EditorUI;

	CLoader& Loader;
	CShaderProgram ShaderProgram;

	CTextureLoader TextureLoader;
	CBufferedReader BufferedReader;

	SMeshData* MeshData;

	String* VertexShaderCode;
	String* FragmentShaderCode;

	CDisplay& Display;

	CShader VertexShader;
	CShader FragmentShader;

public:
	CRenderer(CDisplay& Display, CLoader& Loader, CEditorUI& UI);

	void ClearScreen();

	void InitializeMeshData();
	void InitializeShaders();

	// Separate into two functions ^^

	void LoadTextureFromFile();

	void Render(CMesh* mesh);
	void Interface();

	bool GetIsWireframeEnabled();
	void SetIsWireframeEnabled(bool Value);

	CShaderProgram* GetShaderProgram();
	
	CLoader& GetLoader();
	
	CShader* GetShader(uint32 GLBasedShader);
	SMeshData* GetMeshData();
	CTextureLoader* GetTextureLoader();
};