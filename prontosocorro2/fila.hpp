#ifndef SALADEESPERA
#define SALADEESPERA
using namespace std;
#include "paciente.hpp"
#include "AVL.hpp"

/*
a sala de espera é uma fila dinâmica, onde cada paciente
é adicionado no momento em que dá entrada, e é excluído
da fila ao ser chamado para atendimento.
a fila tem tamanho máximo arbitrário (20).
não há prioridade no atendimento.
*/

typedef struct posicao{
    item *it;
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
    bool inserir(item *it);
    item *retirar();
    item *buscar(int id);
    item *buscarNome(string nome);
    void consultar();

    //checagem de estado da fila
    bool filaVazia();
}fila;

#endif