#include <string>
#include "util.h"

bool Util::is_number(std::string string)
{
	for (int i = 0; i<string.size(); i++)
	{
		if (!std::isdigit(string[i]))
			return false;
	}
	return true;
}
