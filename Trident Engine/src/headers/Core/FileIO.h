#pragma once

class CBufferedReader
{
private:
	String Buffer;

public:
	String* WriteToBuffer(const String& FilePath);
	void AppendCharToBuffer(char Letter);
	void AppendStringToBuffer(const String& AppendingString);
	void ClearBuffer();

	String* GetBufferData();
};