#include "Core/CommonHeaders.h"

#include "glad/glad.h"
#include "Core/Typedefs.h"
#include "Core/Module.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Plugins/stb_image.h"

#include "Core/Texturing.h"
#include "Plugins/Logger.h"

// ** CTextureLoader **

bool CTextureLoader::CheckForTexture(CTexture* Texture)
{
	for (CTexture* t : Textures)
	{
		if (*t->GetImageName() == *Texture->GetImageName())
		{
			return true;
		}
	}
	return false;
}

void CTextureLoader::LoadTextureData(const String& Name)
{
	CTexture* texture = new CTexture();
	texture->SetImageName(Name);

	std::future<bool> checkTextureResult = std::async(std::launch::async, [this, texture]() 
		{ 
			return CheckForTexture(texture); 
	});
	bool result = checkTextureResult.get();

	if (result != true)
	{
		return;
	}

	ELogStatus status;

	int32 w;
	int32 h;
	int32 c;

	stbi_set_flip_vertically_on_load(true);

	uint8* data = stbi_load(Name.c_str(), &w, &h, &c, 0);
	texture->Make(w, h, c);

	texture->SetImageData(data);

	if (c == 3)
	{
		texture->SetFormat(GL_RGB);
	}
	else if (c > 3)
	{
		texture->SetFormat(GL_RGBA);
	}

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

void CTextureLoader::InitializeTexture(uint32 Index)
{
	uint32 id = Textures.at(Index)->GetTextureID();
	CTexture* texturePointer = Textures.at(Index);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	SetTextureParameters(0, texturePointer->GetFormat(), texturePointer->GetWidth(), texturePointer->GetHeight(),
		0, texturePointer->GetFormat(), texturePointer->GetImageData());

	stbi_image_free(texturePointer->GetImageData());
}

void CTextureLoader::SetTextureParameters(int32 MipMapLevel, int32 OpenGLFormat,
	int32 ImageWidth, int32 ImageHeight, int32 Border, int32 ImageFormat, uint8* Data)
{
	glTexImage2D(GL_TEXTURE_2D, MipMapLevel, OpenGLFormat, ImageWidth, ImageHeight, Border,
		ImageFormat, GL_UNSIGNED_BYTE, Data);

	glGenerateMipmap(GL_TEXTURE_2D);
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

uint32 CTexture::GetFormat()
{
	return Format;
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

void CTexture::SetFormat(uint32 Format)
{
	this->Format = Format;
}