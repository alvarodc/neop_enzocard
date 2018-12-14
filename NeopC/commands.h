#pragma once
#include <vector>

namespace neopenzocard {
	class Commands
	{
	public:
		void Enc(std::vector<std::string> &parsed_command);
		void Dec(std::vector<std::string> &parsed_command);
		void Help();
	private:
		bool ValidateUsn(std::string const& s);
	};
}

