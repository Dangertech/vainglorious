#pragma once
#include <vector>
#include <string>

class Args
{
	private:
		std::string file = DEF_FILE;
		bool dry = false;
		int limit = 4;
		std::vector<std::string> switches =
		{
			"-f",
			"--file",
			"-s",
			"--scroll-mode",
			"-l",
			"--limit",
			"-c",
			"--color",
			"--debug",
			"--dry",
			"--help"
		};
		void process_file(int &i, int argc, char * argv[]);
		void process_limit(int &i, int argc, char * argv[]);
	public:
		void process(int argc, char* argv[]);
		std::string get_file() { return file; }
		bool get_dry() { return dry; }
		int get_limit() { return limit; }
};
