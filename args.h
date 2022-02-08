#pragma once
#include <vector>
#include <string>

class Args
{
	private:
		std::string file = DEF_FILE;
		std::vector<std::string> switches =
		{
			"-f",
			"--file",
			"-s",
			"--scroll-mode",
			"-c",
			"--color",
			"--debug",
			"--help"
		};
		void process_file(int &i, int argc, char * argv[]);
	public:
		void process(int argc, char* argv[]);
		std::string get_file() { return file; }
} extern args;
