#include <iostream>
#include "args.h"
#include "file.h"
#include "render.h"
#include "const.h"
#include "util.h"

Args args;
File scrollfile;
Render render;

int main(int argc, char* argv[])
{
	// Process Arguments
	std::cout << "Processing Arguments..." << std::endl;
	args.process(argc, argv);
	 
	// Crunch through scrollfile
	std::cout << "Target Scroll File Is: " << args.get_file() << std::endl;
	std::cout << "Crunching through Scroll file...";
	if (scrollfile.crunch_file(args.get_file()) == ERROR)
	{
		std::cout << "Error opening scroll! Please check file ownership!" << std::endl;
		return 1;
	}
	std::cout << "Done!" << std::endl;
	std::cout << "Total blocks found: " << scrollfile.get_blocks().size() << std::endl;
	 
	 
	// Check if dry run was specified
	if (args.get_dry())
	{
		std::cout << "Dry run, exiting!" << std::endl;
		return 5;
	}

	std::cout << "Initializing Display..." << std::endl;
	// initscr() starts here
	if (render.run(args, scrollfile) == 0)
	{
		std::cout << "Exiting gracefully!" << std::endl;
		return 0;
	}
	return ERR_UNKNOWN;
}
