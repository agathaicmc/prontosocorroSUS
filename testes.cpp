#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
#include "historico.hpp"
#include "paciente.hpp"
#include "fila.hpp"
#include "lista.hpp"

int main(void){
    
    fila q;
    string nome;
    getline(cin, nome);

    paciente p(nome);
    p.id = 1;

    getline(cin, nome);
    paciente p2(nome);
    p2.id = 2;
    
    getline(cin, nome);
    paciente p3(nome);
    p3.id = 3;

    getline(cin, nome);
    paciente p4(nome);
    p4.id = 4;

    q.inserir(&p);
    q.inserir(&p2);
    q.inserir(&p3);
    q.inserir(&p4);

    q.consultar();

    paciente *temp = q.buscar(3);
    string procedimento;
    getline(cin, procedimento);

    temp->hist.inserir(procedimento);
    
    
    p3.hist.consultar();
    
    getline(cin, procedimento);
    p3.hist.inserir(procedimento);
    temp->hist.consultar();

    p3.hist.retirar();

    p3.hist.consultar();

    return(0);
}