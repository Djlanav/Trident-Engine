#pragma once

enum ELogStatus {
	ERRORED,
	FAILURE,
	WARNING,
	SUCCESS,
	MESSAGE
};

class CLogger
{
public:
	static void Log(const String& sMessage, ELogStatus* LogStatus, String* Extra);
};