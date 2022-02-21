#include <iostream>
#include "args.h"
#include "util.h"
#include "const.h"

void Args::process(int argc, char* argv[])
{
	for (int i = 1; i<argc; i++)
	{
		int match = util.veccmp<std::string>(std::string(argv[i]), switches);
		switch (match)
		{
			case 0: case 1:
				process_file(i, argc, argv);
				break;
			case 4: case 5:
				process_limit(i, argc, argv);
				break;
			case 9:
				dry = true;
				break;
			default:
				std::cout << "Invalid argument!" << std::endl;
				break;
		}
	}
}

void Args::process_file(int &i, int argc, char* argv[])
{
	if (i < argc-1)
	{
		i++;
		file = argv[i];
	}
	else
	{
		std::cout << "Usage of -f/--file:" << std::endl
				  << "\tSpecify a scroll file to read from: vain --file scrollfile.txt\n";
		exit(1);
	}
}

void Args::process_limit(int &i, int argc, char* argv[])
{
	if (i < argc-1)
	{
		i++;
		if (atoi(argv[i]) < 1)
			limit = 1;
		else
			limit = atoi(argv[i]);
	}
	else
	{
		std::cout << "Usage of -l/--limit:" << std::endl
				  << "\tSpecify until where the text should go before starting to scroll up" << std::endl
				  << "\tExample: 'vain --limit 3' scrolls up to 3 lines before the terminal ends" << std::endl;
		exit(1);
	}
}
