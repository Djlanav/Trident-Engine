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
	CDisplay& Display;
	CLoader& Loader;

	std::shared_ptr<SMeshData> MeshData;

	CShaderProgram ShaderProgram;

	CTextureLoader TextureLoader;
	CBufferedReader BufferedReader;

	CShader VertexShader;
	CShader FragmentShader;

	String* VertexShaderCode;
	String* FragmentShaderCode;

public:
	CRenderer();
	CRenderer(CDisplay& Display, CLoader& Loader, CEditorUI& UI);

	void ClearScreen();

	void InitializeMeshData();
	void InitializeShaders();

	// Separate into two functions ^^

	void LoadTextureFromFile();

	void Render(std::shared_ptr<CMesh> mesh);
	void Interface();

	bool GetIsWireframeEnabled();
	void SetIsWireframeEnabled(bool Value);

	CShaderProgram& GetShaderProgram();
	std::optional<CShader> GetShader(uint32 GLBasedShader);

	CLoader& GetLoader();
	std::shared_ptr<SMeshData> GetMeshData();


	CTextureLoader& GetTextureLoader();
};