#ifndef LISTAPRIORITARIA
#define LISTAPRIORITARIA
using namespace std;
#define MAX_FILA 100
#include "paciente.hpp"

/*
a fila prioritária é uma heap estática na qual cada paciente é adicionado
no momento que dá entrada no pronto-socorro. a heap é uma heap minima
feita com base no valor "priority" de cada paciente
*/

typedef struct heap{
    paciente *fila[MAX_FILA];
    int fim;

    //construtor
    heap();

    //destrutor
    ~heap();

    //funções utilitárias principais
    int pai(int i);
    int filhoEsq(int i);
    int filhoDir(int i);
    void heap_swap(int i, int j);
    void heap_fix_up();
    bool inserir(paciente *pac);
    int priority(int i);
    int get_id(int i);
    int menorFilho(int i);
    bool temFilho(int i);
    void heap_fix_down();
    paciente *retirar();
    bool heap_cheia();
    bool heap_vazia();
    void heap_consultar();
    int heap_tamanho();
    paciente *buscar(int id);
    bool comparar(int a, int b);
}heap;


#endif