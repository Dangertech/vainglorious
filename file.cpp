#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "file.h"
#include "args.h"
#include "const.h"


int File::crunch_file(Args my_args)
{
	std::ifstream scroll;
	scroll.open(my_args.get_file());
	if (!scroll.is_open())
		return ERROR;
	std::string cur_line;
	int lnum = 1;
	std::vector<std::string> cur_block;
	while (getline(scroll, cur_line))
	{
		if (my_args.get_read_until() != -1 && lnum > my_args.get_read_until())
			break;
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
		lnum++;
	}
	// Push the last block before EOF
	if (cur_block.size() > 0)
		blocks.push_back(cur_block);
	scroll.close();
	return 0;
}

std::vector<std::string> File::rblock()
{
	srand(time(0) + roff);
	int cho = rand()%blocks.size();
	roff++;
	return blocks[cho];
}
