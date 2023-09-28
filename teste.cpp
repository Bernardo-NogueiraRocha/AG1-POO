#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <unordered_map>
#include "CSVReader.h"
using namespace std;
#define CAMPOS 6
class Entrevistado
{
public:
    unordered_map<string, string> infos;

public:
    Entrevistado() {}
    Entrevistado(vector<string> campos, vector<string> dados)
    {
        for (int i = 0; i < dados.size(); i++)
            infos[campos[i]] = dados[i];
    }
    ~Entrevistado() {}
    string getInfoByCampo(string campo)
    {
        if (infos.find(campo) == infos.end())
            return "";
        else
            return infos[campo];
    }
    void setInfoByCampo(string campo, string info)
    {
        if (infos.find(campo) != infos.end())
            infos[campo] = info;
    }

    void print()
    {
        for (auto &i : infos)
            cout << i.first << ": " << i.second << endl;
    }
};

class Entrevistados
{
private:
    vector<string> campos;
    vector<Entrevistado> entrevistados;

public:
    Entrevistados(vector<string> c, string nome)
    {
        campos = c;
        CSVReader reader("Entrevistados.csv");
        auto data = reader.getData();
        for (const auto &s : data)
        {
            vector<string> dados;
            for (int i = 0; i < CAMPOS; i++)
                dados.push_back(s[i]);
            entrevistados.push_back(Entrevistado(c, dados));
        }
    }
    Entrevistado getEntrevistado(int i)
    {
        if (i < entrevistados.size())
            return entrevistados[i];
        else
            return Entrevistado();
    }

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
                opcoes = dados[i].second; // valores aceitaveis passados

                bool flag = false;
                for (const auto &opt : opcoes)
                {
                    if (e.getInfoByCampo(campo).find(opt) != string::npos) // campo é uma dos valores aceitaveis
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
    int getSize()
    {
        return entrevistados.size();
    }

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

    ~Entrevistados() {}
};

int main()
{
    vector<string> campos({"sexo", "idade", "escolaridade", "regiao", "tecnologia", "area"});
    Entrevistados entrevistados(campos, "Entrevistados.csv");

    cout << "Número de Entrevistados: " << entrevistados.getSize() << endl;
    cout << "Número de Entrevistados do sexo masculino: " << entrevistados.getStatistic({{"sexo", {"m"}}}) << endl;
    cout << "Número de Entrevistados do sexo feminino: " << entrevistados.getStatistic({{"sexo", {"f"}}}) << endl;
    cout << "Número de Entrevistados de outro sexo: " << entrevistados.getStatistic({{"sexo", {"o"}}}) << endl;
    cout << "Percentual com idade igual ou superior a 30: " << (float)entrevistados.getStatistic({{"idade", {"De 30 a 59 anos", "Acima de 60 anos"}}}) / entrevistados.getSize() << endl;
    cout << "Percentual de residentes na região Extremo Oeste: " << (float)entrevistados.getStatistic({{"regiao", {"Região Extremo Oeste"}}}) / entrevistados.getSize() << endl;
    cout << "Número de entrevistados com ensiono superior completo: " << entrevistados.getStatistic({{"escolaridade", {"Ensino superior completo"}}}) << endl;
    cout << "Número de entrevistados acima de 29 anos que utilizam Notebook ou Netbook: " << entrevistados.getStatistic({{"idade", {"De 30 a 59 anos", "Acima de 60 anos"}}, {"tecnologia", {"Notebook ou Netbook"}}}) << endl;
    cout << "Tecnologia mais utilizada pelos entrevistados: " << entrevistados.getMaxByCampo("tecnologia") << endl;
    cout << "Percentual feminino: " << (float)entrevistados.getStatistic({{"sexo", {"f"}}}) / entrevistados.getSize() << endl;
    cout << "Numero de entrevistados que consideram educação a area prioritária: " << entrevistados.getStatistic({{"area", {"Educação"}}}) << endl;

    return 0;
}