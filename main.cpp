#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include "entrevistados.h"
using namespace std;


int main()
{
    Entrevistados entrevistados("../data/Entrevistados.csv");
    // Função 1: Total de entrevistados
    int totalEntrevistados = entrevistados.getSize();
    cout << "1. Total de entrevistados: " << totalEntrevistados << endl;

    // Função 2: Número de entrevistados do sexo feminino
    int totalFeminino = entrevistados.totalPorSexo("f");
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
    int totalEnsinoMedioCompleto = entrevistados.totalPorEscolaridade(" Ensino superior completo");
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