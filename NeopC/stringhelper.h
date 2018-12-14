#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <cctype>

class StringHelper
{
public:

	static std::vector<std::string> Split(const std::string &source, char delimiter)
	{
		std::vector<std::string> output;
		std::istringstream ss(source);
		std::string nextItem;

		while (std::getline(ss, nextItem, delimiter))
		{
			output.push_back(nextItem);
		}

		return output;
	}
		
	static std::string Join(std::string const& separator, std::vector<std::string> &arr)
	{
		auto begin = arr.begin();
		auto end = arr.end();

		std::ostringstream result;
		if (begin != end)
			result << *begin++;
		while (begin != end)
			result << separator << *begin++;
		return result.str();
	}

	static std::vector<std::string> SkipFirst(std::vector<std::string> &arr)
	{
		auto aux = std::vector<std::string>(arr.size() - 1);
		for (size_t i = 1; i < arr.size(); i++)
		{
			aux[i - 1] = arr[i];
		}
		return aux;
	}

	template<typename T>
	static std::string ToString(const T &subject)
	{
		std::ostringstream ss;
		ss << subject;
		return ss.str();
	}

	/*template<typename T>
	static T FromString(const std::string &subject)
	{
		std::istringstream ss(subject);
		T target;
		ss >> target;
		return target;
	}*/
};

