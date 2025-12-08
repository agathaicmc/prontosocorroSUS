#ifndef PACIENTESUS
#define PACIENTESUS
#include <string>
using namespace std;

#include "historico.hpp"

typedef struct paciente{
    string nome;
    int id;
    historico hist;
    int priority;

    // construtor
    paciente(string str, int pri);

    // destrutor
    ~paciente();

}paciente;

#endif