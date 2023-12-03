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

	std::unique_ptr<CLoader> Loader;

	std::shared_ptr<CEditorUI> EditorUI;
	std::shared_ptr<SMeshData> MeshData;
	std::shared_ptr<CDisplay> Display;

	CShaderProgram ShaderProgram;

	CTextureLoader TextureLoader;
	CBufferedReader BufferedReader;

	CShader VertexShader;
	CShader FragmentShader;

	String* VertexShaderCode;
	String* FragmentShaderCode;

public:
	CRenderer();
	CRenderer(std::shared_ptr<CDisplay> Display, std::unique_ptr<CLoader> Loader, std::shared_ptr<CEditorUI> UI);

	void ClearScreen();

	void InitializeMeshData();
	void InitializeShaders();

	// Separate into two functions ^^

	void LoadTextureFromFile();

	void Render(CMesh* mesh);
	void Interface();

	bool GetIsWireframeEnabled();
	void SetIsWireframeEnabled(bool Value);

	CShaderProgram& GetShaderProgram();
	CShader& GetShader(uint32 GLBasedShader);

	CLoader& GetLoader();
	std::shared_ptr<SMeshData> GetMeshData();


	CTextureLoader& GetTextureLoader();
};