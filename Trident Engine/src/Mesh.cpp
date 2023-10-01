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

// ** Constructor **
CMesh::CMesh(uint32_t VaoID, uint32_t VertexCount)
{
	this->VaoID = VaoID;
	this->VertexCount = VertexCount;
}

// ** Getters **
uint32_t CMesh::GetVaoID()
{
	return VaoID;
}

uint32_t CMesh::GetVertexCount()
{
	return VertexCount;
}

// ** Setters **
void CMesh::SetVaoID(uint32_t id)
{
	this->VaoID = id;
}

void CMesh::SetVertexCount(uint32_t count)
{
	this->VertexCount = count;
}