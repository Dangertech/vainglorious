#include <string>
#include <ncurses.h>
#include <random>
#include <iostream>
#include "render.h"
#include "file.h"
#include "util.h"

void Render::move_up()
{
	grid.erase(grid.begin());
}

void Render::add_char(char c, int col_id)
{
	if (grid.size() == 0)
		grid.push_back(std::vector<Cell>()); // Failsafe
	 
	if (c != '\n')
		grid[grid.size()-1].push_back(Cell(c, col_id));
	else
	{
		grid.push_back(std::vector<Cell>());
	}
	/* Actually, through this, there is
	 * ALWAYS AN EMPTY NEW LINE at the end of the
	 * text when a newline is cast from add_line(), for example
	 */
}

void Render::change_cur_color(std::vector<unsigned char> rgb)
{
	printf("\e]12;#%.2x%.2x%.2x\a", rgb[0], rgb[1], rgb[2]);
}

Color Render::random_col(std::vector<Color> col_data)
{
	// Basically our seed without using the time
	std::random_device rd;
	std::mt19937 gen(rd());

	// Get weights
	std::vector<int> weights(col_data.size());
	// Fill weights with defined weights from probability
	for (int i = 0; i<col_data.size(); i++)
		weights[i] = col_data[i].pair_prob.prob;

	std::discrete_distribution<> dist(weights.begin(), weights.end());
	 
	/* dist(gen) returns a color index according to the weights
	 * The whole chosen color is returned
	 */
	return col_data[dist(gen)]; 
}

void Render::add_line(std::string line, std::vector<Color> col_data)
{
	/* To circumvent multiple difficulties with
	 * the new line problem, this function just doesn't
	 * finish a line at the end but instead finishes it at
	 * the beginning of it's cast
	 */
	if (grid.size() > 0) // Failsafe
		if (grid[grid.size()-1].size() > 0)
			add_char('\n', 1);
	for (int i = 0; i<line.size(); i++)
	{
		Color col;
		// Decide Color pair
		if (col_data.size() > 1)
		{
			// Generate colpair from pair_data
			col = random_col(col_data);
		}
		else if (col_data.size() == 1)
			col = col_data[0]; // Just save the resources
		
		// Get a random integer between second and first of app_length
		Util util;
		int length = util.random_int(col.pair_prob.app_length.first, 
				col.pair_prob.app_length.second);
		for (int app_count = 0; app_count < length; app_count++)
		{
			add_char(line[i], col.pair_prob.pair_id);
			if (app_count < length-1)
			{
				if (i+1 < line.size())
					i++;
				else
					break; // Break loop when line is finished now
			}
		}
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
			if (getcurx(stdscr) > getmaxx(stdscr)-2)
				break; // Stop rendering
			attron(COLOR_PAIR(grid[i][j].col_id));
			printw("%c", grid[i][j].c);
			attroff(COLOR_PAIR(grid[i][j].col_id));
			lastxpos = getcurx(stdscr);
		}
		printw("\n");
	}
	// Prepare y pos for cursor
	int lastypos = grid.size()-1;
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
	std::vector<Color> theme = my_args.get_theme();
	/* Set cursor color
	 * This has to be done before initscr() is called
	 */
	change_cur_color(my_args.get_curtheme());
	 
	initscr();
	noecho(); // Turn off printing of pressed character
	start_color(); // Use Colors
	// Disable cursor in case of -c
	if (!my_args.get_show_cursor())
		curs_set(0);
	 
	// Init colors
	my_args.makepairs();
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
		 
		add_line(myblock[blockpos].c_str(), theme);
		// Clear the screen every time something happens
		if (my_args.get_forcedraw())
			cleardraw();
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
	// Reset cursor color
	printf("\e]12;white\a");
	return 0;
}
