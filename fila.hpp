#ifndef SALADEESPERA
#define SALADEESPERA
using namespace std;
#define MAX_FILA 20
#include "paciente.hpp"

/*
a sala de espera é uma fila dinâmica, onde cada paciente
é adicionado no momento em que dá entrada, e é excluído
da fila ao ser chamado para atendimento.
a fila tem tamanho máximo arbitrário (20).
não há prioridade no atendimento.
*/

typedef struct posicao{
    paciente *p;
    struct posicao *prox;
}posicao;

typedef struct fila{
    posicao *frente;
    posicao *tras;
    int qtd;

    //construtor
    fila();

    //destrutor
    ~fila();

    //funções utilitárias principais
    bool inserir(paciente *pac);
    paciente *retirar();
    void consultar();

    //checagem de estado da fila
    bool filaCheia();
    bool filaVazia();
}fila;

#endif