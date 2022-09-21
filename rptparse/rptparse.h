/*
	AUTHOR: Brandan Tyler Lasley (TylerTheFox)
	DATE : September 20, 2022
	NAME : rptparse
*/
#pragma once
#include <string>

// This will be the name of the json player database
#define myDBfilename "playerDatabase.json"

namespace EXIT_CODES
{
	/// Indicates that the application exited without any errors occurring.
	const int SUCCESS = 0;
	/// Some runtime error 
	const int RUNTIME_ERROR = -1;
}

class rptparse
{
public:
	/*
		Process the commandline arguments
	*/
	rptparse(const int argument_count, const char* argument_list[]);

	/*
		Entry point of the program called from main, returns a status code of success
		or failure
	*/
	int run();
private:
	/*
		Prints the copyright notice at the start of the application
	*/
	void print_copyright();

	std::string myParseFile;
	std::string myOutputFile;
};