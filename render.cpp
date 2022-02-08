#include "render.h"
#include <ncurses.h>

Render render;

int Render::run(Args my_args)
{
	initscr();
	char ch = getch();
	printw(&ch);
	endwin();
	return 0;
}
