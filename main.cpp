#include <iostream>
#include "args.h"
#include "file.h"
#include "render.h"
#include "const.h"

int main(int argc, char* argv[])
{
	std::cout << "Processing Arguments..." << std::endl;
	args.process(argc, argv);
	std::cout << "Target Scroll File Is: " << args.get_file() << std::endl;
	 
	std::cout << "Crunching through Scroll file..." << std::endl;
	if (file.crunch_file(args.get_file()) == ERROR)
		std::cout << "Error opening scroll! Please check file ownership!" << std::endl;
	std::cout << "Done!" << std::endl;
	std::cout << "Total blocks found: " << file.get_blocks().size() << std::endl;
	std::cout << file.get_blocks()[0][0] << std::endl; // Print the first line of the first block
	
	std::cout << "Initializing Display..." << std::endl;
	// initscr() starts here
	render.run(args);
}
