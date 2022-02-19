#include <iostream>
#include "args.h"
#include "file.h"
#include "render.h"
#include "const.h"

Args args;
File scroll;

int main(int argc, char* argv[])
{
	std::cout << "Processing Arguments..." << std::endl;
	args.process(argc, argv);
	std::cout << "Target Scroll File Is: " << args.get_file() << std::endl;
	 
	std::cout << "Crunching through Scroll file..." << std::endl;
	if (scroll.crunch_file(args.get_file()) == ERROR)
		std::cout << "Error opening scroll! Please check file ownership!" << std::endl;
	std::cout << "Done!" << std::endl;
	std::cout << "Total blocks found: " << scroll.get_blocks().size() << std::endl;
	std::cout << scroll.get_blocks()[0][0] << std::endl; // Print the first line of the first block
	
	std::cout << "Initializing Display..." << std::endl;
	// initscr() starts here
	render.run(args, scroll);
}
