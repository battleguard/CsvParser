#include "CsvParser.hpp"
#include <fstream>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


std::map<std::string, std::vector<double>> CsvParser::GetColumns(
	const std::string aCsvFilePath, 
	const std::set<std::string>& aHeaderKeys)
{
	std::map<std::string, std::vector<double>> output;
	std::map<std::string,int> aHeaderKeyIndexes;
	bool columns[10];
	std::vector<double> columnData[10];
	std::ifstream myfile(aCsvFilePath, std::ifstream::binary);
	std::string                headerText;
	std::getline(myfile, headerText, '\r');
	std::stringstream          lineStream(headerText);
	std::string headerCell;
	int columnCount = 0;
	while (std::getline(lineStream, headerCell, ','))
	{
		bool found = aHeaderKeys.find(headerCell) != aHeaderKeys.cend();
		if (found)
		{ // map column index to key for later
			aHeaderKeyIndexes[headerCell] = columnCount;
		}
		columns[columnCount] = found;
		columnCount++;
	}

	// adding 1 to skip teh '\n'
	int endOfHeader = 1 + myfile.tellg();
	myfile.seekg(0, myfile.end);
	int length = static_cast<int>(myfile.tellg()) - endOfHeader;
	myfile.seekg(endOfHeader);
	char* buffer = new char[length];
	myfile.read(buffer, length);

	const char* endPtr = buffer + length;

	// increment over newlines \r\n so just 1 since we already always increment 1 for the ,
	for (char* curPtr = buffer; curPtr < buffer + length; curPtr++) 
	{
		for (int i = 0; i < columnCount; ++i)
		{
			if (columns[i])
			{
				double value = strtod(curPtr, &curPtr);
				//std::cout << "value:" << value << std::endl;
				columnData[i].push_back(value);
			}
			else {
				curPtr = strchr(curPtr, ',');
				//std::cout << "skippng: " << i << std::endl;
			}
			curPtr++;
		}
	}

	for (auto headerKey : aHeaderKeys)
	{
		auto idx = aHeaderKeyIndexes[headerKey];
		output[headerKey] = std::move(columnData[idx]);
	}
	delete []buffer;
	return std::move(output);
}
