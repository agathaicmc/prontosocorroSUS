#ifndef PACIENTESUS
#define PACIENTESUS
#include <string>
using namespace std;

#include "historico.hpp"

typedef struct paciente{
    string nome;
    int id;
    historico hist;

    // métodos das funções utilitárias

    // construtor
    paciente(string str);

    // destrutor
    ~paciente();

    // jesse delete esse comentário e insira as outras funções que voce achar necessárias
    // sugestões: n sei honestamente


}paciente;

#endif