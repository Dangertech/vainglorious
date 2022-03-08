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
				if (process_theme(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("color");
					exit(1);
				}
				break;
			case 8: case 9:
				if (process_background(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("color");
					exit(1);
				}
				break;
			case 10: case 11:
				if (process_cursor(i, argc, argv) == ERROR)
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

void Args::makepairs(int my_theme_id)
{
	for (int cols = 0; cols<themecols[my_theme_id].size(); cols++)
	{
		Color my_color = themecols[themeid][cols];
		init_color(my_color.id, my_color.R, my_color.G, my_color.B);
		init_pair(my_color.pair_prob.pair_id, my_color.id, bg_col);
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

/*
int Args::process_color(int &i, int argc, char* argv[], ColorSetters type)
{
	i++;
	if (i > argc-1)
		return ERROR;
	 
	std::string prop_col = std::string(argv[i]);
	Util util;
	int namematch = util.veccmp<std::string>(prop_col, themenames);
	if (namematch != ERROR)
	{
		themeid = namematch;
		return 0;
	}
	return ERROR;
}
*/
int Args::process_theme(int &i, int argc, char* argv[])
{
	i++;
	if (i > argc-1)
		return ERROR;
	
	Util util;
	int match = util.veccmp<std::string>(std::string(argv[i]), themenames);
	if (match != ERROR)
	{
		themeid = match;
		return 0;
	}
	return ERROR;
}

int Args::process_background(int &i, int argc, char* argv[])
{
	i++;
	if (i  > argc-1)
		return ERROR;

	Util util;
	int match = util.veccmp<std::string>(std::string(argv[i]), colnames);
	if (match != ERROR)
	{
		bg_col = match;
		return 0;
	}
	return ERROR;
}

int Args::process_cursor(int &i, int argc, char* argv[])
{
	/* TODO: Just as custom themes,
	 * setting a cursor color independent from the
	 * theme is currently not supported, In future,
	 * the user should be able to provide a theme
	 * name or an HEX/RGB value here.
	 */
	return ERROR;
}

// TODO: Theme names could get names that aren't valid ANSI
// cursor escape code names; 
std::string Args::colid_to_string(int colid)
{
	if (colid < themenames.size() && colid >= 0)
		return themenames[colid];
	else
		return "white";
}
