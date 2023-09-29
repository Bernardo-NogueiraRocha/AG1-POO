#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include "CSVReader.h"
#include "entrevistado.h"
#include<unordered_map>
using namespace std;
#define CAMPOS 6

// Classe que representa uma coleção de entrevistados.
class Entrevistados
{
private:
    // Vetor de campos que representam as informações dos entrevistados.
    vector<string> campos;
    // Vetor de objetos da classe Entrevistado.
    vector<Entrevistado> entrevistados;

public:
    // Construtor que inicializa a lista de campos e lê os dados dos entrevistados de um arquivo CSV.
    Entrevistados(vector<string> c, string nome)
    {
        campos = c;
        // Lê o arquivo CSV "Entrevistados.csv".
        CSVReader reader(nome);
        auto data = reader.getData();
        // Itera sobre os dados lidos e cria objetos da classe Entrevistado.
        for (const auto &s : data)
        {
            vector<string> dados;
            for (int i = 0; i < CAMPOS; i++)
                dados.push_back(s[i]);
            entrevistados.push_back(Entrevistado(c, dados));
        }
    }

    // Retorna um entrevistado com base em um índice.
    Entrevistado getEntrevistado(int i)
    {
        if (i < entrevistados.size())
            return entrevistados[i];
        else
            return Entrevistado(); // Retorna um entrevistado vazio se o índice for inválido.
    }

    // Retorna a contagem de entrevistados que atendem a certos critérios.
    int getStatistic(vector<pair<string, vector<string>>> dados)
    {
        int count = 0;
        int mycount = 0;

        string campo;
        vector<string> opcoes;

        for (auto &e : entrevistados)
        {
            mycount = 0;
            for (int i = 0; i < dados.size(); i++)
            {
                campo = dados[i].first;   // campo atual
                opcoes = dados[i].second; // valores aceitáveis passados

                bool flag = false;
                for (const auto &opt : opcoes)
                {
                    if (e.getInfoByCampo(campo).find(opt) != string::npos) // campo é um dos valores aceitáveis
                        flag = true;
                }
                if (flag)
                    mycount++;
            }
            if (mycount == dados.size())
                count++;
        }

        return count;
    }

    // Retorna o tamanho do vetor de entrevistados.
    int getSize()
    {
        return entrevistados.size();
    }

    // Conta quantos entrevistados têm uma determinada informação em um campo específico.
    int countByCampo(string campo, string d)
    {
        int count = 0;
        for (auto &e : entrevistados)
        {
            if (e.getInfoByCampo(campo).find(d) != string::npos)
                count++;
        }
        return count;
    }

    // Retorna o valor mais frequente de um campo específico entre os entrevistados.
    string getMaxByCampo(string campo)
    {
        unordered_map<string, int> count;
        for (auto &e : entrevistados)
        {
            count[e.getInfoByCampo(campo)]++;
        }
        int max = 0;
        string maxStr = "";
        for (auto &c : count)
        {
            if (c.second > max)
            {
                max = c.second;
                maxStr = c.first;
            }
        }
        return maxStr;
    }

    // Destrutor padrão.
    ~Entrevistados() {}
};
