#ifndef AVL
#define AVL
using namespace std;
#include "paciente.hpp"

/*
a lista de pacientes é uma árvore AVL, na qual todos
os pacientes são inseridos ordenadamente em uma 
árvore binária de busca que se autobalanceia usando rotações
*/

typedef struct item{
    paciente *p;
    int altura;
    struct item *esq;
    struct item *dir;

    // cria um nó cuja altura é inicialmente zero
    item(paciente *pac){
        p = pac;
        altura = 0;
        esq = dir = nullptr;
    }

}item;

typedef struct avl{
    item *raiz;
    int qtd;
    int idAtual;

    // construtor da AVL
    avl();
    // destrutor da AVL
    ~avl();
    void destroyItem(item *no);

    // atravessa a AVL em ordem
    void listar(item *raiz);

    int getAltura(item *raiz);
    int getFB(item *raiz);
    void setAltura(item *raiz);
    item *rotEsq(item *raiz);
    item *rotDir(item *raiz);
    item *balancear(item *raiz);
    item *insereAux(item *raiz, paciente *pac);
    bool inserir(paciente *pac);

    item *apagaItem(item *raiz, int id);
    void apagar(int id);

    item *busca(item *raiz, int id);

    int avl_size();
    bool avl_vazia();

}avl;



#endif