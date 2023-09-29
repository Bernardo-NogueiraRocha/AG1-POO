#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include<unordered_map>
using namespace std;
// Classe que representa um entrevistado.
class Entrevistado
{
    // Mapa para armazenar informações do entrevistado. A chave é o campo e o valor é a informação.
    public:
        unordered_map<string, string> infos;

    public:
        // Construtor padrão.
        Entrevistado() {}

        // Construtor que inicializa o mapa de informações com base em vetores de campos e dados.
        Entrevistado(vector<string> campos, vector<string> dados)
        {
            for (int i = 0; i < dados.size(); i++)
                infos[campos[i]] = dados[i];
        }

        // Destrutor padrão.
        ~Entrevistado() {}

        // Método para obter uma informação com base em um campo específico.
        string getInfoByCampo(string campo)
        {
            if (infos.find(campo) == infos.end())
                return ""; // Retorna uma string vazia se o campo não for encontrado.
            else
                return infos[campo]; // Retorna a informação correspondente ao campo.
        }

        // Método para definir uma informação para um campo específico.
        void setInfoByCampo(string campo, string info)
        {
            if (infos.find(campo) != infos.end())
                infos[campo] = info; // Atualiza a informação se o campo já existir.
        }

        // Método para imprimir todas as informações do entrevistado.
        void print()
        {
            for (auto &i : infos)
                cout << i.first << ": " << i.second << endl;
        }
};
