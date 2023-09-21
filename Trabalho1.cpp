#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// Definição da classe Entrevistado
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
    Entrevistado() {}
    Entrevistado(string a, string b, string c, string d, string e, string f)
    {
        genero = a;
        idade = b;
        escolaridade = c;
        regiao = d;
        tecnologia = e;
        areaEscolhida = f;
    }
    ~Entrevistado() {}
};

class Entrevistados
{
private:
    vector<Entrevistado> entrevistados;

public:
    Entrevistados(string nome)
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
    int getSize();
    int totalFeminino();
    map<string,int>PercentualFaixa();
    map<string,int>PercentualArea();
    int totalEnsinoMedio();
    int total60Smartphones();
    int total15Smartphones();
    map<string,int>AreasPrioritarias();
};

int Entrevistados::getSize(){
    return entrevistados.size();
}

int Entrevistados::totalFeminino(){
    int totalFeminino = 0;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        if (entrevistado.genero == "f")
        {
            totalFeminino++;
        }
    }
    return totalFeminino;
}

map<string,int> Entrevistados::PercentualFaixa(){
    map<string, int> faixasEtarias;
    for (const Entrevistado &entrevistado : entrevistados)
    {
        string faixa;
        if (entrevistado.idade == " Até 15 anos")
        {
            faixa = "Até 15 anos";
        }
        else if (entrevistado.idade == " De 16 a 29 anos")
        {
            faixa = "16-29 anos";
        }
        else if (entrevistado.idade == " De 30 a 59 anos")
        {
            faixa = "30-59 anos";
        }
        else
        {
            faixa = "Acima de 60 anos";
        }
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

int Entrevistados::totalEnsinoMedio(){
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

int main()
{
    Entrevistados entrevistados("Entrevistados.csv");
    // Função 1: Total de entrevistados
    int totalEntrevistados = entrevistados.getSize();
    cout << "1. Total de entrevistados: " << totalEntrevistados << endl;

    // Função 2: Número de entrevistados do sexo feminino
    int totalFeminino = entrevistados.totalFeminino();
    cout << "2. Numero de entrevistados do sexo feminino: " << totalFeminino << endl;

    // Função 3: Percentual de entrevistados por faixa etária
    map<string, int> faixasEtarias= entrevistados.PercentualFaixa();
    // cout << "3. Percentual de entrevistados por faixa etaria:" << endl;
    // for (const auto &par : faixasEtarias)
    // {
    //     double percentual = (static_cast<double>(par.second) / totalEntrevistados) * 100.0;
    //     cout << "   - " << par.first << ": " << fixed << setprecision(2) << percentual << "%" << endl;
    // }

    // Função 4: Percentual de entrevistados em cada região do município
    //cout << "4. Percentual de entrevistados em cada regiao do municipio:" << endl;
    map<string, int> regioes=entrevistados.PercentualArea();
    // for (const auto &par : regioes)
    // {
    //     double percentual = (static_cast<double>(par.second) / totalEntrevistados) * 100.0;
    //     cout << "   - " << par.first << ": " << fixed << setprecision(2) << percentual << "%" << endl;
    // }

    // Função 5: Número de entrevistados com pelo menos o ensino médio completo
    int totalEnsinoMedioCompleto = entrevistados.totalEnsinoMedio();
    cout << "5. Numero de entrevistados com pelo menos o ensino medio completo: " << totalEnsinoMedioCompleto << endl;

    // Função 6: Número de entrevistados com idade acima de 60 anos que utilizam smartphone
    int acima60ComSmartphone = entrevistados.total60Smartphones();
    cout << "6. Numero de entrevistados com idade acima de 60 anos que utilizam smartphone: " << acima60ComSmartphone << endl;

    // Função 7: Número de entrevistados com idade até 15 anos que utilizam smartphone
    int ate15ComSmartphone = entrevistados.total15Smartphones();
    cout << "7. Numero de entrevistados com idade ate 15 anos que utilizam smartphone: " << ate15ComSmartphone << endl;

    // Função 8: Área prioritária dos entrevistados
    map<string, int> areasPrioritarias=entrevistados.AreasPrioritarias();
    cout << "8. Area prioritaria dos entrevistados:" << endl;
    for (const auto &par : areasPrioritarias)
    {
        cout << "   - " << par.first << ": " << par.second << " entrevistados" << endl;
    }

    return 0;
}