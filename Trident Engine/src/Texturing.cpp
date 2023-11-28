#include "Core/CommonHeaders.h"

#include "glad/glad.h"
#include "Core/Typedefs.h"
#include "Core/Module.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Plugins/stb_image.h"

#include "Core/Texturing.h"
#include "Plugins/Logger.h"

#define TEXTURELIST_RESERVE_SIZE 6

// ** CTextureList **
CTextureList::CTextureList()
	: PreviouslyAddedTexture(nullptr)
{
	TexturesMap.reserve(TEXTURELIST_RESERVE_SIZE);
}

/// <summary>
/// Insert a CTexture* to the TexturesMap field.
/// This method also sets the field "PreviouslyAddedTexture" to the the CTexture* passed in.
/// </summary>
/// <param name="Name"></param>
/// <param name="Texture"></param>
void CTextureList::AddTextureToList(const String& Name, std::shared_ptr<CTexture> Texture)
{
	PreviouslyAddedTexture = Texture;
	TexturesMap.insert({ Name, Texture });
}

/// <summary>
/// Loops through the Textures map and checks if two CTexture instances have the same name. 
/// If true, returns a pointer to the copy texture. Else it returns nullptr.
/// </summary>
/// <param name="TextureNameToCheck"></param>
/// <returns>Pointer to CTexture instance</returns>
std::shared_ptr<CTexture> CTextureList::FindMatchingTexture(const String& TextureNameToCheck)
{
	auto it = TexturesMap.find(TextureNameToCheck);

	if (it != TexturesMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<CTexture> CTextureList::GetLastAddedTexture()
{
	return PreviouslyAddedTexture;
}

String* CTextureList::GetLastAddedTextureName()
{
	return PreviouslyAddedTexture->GetImageName();
}

std::shared_ptr<CTexture> CTextureList::RetrieveTextureByName(const String& TextureToRetrieve)
{
	return TexturesMap.at(TextureToRetrieve);
}

size_t CTextureList::RetrieveListSize()
{
	return TexturesMap.size();
}

CTextureList::~CTextureList()
{
	TexturesMap.clear();
}

// ** CTextureLoader **

std::shared_ptr<CTexture> CTextureLoader::LoadTextureData(const String& Name)
{
	std::shared_ptr<CTexture> matchResult = TextureMap.FindMatchingTexture(Name);
	if (matchResult.get() != nullptr)
	{
		return matchResult;
	}
	else
	{
		std::shared_ptr<CTexture> texture = std::make_shared<CTexture>();
		texture->SetImageName(Name);

		ELogStatus status;

		int32 w, h, c;

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

		uint32 id = texture->GetTextureID();
		glGenTextures(1, &id);
		texture->SetTextureID(id);

		texture->SetIsLoaded(true);
		TextureMap.AddTextureToList(*texture->GetImageName(), texture);
	
		return texture;
	}
}

void CTextureLoader::InitializeTexture(const String& Name)
{
	std::shared_ptr<CTexture> texturePointer = TextureMap.RetrieveTextureByName(Name);
	uint32 id = texturePointer->GetTextureID();

	glBindTexture(GL_TEXTURE_2D, id);

	SetTextureParameters(texturePointer, 0, texturePointer->GetFormat(), texturePointer->GetWidth(), texturePointer->GetHeight(),
		0, texturePointer->GetFormat(), texturePointer->GetImageData());

	if (texturePointer->GetIsFreed() == true)
	{
		stbi_image_free(texturePointer->GetImageData());
		texturePointer->SetIsFreed(false);
	}
}

void CTextureLoader::SetTextureParameters(std::shared_ptr<CTexture> TexturePointer, int32 MipMapLevel, int32 OpenGLFormat,
	int32 ImageWidth, int32 ImageHeight, int32 Border, int32 ImageFormat, uint8* Data)
{
	glTexImage2D(GL_TEXTURE_2D, MipMapLevel, OpenGLFormat, ImageWidth, ImageHeight, Border,
		ImageFormat, GL_UNSIGNED_BYTE, Data);

	if (TexturePointer->GetHasMipmap() == false)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		TexturePointer->SetHasMipmap(true);
	}
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

bool CTexture::GetIsLoaded()
{
	return IsLoaded;
}

bool CTexture::GetIsFreed()
{
	return IsFreed;
}

bool CTexture::GetHasMipmap()
{
	return HasMipmap;
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

void CTexture::SetIsLoaded(bool Status)
{
	IsLoaded = Status;
}

void CTexture::SetHasMipmap(bool Status)
{
	HasMipmap = Status;
}

void CTexture::SetIsFreed(bool Status)
{
	IsFreed = Status;
}