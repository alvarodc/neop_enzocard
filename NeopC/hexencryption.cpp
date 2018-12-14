#include "hexencryption.h"
#include <iostream>
#include <sstream>
#include "stringhelper.h"

namespace neopenzocard {
	std::string HexEncryption::Encrypt(const std::string & usn)
	{
		auto bUsn = ToByteArray(ToHexString(usn));
		auto bKey = ToByteArray(ToHexString("NeopEnzocard"));

		auto block_key = BlockCopy(bKey);
		auto block_usn = BlockCopy(bUsn);

		auto int_key = ToInt64(block_key, 0); //constant key value: i1 = 8032854129886848334;
		auto int_usn = ToInt64(block_usn, 0);

		auto sum = int_key + int_usn;

		auto bSum = GetBytes(sum);

		std::vector<std::string> result(bSum.size());

		for (size_t i = 0; i < bSum.size(); i++)
		{
			result[i] = ToHexString(StringHelper::ToString(bSum[i]));
		}

		return  StringHelper::Join(" ", result);
	}

	std::string HexEncryption::Decrypt(const std::string & block)
	{
		auto bKey = ToByteArray(ToHexString("NeopEnzocard"));
		auto block_key = BlockCopy(bKey);
		auto bSum = ToByteArray(block);

		auto sum = ToInt64(bSum, 0);
		auto int_key = ToInt64(block_key, 0); //i1 = 8032854129886848334;
		auto int_usn = sum - int_key;

		return GetString(GetBytes(int_usn));
	}

	std::string HexEncryption::ToHexString(const std::string & s)
	{
		static const char* const lut = "0123456789ABCDEF";
		size_t len = s.length();

		std::string output;
		output.reserve(2 * len);
		for (size_t i = 0; i < len; ++i)
		{
			const unsigned char c = s[i];
			output.push_back(lut[c >> 4]);
			output.push_back(lut[c & 15]);
		}
		return output;
	}

	std::vector<unsigned char> HexEncryption::BlockCopy(std::vector<unsigned char> arr)
	{
		const int size = 16;
		size_t arrSize = arr.size();
		std::vector<unsigned char> bytes(size);
		for (size_t j = 0; j < size; ++j)
		{
			bytes[j] = (j >= arrSize) ? 0 : arr[j];
		}

		return bytes;
	}

	std::string HexEncryption::GetString(std::vector<unsigned char> arr)
	{
		const int size = 8;
		std::vector<std::string> bytes(size);
		for (int j = 0; j < size; ++j)
		{
			bytes[j] = arr[j];
		}

		return StringHelper::Join("", bytes);
	}


	std::vector<unsigned char> HexEncryption::ToByteArray(const std::string& hex) {
		std::vector<unsigned char> bytes;

		for (unsigned int i = 0; i < hex.length(); i += 2) {
			std::string byte_string = hex.substr(i, 2);
			unsigned char byte = (unsigned char)strtol(byte_string.c_str(), NULL, 16);
			bytes.push_back(byte);
		}

		return bytes;
	}

	// https://referencesource.microsoft.com/#mscorlib/system/bitconverter.cs
	// C# to C++ conversion.
	// The BitConverter class contains methods for
	// converting an array of bytes to one of the base data 
	// types, as well as for converting a base data type to an
	// array of bytes.
	// Converts an array of bytes into a long.
	int64_t HexEncryption::ToInt64(std::vector<unsigned char> &value, size_t start_index)
	{
		if (value.empty())
		{
			return 0;
		}

		if (static_cast<unsigned int>(start_index) >= value.size())
		{
			return 0;
		}

		if (start_index > value.size() - 8)
		{
			return 0;
		}

		unsigned char * pbyte = &value[start_index];
		if (start_index % 8 == 0)
		{ // data is aligned
			return *((int64_t *)pbyte);
		}
		else
		{
			if (_isLittleEndian)
			{
				int i1 = (*pbyte) | (*(pbyte + 1) << 8) | (*(pbyte + 2) << 16) | (*(pbyte + 3) << 24);
				int i2 = (*(pbyte + 4)) | (*(pbyte + 5) << 8) | (*(pbyte + 6) << 16) | (*(pbyte + 7) << 24);
				return static_cast<unsigned int>(i1) | (static_cast<int64_t>(i2) << 32);
			}
			else
			{
				int i1 = (*pbyte << 24) | (*(pbyte + 1) << 16) | (*(pbyte + 2) << 8) | (*(pbyte + 3));
				int i2 = (*(pbyte + 4) << 24) | (*(pbyte + 5) << 16) | (*(pbyte + 6) << 8) | (*(pbyte + 7));
				return static_cast<unsigned int>(i2) | (static_cast<int64_t>(i1) << 32);
			}
		}
	}

	// https://referencesource.microsoft.com/#mscorlib/system/bitconverter.cs
	// Converts a long into an array of bytes with length 16.
	std::vector<unsigned char> HexEncryption::GetBytes(int64_t value)
	{
		std::vector<unsigned char> bytes(16);
		unsigned char* b = &bytes[0];
		*((long long*)b) = value;
		return bytes;
	}
}