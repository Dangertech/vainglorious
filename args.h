#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <ncurses.h>

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
		 
		// Foreground and background color
		int fg_color = COLOR_GREEN, bg_color = COLOR_BLACK; 		 
		 
		void process_file(int &i, int argc, char * argv[]);
		void process_limit(int &i, int argc, char * argv[]);
		void process_color(int &i, int argc, char * argv[], bool bg);
	public:
		void process(int argc, char* argv[]);
		std::string get_file() { return file; }
		bool get_dry() { return dry; }
		int get_limit() { return limit; }
		int get_fg() { return fg_color; }
		int get_bg() { return bg_color; }
};
