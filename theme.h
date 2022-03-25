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
			"gold"
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
		// These awesome colors are stolen from st3w/neo
		std::vector<std::vector<Color>> themecols =
		{
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
				{58, 839, 545, 216, {1, {8, 10}, 1} },
				{94, 905, 694, 447, {2, {8, 10}, 1} },
				{172, 945, 831, 635, {3, {8, 10}, 1} },
				{178, 1000, 922, 565, {4, {8, 10}, 1} },
				{228, 1000, 953, 796, {5, {8, 10}, 1} },
				{230, 976, 976, 968, {6, {8, 10}, 1} }
			}
		};
		/* Cursor colors corresponding to their schemes */
		std::vector<std::vector<unsigned char>> curcols =
		{
			// GREEN
			{68, 244, 167},
			{255, 255, 0}
		};
};
