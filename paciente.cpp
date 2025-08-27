#include <cstdio>
#include "historico.hpp"
#include "paciente.hpp"

/*
construtor do paciente
*/

paciente::paciente(string str){
    nome = str;
    // id = (?)
    hist = historico();
}


/*
destrutor do paciente (morte por doença não tratada)
*/

paciente::~paciente(){
    // deletando historico, setando id pra 0 e o nome pra string vazia
    delete hist;
    id = 0;
    nome = {};
}

// espaço pras outras funções