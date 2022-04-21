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

void Render::add_char(char c, int c_pair)
{
	if (grid.size() == 0)
		grid.push_back(std::vector<Cell>()); // Failsafe
	
	if (c != '\n')
		grid[grid.size()-1].push_back(Cell(c, c_pair));
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
	if (grid.size())
		add_char('\n', 1);
	for (int i = 0; i<line.size(); i++)
	{
		add_colored_char(line[i], col_data);
	}
}

void Render::add_colored_char(char c, std::vector<Color> col_data)
{
	// No more colors of the same type, assign a
	// new color to hand out
	if (streak_left == 0)
	{
		current_col = random_col(col_data);
		// Get a random integer between second and first of app_length
		Util util;
		streak_left = util.random_int(current_col.pair_prob.app_length.first, 
				current_col.pair_prob.app_length.second);
	}
	add_char(c, current_col.pair_prob.pair_id);
	streak_left--;
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
				break; // Stop rendering if text is beyond terminal bounds
			attron(COLOR_PAIR(grid[i][j].col_id));
			printw("%c", grid[i][j].c);
			attroff(COLOR_PAIR(grid[i][j].col_id));
			lastxpos = getcurx(stdscr);
		}
		// If the next line is empty,
		// lastxpos isn't updated because
		// the loop doesn't even run
		if (grid[i].size() == 0)
			lastxpos = getcurx(stdscr);
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
	move(0, 0);
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
	// Lines into a block
	int lines = 0;
	// Characters into a line on a block
	int chars = 0;
	/* If to_space is 0, everything
	 * runs normally, lines of blocks
	 * get added; If it's not 0, an empty line
	 * is inserted instead and to_space is decreased
	 * by one
	 */
	int to_space = 0;
	/* To avoid spacing on the first block to appear */
	bool first_space = true;
	 
	while (1)
	{
		// Wait for continuation
		ch = getch();
		if (ch == 4) // CTRL-D
			break;
		 
		// Place new characters and render them
		// If there's something to space, enter a new line instead!
			/* Blocks are an exception:
			 * When enabled, the spacing is
			 * run the same input as the rest
			 * of the block to not interrupt the flow
			 */
		for (int times = 0; times < my_args.get_speed(); times++)
		{
			// Setup blocks
			
			/* If everything in the block has been used,
			 * set new block and reset blockpos
			 */
			if (lines >= myblock.size())
			{
				myblock = my_scroll.rblock();
				lines = 0;
				// "Query" the spacing
				if (first_space)
					first_space = false;
				else
					to_space = my_args.get_spacing();
			}
			if (to_space == 0 || my_args.get_style() == BLOCK)
			{
				switch(my_args.get_style())
				{
					case LINE:
						add_line(myblock[lines].c_str(), theme);
						lines++;
						break;
					case WORD:
						while (myblock[lines][chars] != ' ')
						{
							add_colored_char(myblock[lines][chars], theme);
							chars++;
							if (chars >= myblock[lines].size())
							{
								chars = 0;
								add_char('\n', 1);
								lines++;
								// Fill up to the next real character
								if (lines < myblock.size())
								{
									while (myblock[lines][chars] == '\t')
									{
										add_char(myblock[lines][chars], 1);
										chars++;
									}
								}
								// Ensure at least one input per line
								break;
							}
						}
						if (lines < myblock.size())
						{
							while(myblock[lines][chars] == ' ')
							{
								add_colored_char(myblock[lines][chars], theme);
								chars++;
							}
						}
						break;
					case CHARACTER:
						// Skip tabs (User doesn't have to press keys for them)
						while (myblock[lines][chars] == '\t')
						{
							add_char(myblock[lines][chars], 1); 
							chars++;
						}
						add_colored_char(myblock[lines][chars], theme);
						chars++;
						// Break new line
						if (chars >= myblock[lines].size())
						{
							chars = 0;
							add_char('\n', 1);
							lines++;
						}
						break;
					case BLOCK:
						// Do the spacing first
						while(to_space > 0)
						{
							add_char('\n', 1);
							to_space--;
						}
						for (int i = 0; i<myblock.size(); i++)
						{
							for (int j = 0; j<myblock[i].size(); j++)
							{
								add_colored_char(myblock[i][j], theme);
							}
							add_char('\n', 1);
						}
						// Move up
						int scrlimit = getmaxy(stdscr)-my_args.get_limit();
						while (grid.size() > scrlimit)
							move_up();
						// Overflow the lines so a new block is assigned next input
						lines = myblock.size()+1;
						break;
				}
			}
			else
				add_char('\n', 1);
			 
			// Start moving up when the text has advanced far enough
			int scrlimit = getmaxy(stdscr)-my_args.get_limit();
			if (scrlimit < 0)
				scrlimit = 0;
			if (grid.size() > scrlimit)
				move_up();
			 
			// to_space management
			 
			if (to_space > 0)
				to_space--;
		}
		
		// Clear the screen every time something happens
		if (my_args.get_forcedraw())
			cleardraw();
		render_grid(); // Render dat shit!
	}
	endwin();
	// Reset cursor color
	change_cur_color({255, 255, 255});
	return 0;
}
