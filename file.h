#pragma once
#include <string>
#include <vector>

class File
{
	private:
		/* random offset; 
		 * Increases by one every time rblock() has been called
		 * Else, the same block would be chosen in each second
		 */
		int roff = 0; 
		std::vector<std::vector<std::string>> blocks;
	public:
		int crunch_file(std::string scroll); // Parse scroll and fill blocks
		std::vector<std::string> rblock(); // Get a random block from the list
		 
		std::vector<std::vector<std::string>> get_blocks() { return blocks; }
};
