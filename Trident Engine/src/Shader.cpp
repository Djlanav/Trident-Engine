#include "Core/CommonHeaders.h"
#include "glad/glad.h"
#include "Core/Typedefs.h"
#include "Core/Module.h"
#include "Core/Shader.h"
#include "Plugins/Logger.h"

// ** CShaderProgram **
CShaderProgram::CShaderProgram(CShader& VertexShader, CShader& FragmentShader) 
	: VertexShader(VertexShader), FragmentShader(FragmentShader)
{}

void CShaderProgram::CreateShaderProgram()
{
	Program = glCreateProgram();

	glAttachShader(Program, VertexShader.GetShaderID());
	glAttachShader(Program, FragmentShader.GetShaderID());
	glLinkProgram(Program);

	CheckProgramLinkStatus();
}

void CShaderProgram::CheckProgramLinkStatus()
{
	CLogger logger;
	int32 success;
	char log[512];

	ELogStatus status;

	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		status = FAILURE;

		glGetProgramInfoLog(Program, 512, NULL, log);
		String sLog = "OpenGL Log: ";
		sLog.append(log);

		logger.Log("Program Linking Status:", &status, &sLog);
	}
	else
	{
		status = SUCCESS;
		logger.Log("Program Linking Status:", &status, nullptr);
		GetUniformLocations();
	}
}

void CShaderProgram::StartShaderProgram()
{
	glUseProgram(Program);
}

void CShaderProgram::StopShaderProgram()
{
	glUseProgram(0);
}

void CShaderProgram::CleanShaderProgram()
{
	glDetachShader(Program, VertexShader.GetShaderID());
	glDetachShader(Program, FragmentShader.GetShaderID());

	glDeleteShader(VertexShader.GetShaderID());
	glDeleteShader(FragmentShader.GetShaderID());

	glDeleteProgram(Program);
}

void CShaderProgram::SetShaders(CShader& VertexShader, CShader& FragmentShader)
{
	this->VertexShader = VertexShader;
	this->FragmentShader = FragmentShader;
}

void CShaderProgram::AddUniformLocation(const String& Name)
{
	const char* c_name = Name.c_str();
	int32 location = glGetUniformLocation(Program, c_name);

	UniformLocations.insert({ Name, location });
}

void CShaderProgram::GetUniformLocations()
{
	AddUniformLocation("uniform_color");
}

void CShaderProgram::SetFourVectorUniform(const String& Name, float x, float y, float z, float w)
{
	glUniform4f(UniformLocations.at(Name), x, y, z, w);
}
// ** End CShaderProgram **

// ** CShader **

void CShader::InitShader(uint32 Type, String* sShaderCode)
{
	const char* code = sShaderCode->c_str();
	shaderType = Type;

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &code, NULL);
	glCompileShader(shaderID);

	CheckShaderCompileStatus();
}

void CShader::CheckShaderCompileStatus()
{
	int32 success;
	char Log[512];

	ELogStatus status;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		status = FAILURE;

		glGetShaderInfoLog(shaderID, 512, NULL, Log);
		String sLog = "OpenGL Log: ";
		sLog.append(Log);

		if (shaderType == GL_VERTEX_SHADER)
		{
			CLogger::Log("Vertex Shader Compilation Status:", &status, &sLog);
		}
		else if (shaderType == GL_FRAGMENT_SHADER)
		{
			CLogger::Log("Fragment Shader Compilation Status:", &status, &sLog);
		}
	}
	else
	{
		status = SUCCESS;
		if (shaderType == GL_VERTEX_SHADER)
		{
			CLogger::Log("Vertex Shader Compilation Status:", &status, nullptr);
		}
		else if (shaderType == GL_FRAGMENT_SHADER)
		{
			CLogger::Log("Fragment Shader Compilation Status:", &status, nullptr);
		}
	}
}

uint32 CShader::GetShaderID()
{
	return shaderID;
}

uint32 CShader::GetShaderType()
{
	return shaderType;
}

void CShader::SetShaderID(uint32 ID)
{
	shaderID = ID;
}

void CShader::SetShaderType(uint32 Type)
{
	shaderType = Type;
}

// ** End CShader