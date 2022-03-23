#include <iostream>
#include <string>
#include "args.h"
#include "util.h"
#include "const.h"
#include "theme.h"

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
					case 1:
						std::cout << "The RED part of the hex code you provided is invalid.\n"
							<< "It has to be either the numbers 0-9 or one of the letters \"abcdef\" uppercase or lowercase."
							<< std::endl;
						exit(1);
						break;
					case 2:
						std::cout << "The GREEN part of the hex code you provided is invalid.\n"
							<< "It has to be either the numbers 0-9 or one of the letters \"abcdef\" uppercase or lowercase."
							<< std::endl;
						exit(1);
						break;
					case 3:
						std::cout << "The BLUE part of the hex code you provided is invalid.\n"
							<< "It has to be either the numbers 0-9 or one of the letters \"abcdef\" uppercase or lowercase."
							<< std::endl;
						exit(1);
						break;
					case 255:
						std::cout << "If you tried to enter an RGB value, you have to give three numbers between 0 and 256,\n"
							<< "separated by commata, enclosed in quotes, like this:\n" 
							<< C_GREEN_U << "\tvain -C \"0, 255, 0\"" << C_OFF << std::endl;
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
	DefTheme thm;
	for (int cols = 0; cols<thm.get_theme(my_theme_id).size(); cols++)
	{
		Color my_color = thm.get_theme(my_theme_id)[cols];
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
	DefTheme thm;
	int match = util.veccmp<std::string>(std::string(argv[i]), 
			thm.get_themenames());
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
	DefTheme thm;
	int match = util.veccmp<std::string>(std::string(argv[i]), 
			thm.get_colnames());
	if (match != ERROR)
	{
		bg_col = match;
		return 0;
	}
	return ERROR;
}

int Args::process_cursor(int &i, int argc, char* argv[])
{
	 
	i++;
	std::string input = std::string(argv[i]);
	std::vector<unsigned char> ret;
	try
	{
		ret = unify_color_input(input); 
	}
	catch (int e)
	{
		return e; // Errors are handled by process_args itself
	}
	custom_cur = ret;
	return 0;
}

std::vector<unsigned char> Args::unify_color_input(std::string input)
{
	Util util;
	DefTheme thm;
	std::vector<std::string> tnames= thm.get_themenames();
	 
	/* Check if a theme name or id is provided */
	int match = 0;
	if (util.is_number(input))
		match = std::stoi(input);
	else
		match = util.veccmp<std::string>(input, tnames);
	 
	if (match != ERROR)
	{
		if (match < tnames.size() && match >= 0)
		{
			return thm.get_curcol(match); 
		}
	}
	 
	/* Check if a RGB value is provided (like "0,255,0") */
	std::vector<std::string> rgb = util.split_at(", ", input);
	if (rgb.size() == 3)
	{
		// TODO
		std::vector<unsigned char> rgbvals;
		for (int i = 0; i<3; i++)
		{
			int rgbval = 0;
			try
			{
				rgbval = std::stoi(rgb[i]);
			}
			catch (std::invalid_argument& e)
			{
				throw 255;
			}
			 
			if (rgbval >= 0 && rgbval <= 255)
				rgbvals.push_back(rgbval);
			else
				throw 255;
		}
		return rgbvals;
	}
	 
	/* Check if a HEX value is provided (like "#00ff00") */
	if (input.find('#') == 0)
	{
		if (input.size() == 7)
		{
			std::vector<unsigned char> curcol;
			try
			{
				curcol = util.hextorgb(input);
			}
			catch (int e)
			{
				// Invalidate input
				custom_cur = {};
				switch (e)
				{
					case 1:
						throw 1;
						break;
					case 2:
						throw 2;
						break;
					case 3:
						throw 3;
						break;
				}
				throw 16;
			}
			return curcol;
		}
	}
	throw ERROR;
}

std::vector<unsigned char> Args::get_curtheme()
{
	DefTheme thm;
	if (custom_cur.size() == 0)
		return thm.get_curcol(themeid);
	else
		return custom_cur;
}
