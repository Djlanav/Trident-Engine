#pragma once

class CMesh
{
private:
	uint32_t VaoID;
	uint32_t VertexCount;

public:
	// ** Constructor **
	CMesh(uint32_t VaoID, uint32_t VertexCount);

	// ** Getters **
	uint32_t GetVaoID();
	uint32_t GetVertexCount();

	// ** Setters **
	void SetVaoID(uint32_t id);
	void SetVertexCount(uint32_t count);
};