#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "Core/Typedefs.h"
#include "Core/Mesh.h"
#include "Core/Loader.h"
#include "Core/Shader.h"
#include "Core/Texturing.h"
#include "Core/FileIO.h"
#include "Plugins/Logger.h"
#include "Core/Display.h"
#include "Core/MainEngineUI.h"
#include "Core/Rendering.h"

CRenderer::CRenderer(CDisplay* Display, CLoader* Loader)
{
	this->Display = Display;
	this->Loader = Loader;
}

void CRenderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.4f, 0.6f, 1.0f);
}

void CRenderer::InitializeMeshData()
{
	FVector positions =
	{
		-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 0 Top left
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 1 Bottom left
		0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 2 Bottom right
		0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 0.0f, 1.0f, 1.0f  // 3 Top right
	};

	IVector indicies =
	{
		0, 1, 3,
		3, 1, 2
	};

	SMeshData* meshData = new SMeshData;
	meshData->PositionData = positions;
	meshData->Indicies = indicies;

	this->MeshData = meshData;
}

void CRenderer::InitializeShaders()
{
	VertexShaderCode = BufferedReader.WriteToBuffer("shaders/vertexShader.txt");
	VertexShader.InitShader(GL_VERTEX_SHADER, VertexShaderCode);

	FragmentShaderCode = BufferedReader.WriteToBuffer("shaders/fragmentShader.txt");
	FragmentShader.InitShader(GL_FRAGMENT_SHADER, FragmentShaderCode);

	ShaderProgram->SetShaders(&VertexShader, &FragmentShader);
	ShaderProgram->CreateShaderProgram();
}

void CRenderer::InitializeTextures()
{
	TextureLoader->LoadTextureData("res/grass.png", 256, 256, 3);
	TextureLoader->InitializeTexture(0);
}

void CRenderer::Render(CMesh* mesh)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	if (isWireframeEnabled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glDrawElements(GL_TRIANGLES, mesh->GetVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

bool CRenderer::GetIsWireframeEnabled()
{
	return isWireframeEnabled;
}

void CRenderer::SetIsWireframeEnabled(bool Value)
{
	isWireframeEnabled = Value;
}

CShaderProgram* CRenderer::GetShaderProgram()
{
	return ShaderProgram;
}

SMeshData* CRenderer::GetMeshData()
{
	return MeshData;
}

CLoader* CRenderer::GetLoader()
{
	return Loader;
}

CShader* CRenderer::GetShader(uint32 GLBasedShader)
{
	if (GLBasedShader == GL_VERTEX_SHADER)
	{
		return &VertexShader;
	}
	else if (GLBasedShader == GL_FRAGMENT_SHADER)
	{
		return &FragmentShader;
	}
}