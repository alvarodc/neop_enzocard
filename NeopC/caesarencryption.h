#pragma once 
#include <vector> 

namespace neopenzocard {
	class CaesarEncryption
	{
	public:
		std::string Encipher(const std::string &input);
		std::string Decipher(const std::string &input);
	private:
		static constexpr int Key = 3;
		std::vector<int> const Numbers = { 2, 5, 0, 6, 9, 1, 3, 8, 7, 4 };
		char Cipher(char ch, int key);
		std::string ChangeNumbers(const std::string &output);
	};
}

