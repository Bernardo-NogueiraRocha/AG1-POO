#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include "CSVReader.h"
#include "entrevistado.h"
#include <unordered_map>
#include<algorithm>
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
    vector<string> getCampos()
    {
        return campos;
    }

    vector<string> getAllUniqueByCampo(string c)
    {
        vector<string> unique;
        for (auto &e : entrevistados)
        {

            if (find(unique.begin(), unique.end(), e.getInfoByCampo(c)) == unique.end())
                unique.push_back(e.getInfoByCampo(c));
        }
        return unique;
    }

    void query()
    {
        vector<string> mycampos;
        vector<pair<string, vector<string>>> dados;
        vector<string> myopcoes;
        string campo;
        int num;

        while (true)
        {
            system("clear");
            bool flag_ent = false;
            cout << "Buscar por? (-1 para sair):" << endl;

            for (int i = 0; i < this->getCampos().size(); i++)
            {
                if (find(mycampos.begin(), mycampos.end(), this->getCampos()[i]) == mycampos.end())
                {
                    flag_ent = true;
                    cout << i << ") " << this->getCampos()[i] << endl;
                }
            }

            if (!flag_ent)
                break;

            cout << endl;
            cin >> num;

            if (num == -1 || num >= this->getCampos().size())
                break;

            campo = this->getCampos()[num];
            vector<string> opcoes;

            while (true)
            {
                system("clear");
                bool flag = false;
                cout << "Escolha as opções desejadas para " << campo << " (-1 para sair):" << endl;

                for (int i = 0; i < this->getAllUniqueByCampo(campo).size(); i++)
                {
                    if (find(opcoes.begin(), opcoes.end(), this->getAllUniqueByCampo(campo)[i]) == opcoes.end())
                    {
                        cout << i << ") " << this->getAllUniqueByCampo(campo)[i] << endl;
                        flag = true;
                    }
                }

                if (!flag)
                    break;

                cout << endl;

                cout << "Opções selecionadas para " << campo << ":" << endl;
                for (int s = 0; s < opcoes.size(); s++)
                {
                    cout << opcoes[s];
                    if (s != opcoes.size() - 1)
                        cout << ", ";
                }

                cout << endl
                     << endl;
                cin >> num;

                if (num == -1 || num >= this->getAllUniqueByCampo(campo).size())
                    break;

                if (find(opcoes.begin(), opcoes.end(), this->getAllUniqueByCampo(campo)[num]) == opcoes.end())
                    opcoes.push_back(this->getAllUniqueByCampo(campo)[num]);
            }

            if (!opcoes.empty())
            {
                dados.push_back({campo, opcoes});
                mycampos.push_back(campo);
            }

            cout << endl
                 << endl;
            cout << dados.size() << endl;

            system("clear");

            cout << "Dados selecionados:" << endl
                 << endl;

            for (int p = 0; p < dados.size(); p++)
            {
                cout << "\t" << dados[p].first << ": ";
                for (int s = 0; s < dados[p].second.size(); s++)
                {
                    cout << dados[p].second[s];
                    if (s != dados[p].second.size() - 1)
                        cout << " ou ";
                }

                if (p != dados.size() - 1)
                    cout << endl
                         << "\tE\n";
            }

            cout << endl
                 << endl;
            cout << "Deseja adicionar mais um campo? (s/n)" << endl;
            char c;
            cin >> c;

            if (c == 'n')
                break;
        }

        cout << "Número de entrevistados que correspondem à pesquisa: " << this->getStatistic(dados) << endl;
    }
    // Destrutor padrão.
    ~Entrevistados() {}
};
