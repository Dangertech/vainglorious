#include <iostream>
#include <string>
#include <fstream>
#include "args.h"
#include "util.h"
#include "const.h"
#include "theme.h"

#define INVERT(X)	X ? X = false : X = true;

void Args::process(int argc, char* argv[])
{
	for (int i = 1; i<argc; i++)
	{
		Util util;
		int match = util.veccmp<std::string>(std::string(argv[i]), switches);
		switch (match)
		{
			case 0: case 1: // -f, --scrollfile
				if (process_file(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("file");
					exit(1);
				}
				break;
			case 2: // --until
				if (process_until(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("until");
					exit(1);
				}
				break;
			case 3: case 4: // -l, --limit
				if (process_limit(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("limit");
					exit(1);
				}
				break;
			case 5: // --spacing
				if (process_spacing(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("spacing");
					exit(1);
				}
				break;
			case 6: // --forcedraw
				INVERT(forcedraw);
				break;
			case 7: case 8: // -T, --theme
				if (process_theme(i, argc, argv) == ERROR)
				{
					std::cout << err_msgs.at("theme");
					exit(1);
				}
				break;
			case 9: case 10: // -F, --colorfile
			{
				int ret = process_custom_theme(i, argc, argv);
				if (ret == -1)
				{
					std::cout << "The given colorfile could not be read"
						<< "Please check file permissions, ownership "
						<< "and existence." << std::endl;
					exit(1);
				}
				else if (ret != 0)
				{
					std::cout << "The given colorfile is invalid near "
						<< "line " C_GREEN_U << ret << C_OFF << "." << std::endl
						<< "\tHere is the info entry for colorfiles:" << std::endl
						<< err_msgs.at("custom_theme");
					exit(1);
				}
				break;
			}
			case 11: case 12: // -B, --background
				if (process_background(i, argc, argv) == ERROR)
				{
					exit(1);
				}
				break;
			case 13: case 14: // -C, --cursor
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
			case 15: case 16: // -c, --no-show-cursor
				INVERT(show_cursor);
				break;
			case 17: case 18: // -b, --movement-behaviour
				if (process_behaviour(i, argc, argv) == ERROR)
				{
					std::cout << "Argument wrongly used!" << std::endl;
					exit(1);
				}
				break;
			case 19: case 20: // -s, --movement-style
				if (process_style(i, argc, argv) == ERROR)
				{
					std::cout << "Argument wrongly used!" << std::endl;
					exit(1);
				}
				break;
			case 21: case 22: // -S, --movement-speed
				if (process_style(i, argc, argv) == ERROR)
				{
					std::cout << "Argument wrongly used!" << std::endl;
					exit(1);
				}
				break;
			case 23: // --debug (UNUSED)
				break;
			case 24: // --dry
				INVERT(dry);
				break;
			case 25: case 26: // -h, --help
				break;
			default:
				std::cout << "Invalid argument \"" << argv[i] << "\"! Ignoring!" << std::endl;
				break;
		}
	}
}

void Args::makepairs()
{
	// Make background color
	init_color(0, bg_col[0], bg_col[1], bg_col[2]);
	DefTheme thm;
	for (int cols = 0; cols<get_theme().size(); cols++)
	{
		Color my_color = get_theme()[cols];
		/* If the given RGB value is invalid, init_color
		 * just doesn't change the color which enables
		 * setting colors of default pairs through just the
		 * same system as custom RGB colors in theme.h
		 */
		init_color(my_color.id, my_color.R, my_color.G, my_color.B);
		init_pair(my_color.pair_prob.pair_id, my_color.id, 0);
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

int Args::process_theme(int &i, int argc, char* argv[])
{
	i++;
	if (i > argc-1)
		return ERROR;
	
	Util util;
	DefTheme thm;
	int match = util.veccmp<std::string>(util.to_lower(std::string(argv[i])), 
			thm.get_themenames());
	if (match != ERROR)
	{
		themeid = match;
		return 0;
	}
	if (util.is_number(std::string(argv[i])))
	{
		int num = atoi(argv[i]);
		if (num >= 0 && num < thm.get_themenames().size()) 
		{
			themeid = num;
			return 0;
		}
	}
	return ERROR;
}

int Args::process_custom_theme(int &i, int argc, char* argv[])
{
	// Get colorfile name
	i++;
	std::string name = std::string(argv[i]);
	std::ifstream cfile(name);
	if (!cfile.is_open())
		return -1; // File is unknown

	// Set themeid to -1 to mark that the theem used is
	// not to be found in DefTheme objects
	themeid = -1;

	// Parse colorfile
	int lnum = 0;
	std::string line;
	while (getline(cfile, line))
	{

		// Discard line from a '%'(comment) sign on
		for (int i = 0; i<line.size(); i++)
		{
			if (line[i] == '%')
			{
				line = line.substr(0, i);
				break;
			}
		}
		 
		if (line.empty())
		{
			lnum++;
			continue;
		}
		 
		 
		Util util;
		std::vector<std::string> spl = util.split_at(",", line);
		bool hex = false;
		if (spl[0][0] == '#')
			hex = true;
		if (!hex && spl.size() < 3) // Can't contain RGB value
			return lnum+1;
		std::vector<unsigned char> rgbval;
		try
		{
			if (hex)
				rgbval = unify_color_input(spl[0]);
			else
				rgbval = unify_color_input(spl[0] + "," + spl[1] + "," + spl[2]);
		}
		catch (int e)
		{
			return lnum+1;
		}
		 
		// First line is background color
		if (lnum == 0)
		{
			bg_col = {int(rgbval[0]*NCFAC), int(rgbval[1]*NCFAC), int(rgbval[2]*NCFAC)};
			lnum++;
			continue;
		}

		// Determine min, max and probability
		int min = 1, max = 1, prob = 1;
		if (hex && spl.size() >= 3)
		{
			min = std::stoi(spl[1]);
			max = std::stoi(spl[2]);
			if (spl.size() > 4)
				prob = std::stoi(spl[3]);
		}
		else if (spl.size() >= 5)
		{
			min = std::stoi(spl[3]);
			max = std::stoi(spl[4]);
			if (spl.size() > 6)
				prob = std::stoi(spl[5]);
		}

		// Switch around min and max if they are mixed up
		if (min > max)
		{
			int orig_max = max;
			max = min;
			min = orig_max;
		}
		 
		// Construct final color
		Color this_col = 
			{lnum+35, 
				int(rgbval[0]*NCFAC), int(rgbval[1]*NCFAC), int(rgbval[2]*NCFAC),
				{lnum+1, {min, max}, prob}};
		custom_theme.push_back(this_col); // Push it to the theme
		lnum++;
	}
	cfile.close();
	return 0;
}

int Args::process_background(int &i, int argc, char* argv[])
{
	i++;
	if (i  > argc-1)
		return ERROR;

	std::string input = std::string(argv[i]);
	std::vector<unsigned char> ret;
	try
	{
		ret = unify_color_input(input);
	}
	catch (int e)
	{
		return e;
	}
	bg_col[0] = ret[0]*NCFAC;
	bg_col[1] = ret[1]*NCFAC;
	bg_col[2] = ret[2]*NCFAC;
	return 0;
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

int Args::process_until(int &i, int argc, char* argv[])
{
	i++;
	Util util;
	if (!util.is_number(std::string(argv[i])))
		return ERROR;
	read_until = atoi(argv[i]);
	return 0;
}

int Args::process_spacing(int &i, int argc, char * argv[])
{
	i++;
	Util util;
	if (!util.is_number(std::string(argv[i])))
		return ERROR;
	spacing = atoi(argv[i]);
	return 0;
}

std::vector<Color> Args::get_theme()
{
	std::vector<Color> ret;
	if (custom_theme.size() == 0)
	{
		DefTheme thm;
		ret = thm.get_theme(themeid);
	}
	else
	{
		ret = custom_theme;
	}
	return ret;
}

std::vector<unsigned char> Args::get_curtheme()
{
	DefTheme thm;
	if (custom_cur.size() == 0)
		return thm.get_curcol(themeid);
	else
		return custom_cur;
}


int Args::process_behaviour(int &i, int argc, char* argv[])
{
	return 0;
}
int Args::process_style(int &i, int argc, char* argv[])
{
	return 0;
}
int Args::process_speed(int &i, int argc, char* argv[])
{
	return 0;
}
