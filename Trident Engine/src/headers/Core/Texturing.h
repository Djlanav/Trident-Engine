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
	uint32 Format;

public:
	// ** Getters **
	String* GetImageName();

	uint8* GetImageData();
	uint32 GetFormat();

	int32 GetWidth();
	int32 GetHeight();
	int32 GetNumberOfChannels();

	uint32 GetTextureID();

	void Make(int32 Width, int32 Height, int32 Channels);

	void SetImageName(const String& Name);
	void SetImageData(uint8* Data);
	void SetWidth(uint32 NewWidth);
	void SetHeight(uint32 NewHeight);
	void SetChannels(uint32 NewNumber);
	void SetTextureID(uint32 NewID);
	void SetFormat(uint32 Format);
};

class CTextureLoader
{
public:
	IMGVector Textures;

private:
	int32 AccessingIndex = 0;

private:
	void SetTextureParameters(int32 MipMapLevel, int32 OpenGLFormat,
		int32 ImageWidth, int32 ImageHeight, int32 Border, int32 ImageFormat, uint8* Data);

public:
	void LoadTextureData(const String& Name);
	void InitializeTexture(uint32 Index);

	void IncrementIndex();
	int32* GetAccessingIndexPointer();
	int32 GetAccessingIndex();
};