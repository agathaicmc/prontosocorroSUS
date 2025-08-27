#ifndef SALADEESPERA
#define SALADEESPERA
using namespace std;

#include "paciente.hpp"

/*
a sala de espera é uma fila dinâmica, onde cada paciente
é adicionado no momento em que dá entrada, e é excluído
da fila ao ser chamado para atendimento.
a fila tem tamanho máximo arbitrário (podemos escolher).
não há prioridade no atendimento.
*/

typedef struct No{
    paciente *prox;
    paciente p;
}No;

typedef struct fila{
    No *frente;
    No *tras;
    int qtd;

    //construtor
    fila();

    //destrutor
    ~fila();

    //funções utilitárias principais
    bool inserir(paciente p);
    paciente retirar();

    //checagem de estado
    bool filacheia();
    bool filavazia();
}fila;

#endif