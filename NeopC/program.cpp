#include "program.h"
#include <iostream>
#include <algorithm>
#include "stringhelper.h"
#include "commands.h"

namespace neopenzocard {

	Program::Program()
	{
		exit_ = false;
	}

	Program::~Program()
	{
	}
	
	void Program::Run()
	{
		do {
			std::cout << "command > ";
			std::string console_input;
			std::getline(std::cin, console_input);
			ProcessCommand(console_input);
		} while (exit_ == false);
	}

	void Program::ProcessCommand(std::string console_input)
	{
		Commands commands;
		auto parsed_command = StringHelper::Split(console_input, ' ');
		auto command = parsed_command[0];
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);

		if (command == "enc")
		{
			commands.Enc(parsed_command);
		}
		else if (command == "dec")
		{
			commands.Dec(parsed_command);
		}
		else if (command == "help")
		{
			commands.Help();
		}
		else if (command == "clear")
		{
			system("CLS");
		}
		else if (command == "exit")
		{
			exit_ = true;
		}
		else
		{
			std::cout << "Enter 'help' to get the commands options." << std::endl;
		}
	}
}