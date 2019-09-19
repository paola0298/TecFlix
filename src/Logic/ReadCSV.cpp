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
        CSVReader(std::string filename, std::string delm = ",") : fileName(filename), delimeter(delm)
        { }
        // Function to fetch data from a CSV File
        std::vector<std::string> getData(int start, int end);
        std::vector<std::string> getRecord(int lineNumber, std::vector<std::string> dataList);
};
/*
* Parses through csv file line by line and returns the data
* in vector of strings.
*/
std::vector<std::string> CSVReader::getData(int start, int end) { 
    std::ifstream file(fileName);
    std::vector<std::string> dataList;
    std::string line = "";
    int count = 0;
    // Iterate through each line and split the content using delimeter
    while (getline(file, line)) {
        // std::vector<std::string> vec;
        // boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
        if (count>= start && count <= end) 
            dataList.push_back(line);

        if (count == end) 
            break;
        count++;
    }
    // Close the File
    file.close();
    return dataList;
}

/*
*Parses the vector of strings and return a vector of strings with the data
*of an specific record record
*/
std::vector<std::string> CSVReader::getRecord(int lineNumber, std::vector<std::string> dataList) {
    vector<string> row; 
    string word;
    int c = 0;

    cout << "Entering loop...\n";
    cout <<dataList.size()<<"\n";

    for(std::string line : dataList){

        // std::cout<<data << ",";
        std::stringstream ss(line);
        cout <<c<<"\n";

        if (c==lineNumber){
            while (getline(ss, word, ',')) { 
                // add all the column data 
                // of a row to a vector 
                row.push_back(word); 
                // cout << "Word: " << word << "\n";
            }
            cout << "Color: " << row[0] << " \n"; 
            cout << "Director name: " << row[1] << "\n"; 
            cout << "Num critic of reviews: " << row[2] << "\n"; 
            cout << "Duration: " << row[3] << "\n"; 
            cout << "Director facebook likes: " << row[4] << "\n"; 
            cout << "Actor 3 facebook likes: " << row[5] << "\n"; 
            cout << "Actor 2 name: " << row[6] << " \n"; 
            cout << "Actor 1 facebook likes: " << row[7] << "\n"; 
            cout << "Gross: " << row[8] << "\n"; 
            cout << "Genres: " << row[9] << "\n"; 
            cout << "Actor 1 name: " << row[10] << "\n"; 
            cout << "Movie tittle: " << row[11] << "\n"; 
            cout << "Num voted users: " << row[12] << "\n"; 
            cout << "Cast total facebook likes: " << row[13] << "\n"; 
            cout << "Actor 3 name: " << row[14] << "\n"; 
            cout << "Facenumber in poster: " << row[15] << "\n"; 
            cout << "Plot keywords: " << row[16] << "\n"; 
            cout << "Movie imdb link: " << row[17] << "\n"; 
            cout << "Num user for reviews: " << row[18] << "\n"; 
            cout << "Language: " << row[19] << "\n"; 
            cout << "Country: " << row[20] << "\n"; 
            cout << "Content rating: " << row[21] << "\n"; 
            cout << "Budget: " << row[22] << "\n"; 
            cout << "Tittle year: " << row[23] << "\n"; 
            cout << "Actor 2 facebook likes: " << row[24] << "\n"; 
            cout << "Imdb score: " << row[25] << "\n"; 
            cout << "Aspect ratio: " << row[26] << "\n"; 
            cout << "Movie facebook likes: " << row[27] << "\n"; 
        }  
        c++;  
    }
    return row;
}



int main() {
    // Creating an object of CSVWriter
    CSVReader reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv");
    // Get the data from CSV File
    std::vector<std::string> dataList = reader.getData(1, 10);

    reader.getRecord(9, dataList);

    // Print the content of row by row on screen
    // std::cout << dataList.data()<< "\n";
    // vector<string> row; 
    // string word;
    // int c = 0;

    // cout <<c<<"\n";


    // for(std::string line : dataList){

    //         // std::cout<<data << ",";
    //         std::stringstream ss(line);
    //         // cout <<c<<"\n";

    //         if (c==5000){


    //             while (getline(ss, word, ',')) { 
    
    //                 // add all the column data 
    //                 // of a row to a vector 
    //                 row.push_back(word); 
    //                 // cout << "Word: " << word << "\n";
    //             }

    //             cout << "Color: " << row[0] << " \n"; 
    //             cout << "Director name: " << row[1] << "\n"; 
    //             cout << "Num critic of reviews: " << row[2] << "\n"; 
    //             cout << "Duration: " << row[3] << "\n"; 
    //             cout << "Director facebook likes: " << row[4] << "\n"; 
    //             cout << "Actor 3 facebook likes: " << row[5] << "\n"; 
    //             cout << "Actor 2 name: " << row[6] << " \n"; 
    //             cout << "Actor 1 facebook likes: " << row[7] << "\n"; 
    //             cout << "Gross: " << row[8] << "\n"; 
    //             cout << "Genres: " << row[9] << "\n"; 
    //             cout << "Actor 1 name: " << row[10] << "\n"; 
    //             cout << "Movie tittle: " << row[11] << "\n"; 
    //             cout << "Num voted users: " << row[12] << "\n"; 
    //             cout << "Cast total facebook likes: " << row[13] << "\n"; 
    //             cout << "Actor 3 name: " << row[14] << "\n"; 
    //             cout << "Facenumber in poster: " << row[15] << "\n"; 
    //             cout << "Plot keywords: " << row[16] << "\n"; 
    //             cout << "Movie imdb link: " << row[17] << "\n"; 
    //             cout << "Num user for reviews: " << row[18] << "\n"; 
    //             cout << "Language: " << row[19] << "\n"; 
    //             cout << "Country: " << row[20] << "\n"; 
    //             cout << "Content rating: " << row[21] << "\n"; 
    //             cout << "Budget: " << row[22] << "\n"; 
    //             cout << "Tittle year: " << row[23] << "\n"; 
    //             cout << "Actor 2 facebook likes: " << row[24] << "\n"; 
    //             cout << "Imdb score: " << row[25] << "\n"; 
    //             cout << "Aspect ratio: " << row[26] << "\n"; 
    //             cout << "Movie facebook likes: " << row[27] << "\n"; 
    //         }  
    //         c++;  
        
    // }
    return 0;
}