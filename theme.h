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
			"green"
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
				{234,       71,  141, 83,  {1, {1,4}, 3} },
				{22,        149, 243, 161, {2, {2,3}, 2} },
				{28,        188, 596, 318, {3, {1,1}, 3} },
				{35,        188, 714, 397, {4, {1,1}, 5} },
				{78,        227, 925, 561, {5, {4,8}, 7} },
				{84,        271, 973, 667, {6, {1,1}, 6} },
				{159,       667, 1000, 941,{7, {3,6}, 3} }
			}
		};
		/* Cursor colors corresponding to their schemes */
		std::vector<std::vector<unsigned char>> curcols =
		{
			// GREEN
			{0, 255, 0}
		};
};
