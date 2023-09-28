#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "CSVReader.h"
using namespace std;
int main() {
    CSVReader reader("../../data/Entrevistados.csv");
    auto data = reader.getData();
    int i;
    for (const auto& row : data) {
        i = 0;
        for (const auto& cell : row) {
            i++;
            if(i == 1)
                cout << cell << " ";
        }
       cout << endl;
    }
    return 0;
}
