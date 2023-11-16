#include "Core/CommonHeaders.h"

#include "glad/glad.h"
#include "Core/Typedefs.h"
#include "Core/Module.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Plugins/stb_image.h"

#include "Core/Texturing.h"
#include "Plugins/Logger.h"

// ** CTexture **

void CTexture::Make(int32 Width, int32 Height, int32 Channels)
{
	TextureWidth = Width;
	TextureHeight = Height;
	NumberOfChannels = Channels;
}

String* CTexture::GetImageName()
{
	return &sImageName;
}

uint8* CTexture::GetImageData()
{
	return ImageData;
}

int32 CTexture::GetWidth()
{
	return TextureWidth;
}

int32 CTexture::GetHeight()
{
	return TextureHeight;
}

int32 CTexture::GetNumberOfChannels()
{
	return NumberOfChannels;
}

uint32 CTexture::GetTextureID()
{
	return TextureID;
}

void CTexture::SetImageName(const String& Name)
{
	sImageName = Name;
}

void CTexture::SetImageData(uint8* Data)
{
	ImageData = Data;
}

void CTexture::SetWidth(uint32 NewWidth)
{
	TextureWidth = NewWidth;
}

void CTexture::SetHeight(uint32 NewHeight)
{
	TextureHeight = NewHeight;
}

void CTexture::SetChannels(uint32 NewNumber)
{
	NumberOfChannels = NewNumber;
}

void CTexture::SetTextureID(uint32 NewID)
{
	TextureID = NewID;
}

// ** CTextureLoader **

void CTextureLoader::LoadTextureData(const String& Name)
{
	CTexture* texture = new CTexture();
	ELogStatus status;

	int32 w;
	int32 h;
	int32 c;

	uint8* data = stbi_load(Name.c_str(), &w, &h, &c, 0);
	texture->Make(w, h, c);

	texture->SetImageData(data);
	texture->SetImageName(Name);
	if (texture->GetImageData() == nullptr || data == nullptr)
	{
		status = FAILURE;
		CLogger::Log("Texture Data Loading:", &status, nullptr);
	}
	else
	{
		status = SUCCESS;
		CLogger::Log("Texture Data Loading:", &status, nullptr);
	}

	Textures.push_back(texture);
}

void CTextureLoader::SetTextureParameters(int32 MipMapLevel, int32 OpenGLFormat, 
	int32 ImageWidth, int32 ImageHeight, int32 Border, int32 ImageFormat, uint8* Data)
{
	glTexImage2D(GL_TEXTURE_2D, MipMapLevel, OpenGLFormat, ImageWidth, ImageHeight, Border,
		ImageFormat, GL_UNSIGNED_BYTE, Data);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void CTextureLoader::InitializeTexture(uint32 Index)
{
	uint32 id = Textures.at(Index)->GetTextureID();
	CTexture* texturePointer = Textures.at(Index);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	SetTextureParameters(0, GL_RGB, texturePointer->GetWidth(), texturePointer->GetHeight(),
		0, GL_RGB, texturePointer->GetImageData());

	stbi_image_free(texturePointer->GetImageData());
}

void CTextureLoader::IncrementIndex()
{
	this->AccessingIndex += 1;
}

int32* CTextureLoader::GetAccessingIndexPointer()
{
	return &AccessingIndex;
}

int32 CTextureLoader::GetAccessingIndex()
{
	return this->AccessingIndex;
}