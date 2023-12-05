#include "Core/CommonHeaders.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core/Typedefs.h"
#include "Core/Module.h"
#include "Core/Mesh.h"
#include "Core/Loader.h"
#include "Core/Shader.h"
#include "Core/Texturing.h"
#include "Core/FileIO.h"
#include "Plugins/Logger.h"
#include "Core/Rendering.h"

#define BIND_ATTRIB_PTR_LOOPS 3

std::shared_ptr<CMesh> CLoader::LoadMeshFromVao(std::shared_ptr<SMeshData> MeshData)
{
	uint32 vao = CreateVAO();

	CreateVBO(MeshData->PositionData, 3, 6 * sizeof(float), (void*)0);
	CreateEBO(MeshData->Indicies);

	std::shared_ptr<CMesh> Mesh = std::make_shared<CMesh>(vao, MeshData->Indicies.size());
	return Mesh;
}

uint32 CLoader::CreateVAO()
{
	uint32 vaoID = 0;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	return vaoID;
}

void CLoader::CreateVBO(FVector& DataForBuffer, int32 AttributeSize, int32 SpaceBetweenAttributes, const_voidptr Offset)
{
	int32 providedStride = 8 * sizeof(float);

	std::unique_ptr<CVertexBufferObject> VBO = std::make_unique<CVertexBufferObject>(DataForBuffer);

	VBO->AddNewVertexAttribPointer(0, 3, providedStride, (const_voidptr)0);
	VBO->AddNewVertexAttribPointer(1, 3, providedStride, (const_voidptr)(3 * sizeof(float)));
	VBO->AddNewVertexAttribPointer(2, 2, providedStride, (const_voidptr)(6 * sizeof(float)));
	
	for (uint32 i = 0; i < BIND_ATTRIB_PTR_LOOPS; i++)
	{
		VBO->BindVertexAttribPointer(i);
	}

	VBO->UnbindBuffer();

	VertexBufferObjects.push_back(std::move(VBO));
}

void CLoader::CreateEBO(IVector& IndiciesBufferData)
{
	uint32 eboID = 0;
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32) * IndiciesBufferData.size(), IndiciesBufferData.data(), GL_STATIC_DRAW);
}

void CLoader::CleanUp()
{
	for (std::unique_ptr<CVertexBufferObject>& VBO : VertexBufferObjects)
	{
		glDeleteBuffers(1, VBO->GetVboIDAsRawPointer());
	}
}

// ** CVertexBufferObject **
CVertexBufferObject::CVertexBufferObject(FVector& Data) 
	: Data(Data), Offset(nullptr), AttributePointers()
{
	VboID = 0;

	glGenBuffers(1, &VboID);
	glBindBuffer(GL_ARRAY_BUFFER, VboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Data.size(), Data.data(), GL_STATIC_DRAW);
}

void CVertexBufferObject::AddNewVertexAttribPointer(int32 LocationIndex, int32 AttributeSize, int32 Stride, const_voidptr Offset)
{
	std::unique_ptr<SVertexAttribPointer> attribPointer = std::make_unique<SVertexAttribPointer>();
	attribPointer->LocationIndex = LocationIndex;
	attribPointer->AttributeSize = AttributeSize;
	attribPointer->Stride = Stride;
	attribPointer->Offset = Offset;

	AttributePointers.push_back(std::move(attribPointer));
}

VAPVector& CVertexBufferObject::GetAttributePointersVector()
{
	return AttributePointers;
}

void CVertexBufferObject::BindVertexAttribPointer(uint32 Index)
{
	std::unique_ptr<SVertexAttribPointer> VertexAttribPointer = std::move(AttributePointers[Index]);

	glVertexAttribPointer(VertexAttribPointer->LocationIndex,
		VertexAttribPointer->AttributeSize, GL_FLOAT, GL_FALSE, VertexAttribPointer->Stride,
		VertexAttribPointer->Offset);

	AttributePointers[Index] = std::move(VertexAttribPointer);
}

void CVertexBufferObject::UnbindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32 CVertexBufferObject::GetVboID()
{
	return VboID;
}

uint32& CVertexBufferObject::GetVboIDAsReference()
{
	return VboID;
}

uint32* CVertexBufferObject::GetVboIDAsRawPointer()
{
	return &VboID;
}