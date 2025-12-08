#include <cstdio>
#include "historico.hpp"
#include "paciente.hpp"
#include "heap.hpp"

//construtor
heap::heap(){
    fim = -1;
}

//destrutor
heap::~heap(){
    // not much to delete here
    fim = -1;
}

//funções para facilitar cálculo de posições relativas na heap
int heap::pai(int i){
    return (i - 1)/2;
}

int heap::filhoEsq(int i){
    return 2*i + 1;
}

int heap::filhoDir(int i){
    return 2*i + 2;
}

// função para obter a prioridade de um elemento em uma posição da fila
int heap::priority(int i){
    return fila[i]->priority;
}

// função para trocar dois elementos da heap de lugar
void heap::heap_swap(int i, int j){
    paciente *temp = fila[i];
    fila[i] = fila[j];
    fila[j] = temp;
}

// função para restaurar a propriedade heap de baixo para cima
void heap::heap_fix_up(){
    int w = fim;
    int parent = pai(w);

    // troca um elemento com seu pai até que ele esteja na posição certa
    while (w > 0 && priority(w) < priority(parent)){
        heap_swap(w, parent);
        w = parent;
        parent = pai(parent);
    }
}

// função para inserir um novo elemento na heap
bool heap::inserir(paciente *pac){
    if(heap_cheia()){
        printf("\nA sala de espera está lotada.\n");
        return false;
    }
    
    // atualiza a posição do fim
    fim++;
    // insere o paciente novo no fim
    fila[fim] = pac;
    // restaura a ordem da heap
    heap_fix_up();

    return true;
}

// função para descobrir o maior filho de um dado elemento
int heap::menorFilho(int i){
    if(priority(filhoEsq(i)) < priority(filhoDir(i))) return filhoEsq(i);
    else return filhoDir(i);
}

// função que checa se um elemento tem ou não tem filho
bool heap::temFilho(int i){
    if(filhoEsq(i) <= fim || filhoDir(i) <= fim) return true;
    else return false; 
}

// função para restaurar a propriedade da heap de cima para baixo
void heap::heap_fix_down(){
    int w = 0;
    // enquanto um elemento tem filhos, troca ele com o menor filho
    // até que esteja na posição certas
    while(temFilho(w)){
        int m = menorFilho(w);
        if(priority(w) <= priority(m)) break;
        heap_swap(w, m);
        w = m;
    }
}

paciente *heap::retirar(){
    if(heap_vazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return nullptr;
    }

    // guarda o paciente com prioridade mais alta em uma variável temporária
    paciente *temp = fila[0];
    // copia fim no início
    fila[0] = fila[fim];
    // restaura ordem da heap
    heap_fix_down();
    // atualiza a posição do fim
    fim--;
    // retorna o paciente removido
    return temp;
}

bool heap::heap_cheia(){
    return(fim == MAX_FILA - 1);
}

bool heap::heap_vazia(){
    return(fim == -1);
}

// se quiser consertar o print...
void heap::heap_consultar(){
    if(heap_vazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return;
    }

    for(int i = 0; i <= fim; i++){
        printf("Nome: %s\n", fila[i]->nome.c_str());
        printf("ID: %d\n", fila[i]->id);
        printf("Prioridade: %d\n\n", priority(i));
    }
}

paciente *heap::buscar(int id){
    for(int i = 0; i <= fim; i++){
        if(fila[i]->id == id) return fila[i];
    }
    return nullptr;
}