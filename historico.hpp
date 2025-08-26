#ifndef HISTORICOMEDICO
#define HISTORICOMEDICO
#include <string>
using namespace std;

/*
o histórico de procedimentos médicos do paciente consiste em uma
pilha dinâmica, onde o topo aponta para o último procedimento
em andamento.
apesar da pilha ser dinâmica, o máximo de procedimentos médicos
do paciente será 10
*/

typedef struct procedimento{
    string tratamento;
    struct procedimento *prox;
}procedimento;

typedef struct historico{
    procedimento *topo;
    int qtd;

    // métodos das funções utilitárias
    
    // construtor
    historico();

    // destrutor
    ~historico();

    // funções utilitárias principais
    bool inserir(string str);
    string retirar();
    void consultar();

    // checagem de estado do historico
    bool historicoCheio();
    bool historicoVazio();



}historico;

#endif