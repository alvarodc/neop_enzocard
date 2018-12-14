#pragma once
#include <vector>

namespace neopenzocard {
	class HexEncryption
	{
	public:
		std::string Encrypt(const std::string &usn);
		std::string Decrypt(const std::string &block);
	private:
		const int64_t Key = 8032854129886848334;
		const bool _isLittleEndian = true;
		std::string ToHexString(const std::string &s);
		std::vector<unsigned char> BlockCopy(std::vector<unsigned char> arr);
		std::vector<unsigned char> ToByteArray(const std::string & hex);
		std::string GetString(std::vector<unsigned char> arr);
		int64_t ToInt64(std::vector<unsigned char> &value, size_t start_index);
		std::vector<unsigned char> GetBytes(int64_t value);
	};
}