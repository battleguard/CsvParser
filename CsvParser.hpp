#pragma once

#include <set>
#include <string>
#include <vector>
#include <map>

//! @note this is a very specialized CSV Parser for reading in a csv file that has a column header at the top
//! we only care about a certain small amount of columns and want do not need to read all the columns
//! the data is expected to also be doubles after the initial column headers
class CsvParser
{
public:
	//! Constructor
	//! @param aCsvFilePath the path to the csv file to load and parse
	//! @param aHeaderKeys the header column keys that you want to read. 
	static std::map<std::string, std::vector<double>> GetColumns(const std::string aCsvFilePath, const std::set<std::string>& aHeaderKeys);
};