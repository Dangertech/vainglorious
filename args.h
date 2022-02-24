#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <ncurses.h>
#include "const.h"

class Args
{
	private:
		std::string file = DEF_FILE;
		bool dry = false;
		int limit = 4;
		std::vector<std::string> switches =
		{
			"-f",
			"--file",
			"-s",
			"--scroll-mode",
			"-l",
			"--limit",
			"-F",
			"--foreground",
			"-B",
			"--background",
			"-c",
			"--no-show-cursor",
			"--debug",
			"--dry",
			"--help"
		};
		std::unordered_map<std::string, int> colnames =
		{
			{"black",COLOR_BLACK},
			{"red", COLOR_RED},
			{"green", COLOR_GREEN},
			{"yellow", COLOR_YELLOW},
			{"blue", COLOR_BLUE},
			{"magenta", COLOR_MAGENTA},
			{"cyan", COLOR_CYAN},
			{"white", COLOR_WHITE}
		};
		#define s(X) std::string(X)
		#define int_st(X) std::to_string(X)
		std::unordered_map<std::string, std::string> err_msgs =
		{
			{"file",
				s("Usage of -f/--file:\n")
				+ "\tSpecify a file to get text blocks from;\n"
				+ "\t\tExample: '" + C_GREEN_U + "vain --file scrollfile.txt" + C_OFF + "'\n"
				+ "\t\tDefault: '" + file + "'\n"
			},
			{"limit",
				s("Usage of -l/--limit:\n")
				+ "\tSet the bottom margin of the scrolling text;\n"
				+ "\t\tExample: '" + C_GREEN_U + "vain --limit 1" + C_OFF + "'\n"
				+ "\t\tDefault: " + int_st(limit) + "\n"
			},
			{"color",
				s("Usage of -F/--foreground and -B/--background:\n")
				+ "\tChange the foreground or background color with one of eight predefined color names\n"
				+ "\t\tExample: '" + C_GREEN_U + "vain -F red -B white" + C_OFF + "'\n"
				+ "\t\tAll accepted color names:\n"
				+ "\t\t\tblack\n"
				+ "\t\t\tred\n"
				+ "\t\t\tgreen\n"
				+ "\t\t\tyellow\n"
				+ "\t\t\tblue\n"
				+ "\t\t\tmagenta\n"
				+ "\t\t\tcyan\n"
				+ "\t\t\twhite\n"
				+ "\t\tDefault: green foreground, black background\n"
			}
			
		};
		 
		// Color settings
		int fg_color = COLOR_GREEN, bg_color = COLOR_BLACK; 		 
		bool show_cursor = false;
		/* Cursor Color
		 * -1 gets handled by get_cur() as fg_color,
		 *  so that it's just the foreground color unless
		 *  the user specifies something else
		 */
		int cur_color = -1;
		 
		int process_file(int &i, int argc, char * argv[]);
		int process_limit(int &i, int argc, char * argv[]);
		int process_color(int &i, int argc, char * argv[], bool bg);
	public:
		void process(int argc, char* argv[]);
		std::string get_file() { return file; }
		int get_limit() { return limit; }
		int get_fg() { return fg_color; }
		int get_bg() { return bg_color; }
		bool get_show_cursor() { return show_cursor; }
		int get_cur(); // Because of more complexity located in args.cpp
		std::string colid_to_string(int colid);
		bool get_dry() { return dry; }
};
