#pragma once
#include <array>
#include "args.h"
#include "file.h"


class Render
{
	private:
		/* Driver grid that characters are put into
		 * and that is rendered every frame, offset by one
		 */
		struct Cell
		{
			char c;
			int col_id;
			Cell(char my_c, int my_col_id)
			{
				c = my_c;
				col_id = my_col_id;
			}
		};
		std::vector<std::vector<Cell>> grid;
		 
		void add_char(char c, int col_id);
		void render_grid();
		void move_up();

		struct PairProb
		{
			int pair_id; // The color pair id
			std::pair<int, int> app_length; // For how long it appears
			int prob; // Probability to start appearing
			PairProb(int my_id, std::pair<int, int> my_length, float my_prob)
			{
				pair_id = my_id;
				app_length = my_length;
				prob = my_prob;
			}
		};
		/* Gets a random pair with the defined probabilities */
		int random_pair(std::vector<PairProb> pair_data);
		void add_line(std::string line, std::vector<PairProb>);
		void cleardraw();
	public:
		int run(Args, File);
};


