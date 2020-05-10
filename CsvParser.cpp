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
	std::vector<bool> columns;
	std::map<int, std::vector<double>> columnData;
	std::ifstream myfile(aCsvFilePath);
	std::string                headerText;
	std::getline(myfile, headerText);
	std::stringstream          lineStream(headerText);
	std::string headerCell;
	while (std::getline(lineStream, headerCell, ','))
	{
		bool found = aHeaderKeys.find(headerCell) != aHeaderKeys.cend();
		if (found)
		{ // map column index to key for later
			aHeaderKeyIndexes[headerCell] = columns.size();
		}
		columns.push_back(found);
	}

	int index = 0;
	std::string rowText;
	while (std::getline(myfile, rowText))
	{
		index++;
		char* curIdxPtr = &rowText.front();
		for (int i = 0; i < columns.size(); ++i)
		{
			if (columns[i])
			{
				double value = strtod(curIdxPtr, &curIdxPtr);
				//std::cout << "value:" << value << std::endl;
				columnData[i].push_back(value);
			} 
			else {
				curIdxPtr = strchr(curIdxPtr, ',');
				//std::cout << "skippng: " << i << std::endl;
			}
			curIdxPtr++;
		}
	}

	for (auto headerKey : aHeaderKeys)
	{
		auto idx = aHeaderKeyIndexes[headerKey];
		output[headerKey] = std::move(columnData[idx]);
	}
	return std::move(output);
}
