#pragma once

// ** Forward Declarations **
class CShader;
// ** End **

class CShaderProgram
{
private:
	uint32 Program;

	CShader* VertexShader;
	CShader* FragmentShader;

public:
	I32HashMap UniformLocations;

public:
	void CreateShaderProgram();
	void CheckProgramLinkStatus();

	void StartShaderProgram();
	void StopShaderProgram();

	void CleanShaderProgram();

	void SetShaders(CShader* VertexShader, CShader* FragmentShader);

	void AddUniformLocation(const String& Name);
	void GetUniformLocations();

	// ** Uniform Setters **
	void SetFourVectorUniform(const String& Name, float x, float y, float z, float w);
};

class CShader
{
private:
	uint32 shaderID;
	uint32 shaderType;

public:

	void InitShader(uint32 Type, String* sShaderCode);
	void CheckShaderCompileStatus();

	uint32 GetShaderID();
	uint32 GetShaderType();

	void SetShaderID(uint32 ID);
	void SetShaderType(uint32 Type);
};