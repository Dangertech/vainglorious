#pragma once
#include <vector>
#include <string>
 
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

// Holds information about all predefined themes
class DefTheme
{
	public:
		std::vector<std::string> get_themenames() {return themenames;}
		std::vector<std::string> get_colnames() {return colnames;}
		std::vector<Color> get_theme(int theme_id);
		std::vector<unsigned char> get_curcol(int theme_id);
	private:
		/* The input and display name for the default
		 * themes
		 * The sort order implies the id of each theme
		 * (e.g. the green theme has the id 0)
		 */
		std::vector<std::string> themenames =
		{
			"green",
			"gold",
			"yellow",
			"rainbow",
			"red",
			"blue",
			"cyan",
			"orange",
			"purple",
			"vaporwave",
			"gray"
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
			// These awesome colors are stolen from https://github.com/st3w/neo
			// GREEN
			{
				// COLORID, R,   G,   B,ColPair,length,probability
				{234,       71,  141, 83,  {1, {8,10}, 1} },
				{22,        149, 243, 161, {2, {8,10}, 1} },
				{28,        188, 596, 318, {3, {1,2}, 7} },
				{35,        188, 714, 397, {4, {1,3}, 8} },
				{78,        227, 925, 561, {5, {4,8}, 9} },
				{84,        271, 973, 667, {6, {3,5}, 12} },
				{159,       667, 1000, 941,{7, {3,6}, 7} }
			},
			// GOLD
			{
				{58, 839, 545, 216,   {1, {8, 10}, 2} },
				{94, 905, 694, 447,   {2, {8, 10}, 6} },
				{172, 945, 831, 635,  {3, {8, 10}, 4} },
				{178, 1000, 922, 565, {4, {8, 10}, 2} },
				{228, 1000, 953, 796, {5, {8, 10}, 2} },
				{230, 976, 976, 968,  {6, {8, 10}, 1} }
			},
			// YELLOW
			{
				// Default Xterm colors
				{100, -1,-1,-1, {1, {1, 9}, 2} },
				{142, -1,-1,-1, {2, {3, 7}, 2} },
				{184, -1,-1,-1, {3, {3, 7}, 4} },
				{226, -1,-1,-1, {4, {3, 7}, 5} },
				{227, -1,-1,-1, {5, {3, 7}, 3} },
				{229, -1,-1,-1, {6, {2, 4}, 4} },
				{230, -1,-1,-1, {7, {6, 12}, 3} }
			},
			// RAINBOW (cancer)
			{
				{196, -1,-1,-1, {1, {1, 6}, 1} },
				{208, -1,-1,-1, {2, {1, 6}, 1} },
				{226, -1,-1,-1, {3, {1, 6}, 1} },
				{46,  -1,-1,-1, {4, {1, 6}, 1} },
				{21,  -1,-1,-1, {5, {1, 6}, 1} },
				{93,  -1,-1,-1, {6, {1, 6}, 1} },
				{201, -1,-1,-1, {7, {1, 6}, 1} }
			},
			// RED
			{
				{234, -1,-1,-1, {1, {6, 8}, 1} },
				{52, -1,-1,-1,  {2, {3, 5}, 1} },
				{88, -1,-1,-1,  {3, {2, 4}, 3} },
				{124, -1,-1,-1, {4, {3, 5}, 6} },
				{160, -1,-1,-1, {5, {2, 3}, 5} },
				{196, -1,-1,-1, {6, {3, 4}, 7} },
				{197,255,56,59, {7, {4, 6}, 4} },
				{217, -1,-1,-1, {8, {2, 4}, 2} }
			},
			// BLUE
			{
				{234, -1,-1,-1, {1, {3, 6}, 1} },
				{17, -1,-1,-1,  {2, {3, 6}, 1} },
				{18, -1,-1,-1,  {3, {3, 8}, 1} },
				{19, -1,-1,-1,  {4, {3, 6}, 6} },
				{20, -1,-1,-1,  {5, {3, 6}, 6} },
				{21, -1,-1,-1,  {6, {3, 6}, 2} },
				{75, -1,-1,-1,  {7, {2, 5}, 4} },
				{159, -1,-1,-1, {8, {2, 5}, 1} }
			},
			// CYAN
			{
				{24, -1,-1,-1,  {1, {1, 1}, 1} },
				{25, -1,-1,-1,  {2, {1, 1}, 1} },
				{31, -1,-1,-1,  {3, {1, 1}, 1} },
				{32, -1,-1,-1,  {4, {1, 1}, 1} },
				{38, -1,-1,-1,  {5, {1, 1}, 1} },
				{45, -1,-1,-1,  {6, {1, 1}, 1} },
				{159, -1,-1,-1, {7, {1, 1}, 1} }
			},
			// ORANGE
			{
				{52, -1,-1,-1,  {1, {2,  5}, 1} },
				{94, -1,-1,-1,  {2, {6, 10}, 2} },
				{130, -1,-1,-1, {3, {6, 10}, 5} },
				{166, -1,-1,-1, {4, {6, 10}, 7} },
				{202, -1,-1,-1, {5, {6, 10}, 8} },
				{208, -1,-1,-1, {6, {6, 10}, 7} },
				{231, -1,-1,-1, {7, {2,  3}, 0} } // Simply too bright
			},
			// PURPLE
			{
				{60, -1,-1,-1,  {1, {1, 1}, 1} },
				{61, -1,-1,-1,  {2, {1, 1}, 1} },
				{62, -1,-1,-1,  {3, {1, 1}, 1} },
				{63, -1,-1,-1,  {4, {1, 1}, 1} },
				{69, -1,-1,-1,  {5, {1, 1}, 1} },
				{111, -1,-1,-1, {6, {1, 1}, 1} },
				{225, -1,-1,-1, {7, {1, 1}, 1} }
			},
			// VAPORWAVE
			{
				{53, -1,-1,-1,  {1, {6, 10}, 2} },
				{54, -1,-1,-1,  {2, {6, 10}, 2} },
				{55, -1,-1,-1,  {3, {6, 10}, 2} },
				{134, -1,-1,-1, {4, {6, 10}, 2} },
				{177, -1,-1,-1, {5, {6, 10}, 2} },
				{219, -1,-1,-1, {6, {6, 10}, 2} },
				{214, -1,-1,-1, {7, {6, 10}, 2} },
				{220, -1,-1,-1, {8, {6, 10}, 2} },
				{227, -1,-1,-1, {9, {6, 10}, 2} },
				{229, -1,-1,-1, {10, {6, 10}, 1} },
				{87, -1,-1,-1,  {11, {6, 10}, 1} },
				{123, -1,-1,-1, {12, {6, 10}, 1} },
				{159, -1,-1,-1, {13, {6, 10}, 1} },
				{195, -1,-1,-1, {14, {6, 10}, 1} },
				{231, -1,-1,-1, {15, {6, 10}, 1} },
			},
			// GRAY
			{
				{234, -1,-1,-1, {1, {6, 10}, 1} },
				{237, -1,-1,-1, {2, {6, 10}, 1} },
				{240, -1,-1,-1, {3, {6, 10}, 1} },
				{243, -1,-1,-1, {4, {6, 10}, 1} },
				{246, -1,-1,-1, {5, {6, 10}, 1} },
				{249, -1,-1,-1, {6, {6, 10}, 1} },
				{251, -1,-1,-1, {7, {6, 10}, 1} },
				{252, -1,-1,-1, {8, {6, 10}, 1} },
				{231, -1,-1,-1, {9, {6, 10}, 1} },
			}
		};
		/* Cursor colors corresponding to their schemes */
		std::vector<std::vector<unsigned char>> curcols =
		{
			// GREEN
			{68, 244, 167},
			// GOLD
			{188, 120, 12},
			// YELLOW
			{255, 255, 0},
			// RAINBOW
			{227, 67, 255},
			// RED
			{187, 4, 31},
			// BLUE
			{0, 0, 255},
			// CYAN
			{22, 158, 188},
			// ORANGE
			{180, 119, 20},
			// PURPLE
			{58, 39, 206},
			// VAPORWAVE
			{130, 97, 180},
			// GRAY
			{97, 102, 103}
		};
};
