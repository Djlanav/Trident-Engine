#pragma once

// ** Forward Declarations **
class CTextureList;
class CTexture;
class CTextureLoader;

// ** Typedefs **
using StringTextureHashMap = std::unordered_map<String, std::shared_ptr<CTexture>>;

// ** Classes **

class CTextureList
{
private:
	StringTextureHashMap TexturesMap;
	std::shared_ptr<CTexture> PreviouslyAddedTexture;

public:
	CTextureList();

	void AddTextureToList(const String& Name, std::shared_ptr<CTexture> Texture);

	std::shared_ptr<CTexture> FindMatchingTexture(const String& TextureNameToCheck);
	std::shared_ptr<CTexture> GetLastAddedTexture();
	std::shared_ptr<CTexture> RetrieveTextureByName(const String& TextureToRetrieve);

	String* GetLastAddedTextureName();

	size_t RetrieveListSize();

	~CTextureList();
};

class CTextureLoader
{
public:
	CTextureList TextureMap;

private:
	void SetTextureParameters(std::shared_ptr<CTexture>, int32, int32,
		int32, int32, int32, int32, uint8*);

public:
	std::shared_ptr<CTexture> LoadTextureData(const String& Name);
	void InitializeTexture(const String& Name);
};

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

	bool IsLoaded = false; // Default is false. Obviously..
	bool IsFreed = false; // Related to stbi_image_free();
	bool HasMipmap = false; // Again :)

public:
	// ** Getters **
	String* GetImageName();

	uint8* GetImageData();
	uint32 GetFormat();

	int32 GetWidth();
	int32 GetHeight();
	int32 GetNumberOfChannels();

	uint32 GetTextureID();

	bool GetIsLoaded();
	bool GetIsFreed();
	bool GetHasMipmap();

	void Make(int32 Width, int32 Height, int32 Channels);

	void SetImageName(const String& Name);
	void SetImageData(uint8* Data);
	void SetWidth(uint32 NewWidth);
	void SetHeight(uint32 NewHeight);
	void SetChannels(uint32 NewNumber);
	void SetTextureID(uint32 NewID);
	void SetFormat(uint32 Format);
	void SetIsLoaded(bool Status);
	void SetHasMipmap(bool Status);
	void SetIsFreed(bool Status);
};

