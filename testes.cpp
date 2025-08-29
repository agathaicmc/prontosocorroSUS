#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
#include "historico.hpp"
#include "paciente.hpp"
#include "fila.hpp"
#include "lista.hpp"

int main(void){
    
    lista l;
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

    l.inserir(&p);
    l.inserir(&p2);
    l.inserir(&p3);
    l.inserir(&p4);

    l.listar();

    l.apagar(5);

    l.listar();


    return(0);
}