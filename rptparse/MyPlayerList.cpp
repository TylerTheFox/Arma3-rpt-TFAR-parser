/*
	AUTHOR: Brandan Tyler Lasley (TylerTheFox)
	DATE : September 20, 2022
	NAME : MyPlayerList
*/
#include "MyPlayerList.h"

#include <filesystem>
#include <exception>
#include <iostream>
#include <fstream>

#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/types/unordered_map.hpp"

/*
	Excel has a weird feature where intergers in CSV files are automatically converted
	to scientific notation and truncated. This method tells Excel to treat the integers
	as strings but DOES NOT work with suits such as OpenOffice/LibreOffice
*/
#define EXCEL_FORMAT 0

void MyPlayerList::save(const std::string& filepath)
{
	// Do not call.close manually else Cereal won't
	// proerply close the JSON file and write the ending
	// brackets.

	std::ofstream file(filepath, std::ios::trunc);
	if (file.is_open())
	{
		cereal::JSONOutputArchive archive(file);
		archive(MyPlayers);
	}
	else throw std::runtime_error("Could not save database");
}

void MyPlayerList::saveCSV(const std::string& filepath)
{
	{
		std::ofstream out(filepath, std::ios::trunc);
		if (out.is_open())
		{
			for (auto myMap : MyPlayers)
			{
#if EXCEL_FORMAT 
				out << R"("="")" << myMap.first << R"(""","="")" << myMap.second << R"(""")" << '\n';
#else
				out << myMap.first << ',' << myMap.second << '\n';
#endif
			}
			out.close();
		}
		else throw std::runtime_error("Could not save CSV");
	}
}

void MyPlayerList::load(const std::string& filepath)
{
	if (std::filesystem::exists(filepath))
	{
		std::ifstream file(filepath);
		if (file.is_open())
		{
			cereal::JSONInputArchive archive(file);
			archive(MyPlayers);
		}
		else throw std::runtime_error("Could not load database");
	}
}

void MyPlayerList::merge(const std::unordered_multimap<std::string, std::string> & myData)
{
	std::vector<std::pair<std::string, std::string>> ToBeAdded;

	for (const auto& ToBeMerged : myData)
	{
		// Find all entires within MyPlayers with the same steam ID 
		const auto its = MyPlayers.equal_range(ToBeMerged.first);

		// Check if the result of equal_range returns any entiries
		if (its.first != its.second)
		{
			// equal_range contains at least one entry, let's loop through all of them.

			bool valid = true;

			// Loop through all entiries checking if the username matches the steam ID, 
			// if it does, make valid false as to not add a already existing duplicate.
			for (auto it = its.first; it != its.second; ++it)
			{
				if (it->first == ToBeMerged.first && it->second == ToBeMerged.second)
				{
					valid = false;
					break;
				}
			}

			// There is no duplicate which exists between MyPlayers and ToBeMerged.
			// But we need to check if it already exists within our ToBeAdded vector.
			if (valid)
			{
				bool found = false;
				for (const auto& myVar : ToBeAdded)
				{
					if (!(myVar.first == ToBeMerged.first && myVar.second == ToBeMerged.second))
					{
						found = true;
						break;
					}
				}

				// If the pair does not already exist within the ToBeAdded vector, add it.
				if (!found)
					ToBeAdded.push_back(ToBeMerged);
			}

			// All the entires in the ToBeAdded exist within MyData but do not in MyPlayers
			// This should ensure that only pairs which are NOT EXACTLY unique in both name 
			// and IDget added to MyPlayers
			for (const auto& MyAddedThings : ToBeAdded)
			{
				std::cout << "Found new player: " << MyAddedThings.first << " --- " << MyAddedThings.second << '\n';
				MyPlayers.insert(MyAddedThings);
			}
			ToBeAdded.clear();
		}
		else
		{
			// There was no SteamID within MyPlayers so we should directly add it to MyPlayers.
			std::cout << "Found new player: " << ToBeMerged.first << " --- " << ToBeMerged.second << '\n';
			MyPlayers.insert(ToBeMerged);
		}
	}
}