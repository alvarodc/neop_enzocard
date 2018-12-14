#include "commands.h"
#include <iostream>
#include "stringhelper.h"
#include "caesarencryption.h"
#include "hexencryption.h"

namespace neopenzocard {

	CaesarEncryption caesar_enc;
	HexEncryption hex_enc;

	void Commands::Enc(std::vector<std::string>& parsed_command)
	{
		if (parsed_command.size() != 2)
		{
			std::cout << "Command error..." << std::endl;
			Help();
		}
		else
		{
			parsed_command = StringHelper::SkipFirst(parsed_command);
			auto usn = StringHelper::Join(" ", parsed_command);

			if (!ValidateUsn(usn))
			{
				std::cout << usn << ": invalid usn..." << std::endl;
			}
			else
			{
				usn = caesar_enc.Encipher(usn);
				std::cout << hex_enc.Encrypt(usn) << std::endl;
			}
		}
	}

	void Commands::Dec(std::vector<std::string>& parsed_command)
	{
		if (parsed_command.size() != 2)
		{
			std::cout << "Command error..." << std::endl;
			Help();
		}
		else
		{
			parsed_command = StringHelper::SkipFirst(parsed_command);
			auto encrypted_usn = StringHelper::Join(" ", parsed_command);
			encrypted_usn = hex_enc.Decrypt(encrypted_usn);
			std::cout << caesar_enc.Decipher(encrypted_usn) << std::endl;
		}
	}

	void Commands::Help()
	{
		std::cout << "Enc\t-Use: \"enc card_usn\"" << std::endl;
		std::cout << "\t-Encode the usn provided." << std::endl;

		std::cout << "Dec\t-Use: \"dec hex_string\"" << std::endl;
		std::cout << "\t-Get the usn from the hex string provided." << std::endl;

		std::cout << "Clear\t-Clear the console." << std::endl;

		std::cout << "Exit\t-Close the application." << std::endl;

		std::cout << "Help\t-Show help." << std::endl;
	}

	bool Commands::ValidateUsn(std::string const& usn)
	{
		return usn.size() > 2 && usn.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
	}
}

