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
