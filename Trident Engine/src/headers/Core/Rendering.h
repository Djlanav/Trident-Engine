#pragma once

// ** Forward Declarations **
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

class CRenderer
{
private:
	bool isWireframeEnabled;

	CEngineUI* EngineUI;

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

public:
	CRenderer(CDisplay* Display, CLoader* Loader);

	void ClearScreen();

	void InitializeMeshData();
	void InitializeShaders();
	void InitializeTextures();

	void DynamicTextureLoad(CEngineUI* UI);

	void Render(CMesh* mesh);

	bool GetIsWireframeEnabled();
	void SetIsWireframeEnabled(bool Value);
	void SetUI(CEngineUI* UI);

	CShaderProgram* GetShaderProgram();
	CLoader* GetLoader();
	CShader* GetShader(uint32 GLBasedShader);
	SMeshData* GetMeshData();
	CTextureLoader* GetTextureLoader();
};