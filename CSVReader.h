#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class CSVReader {
private:
    std::vector<std::vector<std::string>> data;

public:
    // Construtor que lê o arquivo CSV
    CSVReader(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        getline(file,line);
        while (getline(file, line)) {
            std::vector<std::string> row;
            std::stringstream ss(line);
            std::string cell;
            while (getline(ss, cell, ';')) { // Usando ';' como delimitador
                row.push_back(cell);
            }
            data.push_back(row);
        }
    }

    // Método para retornar os dados em uma matriz
    std::vector<std::vector<std::string>> getData() const {
        return data;
    }
};
