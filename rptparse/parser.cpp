/*
	AUTHOR: Brandan Tyler Lasley (TylerTheFox)
	DATE : September 20, 2022
	NAME : parser
*/
#include "parser.h"

#include <fstream>
#include <sstream>

std::unordered_multimap<std::string, std::string> parser::parse(const std::string & fname)
{
	std::unordered_multimap<std::string, std::string> myPlayers;
	std::string myLine;
	std::ifstream myRptFile(fname);

	if (myRptFile.is_open())
	{
		// Loop through every line in the file
		while (std::getline(myRptFile, myLine))
		{
			// Check if the line contains the words player connected, if not, continue looping.
			if (myLine.find("Info: Player connected") != std::string::npos)
			{
				// This is a lazy way to trim the string, we know the steam ID occurs after
				// the 4th colon.
				int myColonCount = 0;
				std::string deeperLine;
				for (auto chr : myLine)
				{
					if (myColonCount != 4)
					{
						if (chr == ':')
						{
							myColonCount++;
						}
					}
					else
					{
						deeperLine += chr;
					}
				}

				std::stringstream MyDeeperBuffer(deeperLine);
				std::string MyName;
				std::string myID;
				std::vector<std::string> myParams;

				// Split the string by commas and store the result in myParams
				while (MyDeeperBuffer.good())
				{
					std::string my3rdDeepestLine;
					std::getline(MyDeeperBuffer, my3rdDeepestLine, ',');

					if (my3rdDeepestLine.find(R"("")") != std::string::npos)
					{
						myParams.push_back(my3rdDeepestLine);
					}
				}

				// Now we should have all of the paramters stored in the vector starting
				// and ending with double quotes.

				// We know the steam ID occurs at index 0 of this vector and the name
				// occurs at index 1
				myID = myParams[0];
				MyName = myParams[1];

				// Erase the double quotes at the start and end of both myID and myName
				MyName.erase(0, 2);
				MyName.erase(MyName.size() - 2);

				myID.erase(0, 2);
				myID.erase(myID.size() - 2);

				// Insert the name and ID into the multimap, this allows *ALL* duplicates!
				myPlayers.insert({ myID, MyName });
			}
		}
	}
	return myPlayers;
}
