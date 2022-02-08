#include <iostream>
#include "args.h"
#include "render.h"

int main(int argc, char* argv[])
{
	std::cout << "Processing Arguments..." << std::endl;
	args.process(argc, argv);
	std::cout << "Target Scroll File Is: " << args.get_file() << std::endl;
	std::cout << "Done!" << std::endl;
	std::cout << "Initializing Display..." << std::endl;
	render.run(args);
	// initscr() starts here
}
