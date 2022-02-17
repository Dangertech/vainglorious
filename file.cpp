#include <fstream>
#include <iostream>
#include "file.h"
#include "const.h"

File file;

int File::crunch_file(std::string scroll_loc)
{
	std::ifstream scroll(scroll_loc);
	if (!scroll.is_open())
		return ERROR;
	std::string cur_line;
	std::vector<std::string> cur_block;
	while (getline(scroll, cur_line))
	{
		if (cur_line == "") // Block finished, push!
		{
			if (cur_block.size() > 0)
				blocks.push_back(cur_block);
			cur_block.clear();
		}
		else
		{
			cur_block.push_back(cur_line);
		}
	}
	// Push the last block before EOF
	if (cur_block.size() > 0)
		blocks.push_back(cur_block);
	scroll.close();
	return 0;
}
