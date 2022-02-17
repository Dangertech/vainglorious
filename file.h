#pragma once
#include <string>
#include <vector>

class File
{
	private:
		std::vector<std::vector<std::string>> blocks;
	public:
		int crunch_file(std::string scroll); // Parse scroll and fill blocks
		std::vector<std::vector<std::string>> get_blocks() { return blocks; }
		//TODO: std::string rblock(); // Get a random block from the list
};

extern File file;
