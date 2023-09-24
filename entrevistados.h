#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

class Entrevistado
{
public:
    string genero;
    string idade;
    string escolaridade;
    string regiao;
    string tecnologia;
    string areaEscolhida;

public:
    Entrevistado(string a, string b, string c, string d, string e, string f);
};

class Entrevistados
{
private:
    vector<Entrevistado> entrevistados;

public:
    Entrevistados(string nome);
    int getSize();
    int totalPorSexo(string a);
    map<string,int>PercentualFaixa();
    map<string,int>PercentualArea();
    int totalPorEscolaridade(string a);
    int total60Smartphones();
    int total15Smartphones();
    map<string,int>AreasPrioritarias();
};
Entrevistado::Entrevistado(string a, string b, string c, string d, string e, string f)
{
    genero = a;
    idade = b;
    escolaridade = c;
    regiao = d;
    tecnologia = e;
    areaEscolhida = f;
}

Entrevistados::Entrevistados(string nome)
{
        ifstream arquivo(nome);
        if (!arquivo.is_open()){
            cerr << "Erro ao abrir o arquivo." << endl;
            return;}
        string linha;
        getline(arquivo, linha);
        while (getline(arquivo, linha))
        {
            stringstream ss(linha);
            string genero, idade, escolaridade, regiao, tecnologia, area;

            getline(ss, genero, ';');
            getline(ss, idade, ';');
            getline(ss, escolaridade, ';');
            getline(ss, regiao, ';');
            getline(ss, tecnologia, ';');
            getline(ss, area);
            Entrevistado entrevistado(genero, idade, escolaridade, regiao, tecnologia, area);
            entrevistados.push_back(entrevistado);
        }
        arquivo.close();
}
int Entrevistados::getSize(){
    return entrevistados.size();
}

int Entrevistados::totalPorSexo(string a){
    int totalSexo = 0;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        if (entrevistado.genero == a)
        {
            totalSexo++;
        }
    }
    return totalSexo;
}

map<string,int> Entrevistados::PercentualFaixa(){
    map<string, int> faixasEtarias;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        string faixa= entrevistado.idade;
        faixasEtarias[faixa]++;
    }
    cout << "3. Percentual de entrevistados por faixa etaria:" << endl;
    for (const auto &par : faixasEtarias)
    {
        double percentual = (static_cast<double>(par.second) / entrevistados.size()) * 100.0;
        cout << "   - " << par.first << ": " << fixed << setprecision(2) << percentual << "%" << endl;
    }
    return faixasEtarias;
}

map<string,int> Entrevistados::PercentualArea(){
    map<string, int> regioes;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        regioes[entrevistado.regiao]++;
    }
    cout << "4. Percentual de entrevistados em cada regiao do municipio:" << endl;
    for (const auto &par : regioes)
    {
        double percentual = (static_cast<double>(par.second) / entrevistados.size()) * 100.0;
        cout << "   - " << par.first << ": " << fixed << setprecision(2) << percentual << "%" << endl;
    }
    return regioes;
}

int Entrevistados::totalPorEscolaridade(string a){
    int totalEnsinoMedioCompleto = 0;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        if (entrevistado.escolaridade == " Ensino médio completo" || entrevistado.escolaridade == " Ensino superior completo")
        {
            totalEnsinoMedioCompleto++;
        }
    }
    return totalEnsinoMedioCompleto;
}

int Entrevistados::total60Smartphones(){
    int acima60ComSmartphone = 0;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        if (entrevistado.idade == " Acima de 60 anos" && entrevistado.tecnologia == " Smartphone")
        {
            acima60ComSmartphone++;
        }
    }
    return acima60ComSmartphone;
}

int Entrevistados::total15Smartphones(){
    int ate15ComSmartphone = 0;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        if (entrevistado.idade == " Até 15 anos" && entrevistado.tecnologia == " Smartphone")
        {
            ate15ComSmartphone++;
        }
    }
    return ate15ComSmartphone;
}

map<string,int> Entrevistados::AreasPrioritarias(){
    map<string, int> areasPrioritarias;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        areasPrioritarias[entrevistado.areaEscolhida]++;
    }
    return areasPrioritarias;
}
