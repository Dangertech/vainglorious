#include "render.h"
#include "file.h"
#include <ncurses.h>

Render render;

int Render::run(Args my_args, File my_scroll)
{
	initscr();
	noecho(); // Turn off printing of pressed character
	int ch;
	while (1)
	{
		ch = getch();
		if (ch == 4)
			break;
		printw("%i\n", ch);
	}
	endwin();
	return 0;
}
