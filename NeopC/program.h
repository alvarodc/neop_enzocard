#pragma once
#include <string>

namespace neopenzocard {
	class Program
	{
	public:
		Program();
		~Program();
		void Run();
	private:
		bool exit_ = false;
		void ProcessCommand(std::string command);
	};
}


