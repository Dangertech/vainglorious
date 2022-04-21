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
		 
		void add_char(char c, int c_pair);
		void render_grid();
		void move_up();
		
		void change_cur_color(std::vector<unsigned char> rgb);
		 
		/* Gets a random pair with the defined probabilities */
		Color random_col(std::vector<Color> );
		void add_line(std::string line, std::vector<Color> col_data);
		void cleardraw();
		 
		 
	public:
		int run(Args, File);
};
