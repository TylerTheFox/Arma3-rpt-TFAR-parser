/*
	AUTHOR: Brandan Tyler Lasley (TylerTheFox)
	DATE : September 20, 2022
	NAME : parser
*/
#pragma once

#include <string>
#include <unordered_map>

class parser
{
public:
	/*
		Parses an arma 3 rpt file looking for tfar enforcer messages of connected players.
		then it parses those messages to extract both the steam ID and name and added it to
		a multimap.

		No filtering is done and all duplicates will be returned from this function.
	*/
	static std::unordered_multimap<std::string, std::string> parse(const std::string & fname);
};