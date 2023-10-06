#pragma once

template<typename T>
class TUIDataContainer
{
private:
	std::unordered_map<String, T> DataBuffer;

public:
	void AddToBuffer(const String& Name, T Data)
	{
		DataBuffer.insert({ Name, Data });
	}

	T GetDataFromBuffer(const String& ElementName)
	{
		return DataBuffer.at(ElementName);
	}
};