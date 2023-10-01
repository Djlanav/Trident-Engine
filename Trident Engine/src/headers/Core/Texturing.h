#pragma once

// ** Forward Declarations **
class CTexture;
class CTextureLoader;

// ** Typedefs **
typedef std::vector<CTexture*> IMGVector;

// ** Classes **

class CTexture
{
private:
	String sImageName;

	int32 TextureWidth;
	int32 TextureHeight;
	int32 NumberOfChannels;

	uint8* ImageData;

	uint32 TextureID;

public:
	CTexture(int32 Width, int32 Height, int32 Channels);

	// ** Getters **
	String* GetImageName();

	uint8* GetImageData();

	int32 GetWidth();
	int32 GetHeight();
	int32 GetNumberOfChannels();

	uint32 GetTextureID();

	void SetImageName(const String& Name);
	void SetImageData(uint8* Data);
	void SetWidth(uint32 NewWidth);
	void SetHeight(uint32 NewHeight);
	void SetChannels(uint32 NewNumber);
	void SetTextureID(uint32 NewID);
};

class CTextureLoader
{
private:
	IMGVector Textures;

private:
	void SetTextureParameters(int32 MipMapLevel, int32 OpenGLFormat,
		int32 ImageWidth, int32 ImageHeight, int32 Border, int32 ImageFormat, uint8* Data);

public:
	void LoadTextureData(const String& Name, int32 Width, int32 Height, int32 Channels);
	void InitializeTexture(uint32 Index);
};