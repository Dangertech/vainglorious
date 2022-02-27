#include <string>
#include <ncurses.h>
#include "render.h"
#include "file.h"
#include "util.h"

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
	/* This is used to move the
	 * cursor to the position before the
	 * last newline character so that it really
	 * looks like the cursor typed the lines/characters
	 */
	int lastxpos = 0;
	 
	move(0, 0);
	for (int i = 0; i<grid.size(); i++)
	{
		for (int j = 0; j<grid[i].size(); j++)
		{
			printw("%c", grid[i][j]);
			lastxpos = getcurx(stdscr);
		}
		printw("\n");
	}
	// Prepare y pos for cursor
	int lastypos = getcury(stdscr);
	if (lastypos != getmaxy(stdscr)-1)
		lastypos--;
	move(lastypos, lastxpos); // move cursor
}

void Render::cleardraw()
{
	for (int y = 0; y<getmaxy(stdscr); y++)
	{
		move(y, 0);
		for (int x = 0; x<getmaxx(stdscr); x++)
		{
			printw(" ");
		}
	}
}

int Render::run(Args my_args, File my_scroll)
{
	/* Set cursor color
	 * This has to be done before initscr() is called
	 */
	std::string ccolname = my_args.colid_to_string(my_args.get_cur());
	printf("\e]12;%s\a", ccolname.c_str());
	 
	initscr();
	noecho(); // Turn off printing of pressed character
	start_color(); // Use Colors
	// Disable cursor in case of -c
	if (my_args.get_show_cursor())
		curs_set(0);
	 
	// Init colors
	init_pair(1, my_args.get_fg(), my_args.get_bg());
	bkgd(COLOR_PAIR(1));
	attron(COLOR_PAIR(1));
	/* Draw everything once to set the background everywhere
	 * bkgd() or wbkgd() alone leaves a column black at the right 
	 * side of my terminal for some reason
	 */
	cleardraw();
	 
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
	attroff(COLOR_PAIR(1));
	endwin();
	return 0;
}
