#include <cstdio>
#include "historico.hpp"
#include "paciente.hpp"
#include "fila.hpp"

/*
construtor da fila
*/

fila::fila(){
    frente = nullptr;
    tras = nullptr;
    qtd = 0;
}

/*
destrutor da fila
*/

fila::~fila(){
    while(!filaVazia()) retirar();
}

// função que insere um novo paciente na sala de espera
bool fila::inserir(paciente *pac){
    if(filaCheia()){
        printf("\nA sala de espera está lotada.\n");
        return false;
    }

    // cria uma nova posição
    posicao *aux = new posicao;
    // coloca o paciente dentro da posição
    aux->p = pac;
    // agora o prox aponta para null
    aux->prox = nullptr;

    // se a fila for vazia, frente e trás apontam para aux
    if(filaVazia()) frente = aux;
    // do contrário, alterar o tras->prox para o novo elemento
    else tras->prox = aux;

    // atualiza o 'tras' para o aux
    tras = aux;
    // atualiza a quantidade de pacientes na fila
    qtd++;

    return true;
}


// função que chama o paciente que está na primeira posição da fila
paciente *fila::retirar(){
    if(filaVazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return nullptr;
    }

    // guardando o paciente atual numa variável temporária
    paciente *temp = frente->p;
    // passando a posição atual para uma posição auxiliar
    posicao *aux = frente;
    // atualizando o valor da frente da fila
    frente = frente->prox;
    // caso especial para caso a fila tivesse apenas um paciente
    if(frente == nullptr) tras = nullptr;
    // deletando a posição que costumava ser a frente
    delete aux;
    // atualiza a quantidade de pacientes na fila
    qtd--;
    // retornando o paciente
    return temp;
}

paciente *fila::buscar(int id){
    if(filaVazia()) return nullptr;
    // define um ponteiro auxiliar apontando para o paciente da frente da fila
    posicao *aux = frente;
    // checa se a frente da fila já é o paciente buscado
    if(aux->p->id == id) return aux->p;
    // checa todos os elementos da fila até encontrar o paciente desejado
    while(aux != nullptr && aux->p->id != id) aux = aux->prox;
    // caso aux == nullptr, o paciente não foi encontrado
    if(aux == nullptr){
        return nullptr;
    }

    return aux->p;
}


// função que imprime todos os pacientes atualmente na sala de espera
void fila::consultar(){
    if(filaVazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return;
    }

    printf("\nListagem dos pacientes na fila de espera:\n");
    for(posicao *i = frente; i != nullptr; i = i->prox){
        printf("Nome: %s\n", i->p->nome.c_str());
        printf("ID: %d\n\n", i->p->id);
    }
}


// função que checa se a sala de espera está cheia
bool fila::filaCheia(){
    if(qtd == MAX_FILA) return true;
    else return false;
}


// função que checa se a sala de espera está vazia
bool fila::filaVazia(){
    if(qtd == 0) return true;
    else return false;
}