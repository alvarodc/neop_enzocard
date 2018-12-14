#include "caesarencryption.h" 
#include "stringhelper.h"
#include "stringbuilder.h"

namespace neopenzocard {
 	std::string CaesarEncryption::Encipher(const std::string & input)
	{
		std::string result = "";
		for (auto c : input)
		{
			result = result + StringHelper::ToString(Cipher(c, Key));
		}
		return ChangeNumbers(result);
	}

	std::string CaesarEncryption::Decipher(const std::string & input)
	{
		std::string result = "";
		for (auto c : input)
		{
			result = result + StringHelper::ToString(Cipher(c, 26 - Key));
		}
		return ChangeNumbers(result);
	}

	char CaesarEncryption::Cipher(char ch, int key)
	{
		if (!std::isalpha(ch))
		{
			return ch;
		}

		auto d = std::isupper(ch) ? 'A' : 'a';
		return static_cast<char>((ch + key - d) % 26 + d);
	}

	std::string CaesarEncryption::ChangeNumbers(const std::string & output)
	{
		auto builder = new StringBuilder();
		for (auto c : output)
		{
			auto aux = c;
			if (std::isdigit(aux))
			{
				builder->append(Numbers[std::stoi(StringHelper::ToString(aux))]);
			}
			else
			{
				builder->append(aux);
			}
		}

		auto result = builder->toString();

		delete builder;
		return result;
	}
}