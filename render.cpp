#include "render.h"
#include <ncurses.h>

Render render;

int Render::run(Args my_args)
{
	initscr();
	noecho(); // Turn of printing of pressed character
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
