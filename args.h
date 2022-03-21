#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <ncurses.h>
#include "const.h"

struct PairProb
{
	int pair_id; // The color pair id
	std::pair<int, int> app_length; // For how long it appears
	int prob; // Probability to start appearing
};

struct Color
{
	int id;
	int R, G, B;
	PairProb pair_prob;
};

class Args
{
	private:

		/* General Argument management
		 * Processers for the flags are
		 * managed by the public process_args()
		 */
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
			"-T",
			"--theme",
			"-B",
			"--background",
			"-C",
			"--cursor",
			"-c",
			"--no-show-cursor",
			"--debug",
			"--dry",
			"--help"
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
			{"cursor",
				s("Usage of -C/--cursor:\n")
				+ "\tSet the cursor color through either a theme name/id, a RGB value or a HEX value;\n"
				+ "\tExamples:\n"
				+ "\t\t- Theme name/id: '" + C_GREEN_U + "vain -C 1" + C_OFF + "' sets the cursor color to the predefined cursor color of the theme with ID 1\n"
				+ "\t\t- RGB value: '" + C_GREEN_U + "vain -C \"85, 255, 0\"" + C_OFF + "' sets the cursor color to a bright green\n"
				+ "\t\t- HEX value: '" + C_GREEN_U + "vain -C \"#3ebfb3\"" + C_OFF + "' sets the cursor color to a teal tone\n"
				+ "\tDefault: Cursor color is defined by the theme you chose\n"
			}
			
		};
		int process_file(int &i, int argc, char * argv[]);
		int process_limit(int &i, int argc, char * argv[]);
		 
		int process_theme(int &i, int argc, char * argv[]);
		int process_background(int &i, int argc, char * argv[]);
		int process_cursor(int &i, int argc, char * argv[]);

		std::vector<unsigned char> unify_color_input(std::string input);


		// Color settings
		int themeid = 0;
		/* The background color is
		 * completely independent from
		 * the set theme; It is used by args::makepairs()
		 * to set the correct background color for every pair */
		int bg_col = COLOR_BLACK;
		bool multicol = true; // If this is false, only color 0 from a theme will be used
		/* The input and display name for the default
		 * themes
		 * T^he sort order implies the id of each theme
		 * (e.g. the green theme has the id 0)
		 */
		std::vector<std::string> themenames =
		{
			"green",
			"test"
		};

		/* General accepted names of colors,
		 * used for setting the background color,
		 * for example
		 */
		std::vector<std::string> colnames =
		{
			"black",
			"red",
			"green",
			"yellow",
			"blue",
			"magenta",
			"cyan",
			"white"
		};

		/* The default colors for the predefined themes
		 * The second layer is sorted by the theme ids
		 */
		std::vector<std::vector<Color>> themecols =
		{
			// GREEN example
			{
				// COLORID, R,   G,   B,ColPair,length,probability
				{234,       71,  141, 83,  {1, {1,4}, 10} },
				{22,        149, 243, 161, {2, {1,1}, 20} },
				{28,        188, 596, 318, {3, {1,1}, 30} },
				{35,        188, 714, 397, {4, {1,1}, 40} },
				{78,        227, 925, 561, {5, {1,1}, 50} },
				{84,        271, 973, 667, {6, {1,1}, 60} },
				{159,       667, 1000, 941,{7, {4,8}, 70} }
			}
		};
		/* Cursor colors corresponding to their schemes */
		std::vector<std::vector<unsigned char>> curcols =
		{
			// GREEN
			{0, 255, 0},
			{55, 255, 212}
		};
		/* Custom cursor scheme set by the user */
		std::vector<unsigned char> custom_cur = {};
		bool show_cursor = true;
		 

		 
	public:
		void process(int argc, char* argv[]);
		void makepairs(int themeid);
		std::string colid_to_string(int colid);
		 
		std::string get_file() { return file; }
		int get_limit() { return limit; }
		bool get_dry() { return dry; }
		 
		int get_themeid() { return themeid; }
		std::vector<Color> get_theme_cols(int theme_id) { return themecols[themeid];}
		bool get_show_cursor() { return show_cursor; }
		/* Returns curcol of theme_id when custom_cur is not set,
		 * custom_cur content if otherwise
		 */
		std::vector<unsigned char> get_curtheme();
};
