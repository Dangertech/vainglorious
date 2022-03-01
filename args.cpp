#include <iostream>
#include <string>
#include "args.h"
#include "util.h"
#include "const.h"

void Args::process(int argc, char* argv[])
{
	for (int i = 1; i<argc; i++)
	{
		int match = util.veccmp<std::string>(std::string(argv[i]), switches);
		switch (match)
		{
			case 0: case 1:
				if (process_file(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("file");
					exit(1);
				}
				break;
			case 4: case 5:
				if (process_limit(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("limit");
					exit(1);
				}
				break;
			case 6: case 7:
				if (process_color(i, argc, argv, FG) == ERROR)
				{
					std::cout << err_msgs.at("color");
					exit(1);
				}
				break;
			case 8: case 9:
				if (process_color(i, argc, argv, BG) == ERROR)
				{
					std::cout << err_msgs.at("color");
					exit(1);
				}
				break;
			case 10: case 11:
				if (process_color(i, argc, argv, CUR) == ERROR)
				{
					std::cout << err_msgs.at("color");
					exit(1);
				}
				break;
			case 12: case 13:
				show_cursor = false;
				break;
			case 15:
				dry = true;
				break;
			default:
				std::cout << "Invalid argument!" << std::endl;
				break;
		}
	}
}

int Args::process_file(int &i, int argc, char* argv[])
{
	if (i < argc-1)
	{
		i++;
		file = argv[i];
	}
	else
		return ERROR;
	return 0;
}

int Args::process_limit(int &i, int argc, char* argv[])
{
	if (i < argc-1)
	{
		i++;
		if (atoi(argv[i]) < 1)
			limit = 1;
		else
			limit = atoi(argv[i]);
	}
	else
		return ERROR;
	return 0;
}

int Args::process_color(int &i, int argc, char* argv[], ColorSetters type)
{
	i++;
	if (i > argc-1)
		return ERROR;
	 
	std::string prop_col = std::string(argv[i]);
	/*
	if (colnames.find(prop_col) != colnames.end())
	{
		if (type == FG)
			fg_color = colnames.at(prop_col);
		else if (type == BG)
			bg_color = colnames.at(prop_col);
		else if (type == CUR)
			cur_color = colnames.at(prop_col);
	}
	*/
	Util util;
	int namematch = util.veccmp<std::string>(prop_col, themenames);
	if (namematch != ERROR)
		fg_color = namematch;
	return ERROR;
}

std::string Args::colid_to_string(int colid)
{
	if (colid < themenames.size() && colid >= 0)
		return themenames[colid];
	else
		return "white";
}

int Args::get_cur()
{
	if (cur_color == -1)
		return fg_color;
	else
		return cur_color;
}
