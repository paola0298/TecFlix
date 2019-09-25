#include "ReadCSV.hpp"

CSVReader::CSVReader(std::string filename, std::string delm) : 
fileName(filename), delimeter(delm) {}
    
/*
* Parses through csv file line by line and returns the data
* in vector of strings.
*/
std::vector<std::string> CSVReader::getData(int start, int end, bool allData) { 
    std::ifstream file(fileName);
    std::vector<std::string> dataList;
    std::string line = "";
    int count = 0;

    if (!allData) {
        // Iterate through each line and split the content using delimeter
        while (getline(file, line)) {
            if (count>= start && count <= end) {
                dataList.push_back(line);
            }
            if (count == end) 
                break;
            count++;
        }
    } else {
        // Iterate through each line and split the content using delimeter
        while (getline(file, line)) {
            dataList.push_back(line);
        }
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

    // cout << "Entering loop...\n";
    // cout <<dataList.size()<<"\n";

    for(std::string line : dataList){
        // cout << "Loop \n";

        // std::cout<<data << ",";
        std::stringstream ss(line);

        if (c==lineNumber){
            while (getline(ss, word, ',')) { 
                // add all the column data 
                // of a row to a vector 
                row.push_back(word); 
                // cout << "Word: " << word << "\n";
            }
            // cout << "Color: " << row[0] << " \n"; 
            // cout << "Director name: " << row[1] << "\n"; 
            // cout << "Num critic of reviews: " << row[2] << "\n"; 
            // cout << "Duration: " << row[3] << "\n"; 
            // cout << "Director facebook likes: " << row[4] << "\n"; 
            // cout << "Actor 3 facebook likes: " << row[5] << "\n"; 
            // cout << "Actor 2 name: " << row[6] << " \n"; 
            // cout << "Actor 1 facebook likes: " << row[7] << "\n"; 
            // cout << "Gross: " << row[8] << "\n"; 
            // cout << "Genres: " << row[9] << "\n"; 
            // cout << "Actor 1 name: " << row[10] << "\n"; 
            // cout << "Movie tittle: " << row[11] << "\n"; 
            // cout << "Num voted users: " << row[12] << "\n"; 
            // cout << "Cast total facebook likes: " << row[13] << "\n"; 
            // cout << "Actor 3 name: " << row[14] << "\n"; 
            // cout << "Facenumber in poster: " << row[15] << "\n"; 
            // cout << "Plot keywords: " << row[16] << "\n"; 
            // cout << "Movie imdb link: " << row[17] << "\n"; 
            // cout << "Num user for reviews: " << row[18] << "\n"; 
            // cout << "Language: " << row[19] << "\n"; 
            // cout << "Country: " << row[20] << "\n"; 
            // cout << "Content rating: " << row[21] << "\n"; 
            // cout << "Budget: " << row[22] << "\n"; 
            // cout << "Tittle year: " << row[23] << "\n"; 
            // cout << "Actor 2 facebook likes: " << row[24] << "\n"; 
            // cout << "Imdb score: " << row[25] << "\n"; 
            // cout << "Aspect ratio: " << row[26] << "\n"; 
            // cout << "Movie facebook likes: " << row[27] << "\n"; 
        }  
        c++;  
    }
    return row;
}



// int main() {
//     // Creating an object of CSVWriter
//     CSVReader reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv");
//     // Get the data from CSV File
//     std::vector<std::string> dataList = reader.getData(1, 10);
//     reader.getRecord(9, dataList);
//     return 0;
// }