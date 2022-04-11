#include "theme.h"

std::vector<Color> DefTheme::get_theme(int theme_id)
{
	if (theme_id < themecols.size())
		return themecols[theme_id];
	else
		return themecols[0];
}

std::vector<unsigned char> DefTheme::get_curcol(int theme_id)
{
	if (theme_id < curcols.size())
		return curcols[theme_id];
	else
		return curcols[0];
}
