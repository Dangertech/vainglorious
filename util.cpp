#include <string>
#include <iostream>
#include <random>
#include "util.h"

int Util::sixteen_to_ten(char ten_str)
{
	ten_str = tolower(ten_str);
	if(isalpha(ten_str))
	{
		if (ten_str < 103)
			return ten_str-87;
		else
			// That's more than an f and not a hex code
			return ERROR;
	}
	else
		return ten_str-48;
}

bool Util::is_number(std::string string)
{
	for (int i = 0; i<string.size(); i++)
	{
		if (!std::isdigit(string[i]))
			return false;
	}
	return true;
}

std::vector<unsigned char> Util::hextorgb(std::string hex)
{
	std::vector<unsigned char> ret;
	int red = sixteen_to_ten(hex[1])*16 + sixteen_to_ten(hex[2]);
	if (red >= 0 && red <= 255)
		ret.push_back(red);
	else
		throw 1;
	int green = sixteen_to_ten(hex[3])*16 + sixteen_to_ten(hex[4]);
	if (green >= 0 && green <= 255)
		ret.push_back(green);
	else
		throw 2;
	int blue = sixteen_to_ten(hex[5])*16 + sixteen_to_ten(hex[6]);
	if (blue >= 0 && blue <= 255)
		ret.push_back(blue);
	else
		throw 3;
	return ret;
}

std::vector<std::string> 
Util::split_at(std::string splitchar, std::string input)
{
	std::vector<std::string> ret;
	int pointer = 0;
	 
	std::string temp;
	while (1 == 1)
	{
		while (input[pointer] != splitchar[0])
		{
			if (pointer >= input.size())
			{
				if (temp.size())
					ret.push_back(temp);
				return ret;
			}
			temp += input[pointer];
			pointer++;
		}
		ret.push_back(temp);
		temp = "";
		int spoint = 0;
		while (splitchar[spoint] == input[pointer])
		{
			spoint++;
			pointer++;
		}
	}
}

int Util::random_int(int min, int max)
{
	// Seeder
	std::random_device rd;
	 
	std::mt19937 gen(rd());
	 
	std::uniform_int_distribution<int> dist(min, max);
	 
	return dist(gen);
}

std::string Util::to_lower(std::string input)
{
	std::string lower;
	for (int i = 0; i<input.size(); i++)
	{
		lower += std::tolower(input[i]);
	}
	return lower;
}
