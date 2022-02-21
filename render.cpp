#include <string>
#include <ncurses.h>
#include "render.h"
#include "file.h"

void Render::move_up()
{
	grid.erase(grid.begin());
}

void Render::add_line(std::string line)
{
	grid.push_back(std::vector<char>());
	for (int i = 0; i<line.size(); i++)
	{
		grid[grid.size()-1].push_back(line[i]);
	}
}

void Render::render_grid()
{
	move(0, 0);
	for (int i = 0; i<grid.size(); i++)
	{
		for (int j = 0; j<grid[i].size(); j++)
		{
			printw("%c", grid[i][j]);
		}
		printw("\n");
	}
}

int Render::run(Args my_args, File my_scroll)
{
	initscr();
	noecho(); // Turn off printing of pressed character
	int ch;
	std::vector<std::string> myblock;
	int blockpos = 0;
	while (1)
	{
		/* If everything in the block has been used,
		 * set new block and reset blockpos
		 */
		if (blockpos >= myblock.size())
		{
			myblock = my_scroll.rblock();
			blockpos = 0;
		}
		 
		ch = getch();
		if (ch == 4) // CTRL-D
			break;
		 
		add_line(myblock[blockpos].c_str());
		render_grid();
		blockpos++;
		// Start moving up when the text has advanced far enough
		int scrlimit = getmaxy(stdscr)-my_args.get_limit();
		if (scrlimit < 0)
			scrlimit = 0;
		if (grid.size() > scrlimit)
			move_up();
	}
	endwin();
	return 0;
}
