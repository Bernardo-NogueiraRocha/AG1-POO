#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <unordered_map>
#include "entrevistados.h"
using namespace std;


int main()
{
    vector<string> campos({"sexo", "idade", "escolaridade", "regiao", "tecnologia", "area"});
    Entrevistados entrevistados(campos, "./data/Entrevistados.csv");

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
    entrevistados.query();
    return 0;
}