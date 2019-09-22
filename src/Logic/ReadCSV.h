#ifndef READ_CSV
#define READ_CSV

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <sstream>
using namespace std;

/*
* A class to read data from a csv file.
*/
class CSVReader {
    std::string fileName;
    std::string delimeter;
    public:
        CSVReader(std::string filename, std::string delm = ",");
        // Function to fetch data from a CSV File
        std::vector<std::string> getData(int start, int end);
        std::vector<std::string> getRecord(int lineNumber, std::vector<std::string> dataList);
};

#endif