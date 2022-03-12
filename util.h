#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "const.h"

class Util
{
	private:
		// Convert a base 16 digit to it's base 10 equivalent
		int sixteen_to_ten(char ten_str);
	public:
		template <typename T>
		int veccmp(T to_comp, std::vector<T> vec)
		{
			for (long unsigned int i = 0; i<vec.size(); i++)
			{
				if (to_comp == vec[i])
					return i;
			}
			return ERROR;
		}
		/* I know, this makes an unordered_map a lil 
		 * stupid but the performance hit is minimal
		 * and I don't care enough to reengineer with
		 * an std::pair or something
		 */
		template <typename A, typename T>
		A valtokey(std::unordered_map<A, T> map, T val)
		{
			for (auto i = map.begin(); i != map.end(); i++)
			{
				if (i->second == val)
					return i->first;
			}
			return nullptr;
		}
		bool is_number(std::string string);
		std::vector<unsigned char> hextorgb(std::string hex);
};
