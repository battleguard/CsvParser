#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <chrono> 
#include "CsvParser.hpp"


using namespace std::chrono;



std::vector<std::vector<std::string>> GetCsvData(std::istream& str)
{
    std::vector<std::vector<std::string>> output;
    std::string                line;
    while (std::getline(str, line))
    {
        std::vector<std::string>   result;
        std::stringstream          lineStream(line);
        std::string                cell;

        while (std::getline(lineStream, cell, ','))
        {
            result.push_back(cell);
        }
        output.push_back(result);
    }
    return output;
}

// http://www.cplusplus.com/reference/istream/istream/read/

// original: 24263
// raw char bob 4218
// removed maps 3170
int main()
{
    auto start = high_resolution_clock::now();
    
    //std::ifstream myfile("input.csv");
    auto columns = CsvParser::GetColumns("input-large.csv", { "x", "z" });

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "Ellpased Ms:" << duration.count() << std::endl;

    std::cout << columns.size() << std::endl;
    std::cout << "x:" << columns["x"].size() << std::endl; // 2,080,005
    std::cout << "y:" << columns["y"].size() << std::endl;
    std::cout << "z:" << columns["z"].size() << std::endl;

}