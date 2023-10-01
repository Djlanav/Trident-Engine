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

// ** Custom Typedefs **
typedef std::vector<SVertexAttribPointer*> VAPVector;
typedef std::vector<CVertexBufferObject*> VBOVector;

// ** Classes **

class CLoader
{
private:
	VBOVector VertexBufferObjects;

public:
	CMesh* LoadMeshFromVao(SMeshData* MeshData);

	uint32 CreateVAO();

	void CreateVBO(FVector* DataForBuffer, int32 AttributeSize, int32 SpaceBetweenAttributes, const_voidptr Offset);
	void CreateEBO(IVector* IndiciesBufferData); // Indicies

	void CleanUp();
};

class CVertexBufferObject
{
private:
	uint32 VboID;

	FVector* Data;
	VAPVector AttributePointers;

	const_voidptr Offset;

public:
	CVertexBufferObject(FVector* Data);

public:
	void AddNewVertexAttribPointer(int32 LocationIndex, int32 AttributeSize, int32 Stride, const_voidptr Offset);
	void BindVertexAttribPointer(SVertexAttribPointer* VertexAttribPointer);

	void UnbindBuffer();

	VAPVector* GetAttributePointersVector();

	uint32 GetVboID();
	uint32* GetVboIDAsPointer();
};