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
		std::vector<std::vector<char>> grid;
		void move_up();
		void add_line(std::string line);
		void render_grid();
	public:
		int run(Args, File);
};


