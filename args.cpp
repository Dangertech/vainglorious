#include <iostream>
#include <string>
#include "args.h"
#include "util.h"
#include "const.h"

void Args::process(int argc, char* argv[])
{
	for (int i = 1; i<argc; i++)
	{
		Util util;
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
					exit(1);
				}
				break;
			case 8: case 9:
				if (process_background(i, argc, argv) == ERROR)
				{
					exit(1);
				}
				break;
			case 10: case 11:
				switch(process_cursor(i, argc, argv))
				{
					case 0:
						break;
					case -1:
						std::cout << "The RED part of the hex code you provided is invalid.\n"
							<< "It has to be either the numbers 0-9 or one of the letters \"abcdef\" uppercase or lowercase."
							<< std::endl;
						exit(1);
						break;
					case -2:
						std::cout << "The GREEN part of the hex code you provided is invalid.\n"
							<< "It has to be either the numbers 0-9 or one of the letters \"abcdef\" uppercase or lowercase."
							<< std::endl;
						exit(1);
						break;
					case -3:
						std::cout << "The BLUE part of the hex code you provided is invalid.\n"
							<< "It has to be either the numbers 0-9 or one of the letters \"abcdef\" uppercase or lowercase."
							<< std::endl;
						exit(1);
						break;
					case 16: case ERROR:
						std::cout << err_msgs.at("cursor");
						exit(1);
						break;
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
	i++;
	std::string input = std::string(argv[i]);
	 
	/* Check if a theme name or id is provided */
	int match = 0;
	Util util;
	if (util.is_number(input))
		match = std::stoi(input);
	else
		match = util.veccmp<std::string>(input, themenames);
	 
	if (match != ERROR)
	{
		if (match < themenames.size() && match >= 0)
		{
			custom_cur = curcols[match]; 
			return 0;
		}
	}
	 
	/* TODO: Check if a RGB value is provided (like "0,255,0") */
	 
	/* Check if a HEX value is provided (like "#00ff00") */
	if (input.find('#') == 0)
	{
		if (input.size() == 7)
		{
			/* TODO: Process HEX input */
			try
			{
				custom_cur = util.hextorgb(input);
			}
			catch (int e)
			{
				std::cout << "Invalid!" << std::endl;
				// Invalidate input
				custom_cur = {};
				switch (e)
				{
					case 1:
						return -1;
						break;
					case 2:
						return -2;
						break;
					case 3:
						return -3;
						break;
				}
				return -16;
			}
			return 0;
		}
	}
	return ERROR;
}

std::vector<unsigned char> Args::get_curtheme()
{
	if (custom_cur.size() == 0)
		return curcols[themeid];
	else
		return custom_cur;
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
