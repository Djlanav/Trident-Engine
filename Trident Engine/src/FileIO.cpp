#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <fstream>
#include "Core/Typedefs.h"
#include "Core/Mesh.h"
#include "Core/Loader.h"
#include "Core/Shader.h"
#include "Core/Texturing.h"
#include "Core/FileIO.h"
#include "Plugins/Logger.h"
#include "Core/Rendering.h"

String* CBufferedReader::WriteToBuffer(const String& FilePath)
{
	ClearBuffer();

	std::ifstream file(FilePath);

	if (file.is_open())
	{
		String line;
		while (std::getline(file, line))
		{
			Buffer.append(line).append("\n");
		}
	}

	file.close();
	return &Buffer;
}

void CBufferedReader::ClearBuffer()
{
	ELogStatus status;

	if (!Buffer.empty())
	{
		Buffer.clear();
		status = SUCCESS;
		CLogger::Log("Cleared Buffer", &status, nullptr);
	}
	else
	{
		status = WARNING;
		CLogger::Log("Attempted to clear empty buffer!", &status, nullptr);
	}
}

void CBufferedReader::AppendCharToBuffer(char Letter)
{
	Buffer.append(&Letter);
}

void CBufferedReader::AppendStringToBuffer(const String& AppendingString)
{
	Buffer.append(AppendingString);
}

String* CBufferedReader::GetBufferData()
{
	return &Buffer;
}