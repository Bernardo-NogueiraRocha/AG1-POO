// Inclui o arquivo de cabeçalho da classe CSVHandler.
#include "CSVhandler.h"
using namespace std;

// Implementação do construtor da classe CSVHandler.
CSVHandler::CSVHandler(const string& path) : filePath(path) {}

// Implementação do método writeData.
bool CSVHandler::writeData(const vector<vector<string>>& data) {
    // Abre o arquivo para escrita.
    ofstream file(filePath);
    // Verifica se o arquivo foi aberto com sucesso.
    if (!file.is_open()) {
        return false;
    }

    // Itera sobre cada linha de dados.
    for (const auto& row : data) {
        // Itera sobre cada coluna da linha.
        for (size_t i = 0; i < row.size(); ++i) {
            // Escreve o valor da coluna no arquivo.
            file << row[i];
            // Se não for a última coluna, adiciona uma vírgula.
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        // Adiciona uma nova linha após escrever todos os valores da linha.
        file << "\n";
    }

    // Fecha o arquivo.
    file.close();
    return true;
}

// Implementação do método readData.
vector<vector<string>> CSVHandler::readData() {
    // Vetor para armazenar os dados lidos.
    vector<vector<string>> data;
    // Abre o arquivo para leitura.
    ifstream file(filePath);
    // Verifica se o arquivo foi aberto com sucesso.
    if (!file.is_open()) {
        return data;
    }

    string line;
    // Lê o arquivo linha por linha.
    while (getline(file, line)) {
        vector<string> row;
        size_t pos = 0;
        // Divide a linha em valores separados por vírgulas.
        while ((pos = line.find(",")) != string::npos) {
            row.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        // Adiciona o último valor (após a última vírgula) à linha.
        row.push_back(line);
        // Adiciona a linha lida ao vetor de dados.
        data.push_back(row);
    }

    // Fecha o arquivo.
    file.close();
    return data;
}
