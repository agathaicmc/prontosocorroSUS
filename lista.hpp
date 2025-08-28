#ifndef LISTA
#define LISTA
using namespace std;
#include "paciente.hpp"

/*
a lista de pacientes é uma lista encadeada, onde
todos os pacientes que dão entrada na emergência
são adicionados (a não ser que já estejam na lista).
não há restrições de tamanho.
*/

typedef struct item{
    paciente *p;
    struct item *prox;
}item;

typedef struct lista{
    item *head;
    
    // construtor
    lista();
    //destrutor
    ~lista();

    //funções utilitárias principais
    bool inserir(paciente *p);
    item *busca(int id);
    bool apagar(int id);
    void listar();
    
} lista;

#endif