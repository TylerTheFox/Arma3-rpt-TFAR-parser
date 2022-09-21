/*
	AUTHOR: Brandan Tyler Lasley (TylerTheFox)
	DATE : September 20, 2022
	NAME : rptparse
*/
#include "rptparse.h"
#include "MyPlayerList.h"
#include "parser.h"

#include <unordered_map>
#include <exception>
#include <iostream>
#include <string>

void rptparse::print_copyright()
{
	std::cout << "Copyright Brandan Tyler Lasley 2022 (TylerTheFox)" << '\n'
		<< "Build date: " << __DATE__ << " -- " << __TIME__ << "\n\n";
}

rptparse::rptparse(unsigned int argument_count, const char * argument_list[])
{
	const unsigned int EXPECTED_ARGUMENT_COUNT = 3;

	// Indexes of the rpt and output within the argument list
	const unsigned int INPUT_RPT_FILENAME = 1;
	const unsigned int OUTPUT_CSV_FILENAME = 2;

	if (EXPECTED_ARGUMENT_COUNT != argument_count)
	{
		print_copyright();
		throw std::runtime_error("Invalid arguments received.  Expected arguments:\nrptparse.exe <input-rpt> <output-csv>");
	}

	myParseFile = argument_list[INPUT_RPT_FILENAME];
	myOutputFile = argument_list[OUTPUT_CSV_FILENAME];
}

int rptparse::run()
{
	print_copyright();

	MyPlayerList Players;
	Players.load(myDBfilename);
	Players.merge(parser::parse(myParseFile));
	Players.save(myDBfilename);
	Players.saveCSV(myOutputFile);

	std::cout << "Success!\n";

	return EXIT_CODES::SUCCESS;
}

int main(const int argument_count, const char* argument_list[])
{
	try {
		rptparse program(argument_count, argument_list);
		return program.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what();
		return EXIT_CODES::RUNTIME_ERROR;
	}
}