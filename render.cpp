#include <string>
#include <ncurses.h>
#include "render.h"
#include "file.h"

Render render;

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
		 
		printw("%s\n", myblock[blockpos].c_str());
		blockpos++;
	}
	endwin();
	return 0;
}
