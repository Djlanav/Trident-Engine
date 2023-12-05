#pragma once

// ** Forward Delcarations **
class CMesh;
class CVertexBufferObject;
struct SVertexAttribPointer;

struct SVertexAttribPointer
{
	int32 LocationIndex;
	int32 AttributeSize;
	int32 Stride;

	const_voidptr Offset;
};

// ** Structs **
struct SMeshData
{
	FVector PositionData;
	IVector Indicies;
};

// Using statements
using VAPVector = std::vector<std::unique_ptr<SVertexAttribPointer>>;
using VBOVector = std::vector<std::unique_ptr<CVertexBufferObject>>;

// ** Classes **

class CLoader
{
private:
	VBOVector VertexBufferObjects;

public:
	std::shared_ptr<CMesh> LoadMeshFromVao(std::shared_ptr<SMeshData> MeshData);

	uint32 CreateVAO();

	void CreateVBO(FVector& DataForBuffer, int32 AttributeSize, int32 SpaceBetweenAttributes, const_voidptr Offset);
	void CreateEBO(IVector& IndiciesBufferData); // Indicies

	void CleanUp();
};

class CVertexBufferObject
{
private:
	uint32 VboID;

	FVector& Data;
	VAPVector AttributePointers;

	const_voidptr Offset;

public:
	CVertexBufferObject(FVector& Data);

public:
	void AddNewVertexAttribPointer(int32 LocationIndex, int32 AttributeSize, int32 Stride, const_voidptr Offset);
	void BindVertexAttribPointer(uint32 Index);

	void UnbindBuffer();

	VAPVector& GetAttributePointersVector();

	uint32 GetVboID();
	uint32& GetVboIDAsReference();
	uint32* GetVboIDAsRawPointer();
};