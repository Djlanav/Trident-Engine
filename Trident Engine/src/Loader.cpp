#include "Plugins/imgui/imgui.h"
#include "Plugins/imgui/imgui_impl_glfw.h"
#include "Plugins/imgui/imgui_impl_opengl3.h"

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
#include "Core/Rendering.h"

CMesh* CLoader::LoadMeshFromVao(SMeshData* MeshData)
{
	uint32 vao = CreateVAO();

	CreateVBO(&MeshData->PositionData, 3, 6 * sizeof(float), (void*)0);
	CreateEBO(&MeshData->Indicies);

	CMesh* Mesh = new CMesh(vao, MeshData->Indicies.size());
	return Mesh;
}

uint32 CLoader::CreateVAO()
{
	uint32 vaoID = 0;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	return vaoID;
}

void CLoader::CreateVBO(FVector* DataForBuffer, int32 AttributeSize, int32 SpaceBetweenAttributes, const_voidptr Offset)
{
	int32 providedStride = 8 * sizeof(float);

	CVertexBufferObject* VBO = new CVertexBufferObject(DataForBuffer);

	VBO->AddNewVertexAttribPointer(0, 3, providedStride, (const_voidptr)0);
	VBO->AddNewVertexAttribPointer(1, 3, providedStride, (const_voidptr)(3 * sizeof(float)));
	VBO->AddNewVertexAttribPointer(2, 2, providedStride, (const_voidptr)(6 * sizeof(float)));
	
	VBO->BindVertexAttribPointer(VBO->GetAttributePointersVector()->at(0));
	VBO->BindVertexAttribPointer(VBO->GetAttributePointersVector()->at(1));
	VBO->BindVertexAttribPointer(VBO->GetAttributePointersVector()->at(2));

	VBO->UnbindBuffer();

	VertexBufferObjects.push_back(VBO);
}

void CLoader::CreateEBO(IVector* IndiciesBufferData)
{
	uint32 eboID = 0;
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32) * IndiciesBufferData->size(), IndiciesBufferData->data(), GL_STATIC_DRAW);
}

void CLoader::CleanUp()
{
	for (auto VBO : VertexBufferObjects)
	{
		glDeleteBuffers(1, VBO->GetVboIDAsPointer());
		delete VBO;
	}
}

// ** CVertexBufferObject **
CVertexBufferObject::CVertexBufferObject(FVector* Data) 
	: Offset(nullptr), AttributePointers()
{
	this->Data = Data;
	VboID = 0;

	glGenBuffers(1, &VboID);
	glBindBuffer(GL_ARRAY_BUFFER, VboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Data->size(), Data->data(), GL_STATIC_DRAW);
}

void CVertexBufferObject::AddNewVertexAttribPointer(int32 LocationIndex, int32 AttributeSize, int32 Stride, const_voidptr Offset)
{
	SVertexAttribPointer* attribPointer = new SVertexAttribPointer;
	attribPointer->LocationIndex = LocationIndex;
	attribPointer->AttributeSize = AttributeSize;
	attribPointer->Stride = Stride;
	attribPointer->Offset = Offset;

	AttributePointers.push_back(attribPointer);
}

VAPVector* CVertexBufferObject::GetAttributePointersVector()
{
	return &AttributePointers;
}

void CVertexBufferObject::BindVertexAttribPointer(SVertexAttribPointer* VertexAttribPointer)
{
	glVertexAttribPointer(VertexAttribPointer->LocationIndex,
		VertexAttribPointer->AttributeSize, GL_FLOAT, GL_FALSE, VertexAttribPointer->Stride,
		VertexAttribPointer->Offset);
}

void CVertexBufferObject::UnbindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32 CVertexBufferObject::GetVboID()
{
	return VboID;
}

uint32* CVertexBufferObject::GetVboIDAsPointer()
{
	return &VboID;
}