#include <iostream>
#include "args.h"
#include "util.h"
#include "const.h"

Args args;

void Args::process(int argc, char* argv[])
{
	for (int i = 1; i<argc; i++)
	{
		int match = util.veccmp<std::string>(std::string(argv[i]), switches);
		switch (match)
		{
			case 0:
				process_file(i, argc, argv);
				break;
			default:
				std::cout << "Invalid argument!" << std::endl;
				break;
		}
	}
}

void Args::process_file(int &i, int argc, char* argv[])
{
	i++;
	file = argv[i];
}
