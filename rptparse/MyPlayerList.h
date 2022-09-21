/*
	AUTHOR: Brandan Tyler Lasley (TylerTheFox)
	DATE : September 20, 2022
	NAME : MyPlayerList
*/
#pragma once
#include <string>
#include <unordered_map>

/*
	The goal of this class is to manage the Player database and ensure
	that duplicates are handled appropriately. 
*/
class MyPlayerList
{
public:
	/*
		Saves MyPlayers to a JSON database on disk
	*/
	void save(const std::string& filepath);
	/*
		Saves MyPlayers to a CSV file on disk to be opened with Excel. 
	*/
	void saveCSV(const std::string& filepath);
	/*
		This loads MyPlayers from a JSON database on disk
	*/
	void load(const std::string& filepath);
	/*
		This merges a multimap into MyPlayers ensuring that there is no
		exact duplicates being added. IE. Steam ID and Name EXACTLY match

		However, allows other duplicates multiple steam IDs with different names
		or duplciate names with different steam IDs
	*/
	void merge(const std::unordered_multimap<std::string, std::string> & myData);
private:
	std::unordered_multimap<std::string, std::string> MyPlayers;
};
