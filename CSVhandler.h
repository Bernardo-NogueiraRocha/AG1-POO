// Instrução para garantir que o arquivo de cabeçalho seja incluído apenas uma vez.
#pragma once

// Inclui as bibliotecas necessárias.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
// Declaração da classe CSVHandler.
class CSVHandler {
private:
    // Atributo privado para armazenar o caminho do arquivo CSV.
    string filePath;

public:
    // Construtor que aceita o caminho do arquivo CSV como argumento.
    CSVHandler(const string& path);

    // Método para escrever dados em um arquivo CSV.
    // Retorna 'true' se a escrita for bem-sucedida, 'false' caso contrário.
    bool writeData(const vector<vector<string>>& data);

    // Método para ler dados de um arquivo CSV.
    // Retorna os dados como um vetor bidimensional de strings.
    vector<vector<string>> readData();
};
