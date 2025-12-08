#include <cstdio>
#include "historico.hpp"
#include "paciente.hpp"

/*
construtor do paciente
*/

paciente::paciente(string str, int pri){
    nome = str;
    id = 0;
    hist = historico();
    priority = pri;
}


/*
destrutor do paciente (morte por doença não tratada)
*/

paciente::~paciente(){
    // not much to delete here
    id = 0;
    nome = {};
}