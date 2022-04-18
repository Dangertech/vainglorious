#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <ncurses.h>
#include "theme.h"
#include "const.h"

enum MovementBehaviour { INPUT, AUTO };
enum ProgressStyle { LINE, WORD, CHARACTER, BLOCK };


class Args
{
	private:

		// Properties (accessible through public functions)
		 
		/* File to read blocks from */
		std::string file = DEF_FILE;
		/* Until where should the scroll file
		 * be read? -1 reads until the end
		 */
		int read_until = -1;
		/* How far down from the lower terminal border
		 * should the text be shown before scrolling up?
		 */
		int spacing = 1;
		/* How many lines should be left empty
		 * between individual blocks
		 */
		int limit = 4;
		/* Should the screen be cleared and redrawn
		 * from scratch every time it changes?
		 */
		bool forcedraw = false;

		/* Only get arguments and quit before initializing
		 * the ncurses display
		 */
		bool dry = false;

		// Color settings
		int themeid = 0;
		/* The background color is
		 * completely independent from
		 * the set theme; It is used by args::makepairs()
		 * to set the correct background color for every pair */
		// Uses rgb values from range 0 to 1000
		std::vector<int> bg_col = {0, 0, 0};
		/* if this is false, only color 0 from a theme will be used */
		bool multicol = true;
		/* Custom theme that is set if the user gives a valid colorfile */
		std::vector<Color> custom_theme = {};
		/* Custom cursor scheme set by the user */
		std::vector<unsigned char> custom_cur = {};
		bool show_cursor = true;

		// Movement style
		MovementBehaviour behaviour = INPUT;
		ProgressStyle style = LINE;
		int speed = 1;
		/* By default, the user can advance the
		 * text by 1 line by pressing a button
		 */

		// Input management
		 
		std::vector<std::string> switches =
		{
			"-f",
			"--scrollfile",
			"--until",

			// General properties
			"-l",
			"--limit",
			"--spacing",
			"--forcedraw",
			 
			// Color related
			"-T",
			"--theme",
			"-F",
			"--colorfile",
			"-B",
			"--background",
			"-C",
			"--cursor",
			"-c",
			"--no-show-cursor",

			// Input related
			"-b",
			"--movement-behaviour",
			"-s",
			"--movement-style",
			"-S",
			"--movement-speed",
			 
			// Utilities
			"--debug",
			"--dry",
			"-h",
			"--help"
		};

		// Flag processors 
		 
		int process_file(int &i, int argc, char * argv[]);
		int process_until(int &i, int argc, char * argv[]);
		int process_limit(int &i, int argc, char * argv[]);
		int process_spacing(int &i, int argc, char * argv[]);
		 
		int process_theme(int &i, int argc, char * argv[]);
		/* Return values: Returns 0 if everything is OK,
		 * or the line number in which an error was encountered,
		 * starting at 1; Returns -1 if the file could not be opened
		 */
		int process_custom_theme(int &i, int argc, char * argv[]);
		int process_background(int &i, int argc, char * argv[]);
		int process_cursor(int &i, int argc, char * argv[]);

		std::vector<unsigned char> unify_color_input(std::string input);

		int process_behaviour(int &i, int argc, char * argv[]);
		int process_style(int &i, int argc, char * argv[]);
		int process_speed(int &i, int argc, char * argv[]);



		// Error/Help messages
		 
		#define s(X) std::string(X)
		#define int_st(X) std::to_string(X)
		// Ugly bodge for err_msgs.at("theme");
		DefTheme listener;
		std::string print_themes()
		{
			std::string ret;
			std::vector<std::string> names = listener.get_themenames();
			for (int i = 0; i<names.size(); i++)
			{
				ret += "\t\t" + names[i] + "\n";
			}
			return ret;
		}
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
				+ "\t\t- Theme name/id: '" + C_GREEN_U + "vain -C 1" 
					+ C_OFF + "' sets the cursor color to the predefined cursor color of the theme with ID 1\n"
				+ "\t\t- RGB value: '" + C_GREEN_U + "vain -C \"85, 255, 0\"" 
					+ C_OFF + "' sets the cursor color to a bright green\n"
				+ "\t\t- HEX value: '" + C_GREEN_U + "vain -C \"#3ebfb3\"" 
					+ C_OFF + "' sets the cursor color to a teal tone\n"
				+ "\tDefault: Cursor color is defined by the theme you chose\n"
			},
			{"theme",
				s("Usage of -T/--theme:\n")
				+ "\tChange the theme to one of the predefined ones;\n"
				+ "\tThere are currently " 
					+ int_st(listener.get_themenames().size())
					+ " themes available:\n"
				+ print_themes()
				+ "\tBIG THANKS to https://github.com/st3w/neo for some "
					+ "theme colors which I shamelessly stole from their project\n"
				+ "\tExamples:\n"
				+ "\t\tBy name:  '" + C_GREEN_U + "vain --theme " 
					+ listener.get_themenames()[1] + C_OFF + "'\n"
				+ "\t\tBy index: '" + C_GREEN_U + "vain --theme 1" + C_OFF + "'\n"
				+ "\t\t\t(The index starts at 0, so 1 is the " 
					+ listener.get_themenames()[1] + " theme)\n"
				+ "\tDefault: Green theme with index 0\n"
			},
			{"custom_theme",
				s("Usage of -F/--colorfile:\n")
				+ "\t(This entry is a stub and will be extended in the future)\n"
			},
			{"spacing",
				s("Usage of --spacing:\n")
				+ "\tChange the amount of empty lines between individual blocks\n"
				+ "\t\tExample: '" + C_GREEN_U + "vain --spacing 3" + C_OFF 
					+ "' produces three empty lines after each block\n"
				+ "\tDefault: " + int_st(spacing) + "\n"
			},
			{"until",
				s("Usage of --until:\n")
				+ "\tDefine until where the scroll file should be read\n"
				+ "\tThis can be used to avoid long wait times or Out-Of-Memory "
					+ "situations when reading from very large files\n"
				+ "\tNote that vainglorious does NOT read until the end of the "
					+ "current block, it does a hard stop as soon as the given line is reached.\n"
				+ "\t\tExample: '" + C_GREEN_U + "vain --until 180 --scrollfile scroll.txt" + C_OFF
					+ "' reads until line 180 from the file \"scroll.txt\"\n"
				+ "\tDefault: The scrollfile is read until EOF\n"
			}
			// TODO: Add entries for every flag
		};
	public:
		void process(int argc, char* argv[]);
		void makepairs();
		 
		std::string get_file() { return file; }
		int get_limit() { return limit; }
		bool get_dry() { return dry; }
		bool get_forcedraw() { return forcedraw; }
		int get_spacing() { return spacing; }
		int get_read_until() { return read_until; }
		 
		int get_themeid() { return themeid; }
		/* Returns either default theme or custom theme */
		std::vector<Color> get_theme();
		bool get_show_cursor() { return show_cursor; }
		/* Returns curcol of theme_id when custom_cur is not set,
		 * custom_cur content if otherwise
		 */
		std::vector<unsigned char> get_curtheme();
};
