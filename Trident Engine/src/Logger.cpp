#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include "Core/Typedefs.h"
#include "Plugins/color.hpp"
#include "Plugins/Logger.h"

void CLogger::Log(const String& sMessage, ELogStatus* LogStatus, String* Extra)
{
	switch (*LogStatus)
	{
	case ERROR:
		std::cout << dye::aqua("[LOG] ") << sMessage << " " << dye::red("ERROR\n");
		break;
	case FAILURE:
		std::cout << dye::aqua("[LOG] ") << sMessage << " " << dye::red("FAILED\n");
		break;
	case WARNING:
		std::cout << dye::aqua("[LOG] ") << sMessage << " " << dye::yellow("WARNING\n");
		break;
	case SUCCESS:
		std::cout << dye::aqua("[LOG] ") << sMessage << " " << dye::green("SUCCESSFUL\n");
		break;
	case MESSAGE:
		std::cout << dye::aqua("[MESSAGE] ") << sMessage << " " << "\n";
		break;
	}

	if (Extra != nullptr)
	{
		std::cout << *Extra;
	}
}