#ifndef PACIENTESUS
#define PACIENTESUS
#include <string>
using namespace std;

#include "historico.hpp"

typedef struct paciente{
    string nome;
    int id;
    historico hist;

    // construtor
    paciente(string str);

    // destrutor
    ~paciente();

}paciente;

#endif