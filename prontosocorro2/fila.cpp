#include <cstdio>
#include "historico.hpp"
#include "paciente.hpp"
#include "fila.hpp"
#include "AVL.hpp"

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

// função que insere um novo item na fila
bool fila::inserir(item *it){
    // cria uma nova posição
    posicao *aux = new posicao;
    // coloca o item dentro da posição
    aux->it = it;
    // agora o prox aponta para null
    aux->prox = nullptr;

    // se a fila for vazia, frente e trás apontam para aux
    if(filaVazia()) frente = aux;
    // do contrário, alterar o tras->prox para o novo elemento
    else tras->prox = aux;

    // atualiza o 'tras' para o aux
    tras = aux;
    // atualiza a quantidade de itens na fila
    qtd++;

    return true;
}


// função que retira o item da frente da fila
item *fila::retirar(){
    // guardando o item atual numa variável temporária
    item *temp = frente->it;
    // passando a posição atual para uma posição auxiliar
    posicao *aux = frente;
    // atualizando o valor da frente da fila
    frente = frente->prox;
    // caso especial para caso a fila tivesse apenas um item
    if(frente == nullptr) tras = nullptr;
    // deletando a posição que costumava ser a frente
    delete aux;
    // atualiza a quantidade de itens na fila
    qtd--;
    // retornando o item
    return temp;
}

item *fila::buscar(int id){
    if(filaVazia()) return nullptr;
    // define um ponteiro auxiliar apontando para o item da frente da fila
    posicao *aux = frente;
    // checa se a frente da fila já é o item buscado
    if(aux->it->p->id == id) return aux->it;
    // checa todos os elementos da fila até encontrar o item desejado
    while(aux != nullptr && aux->it->p->id != id) aux = aux->prox;
    // caso aux == nullptr, o item não foi encontrado
    if(aux == nullptr) return nullptr;

    return aux->it;
}

item *fila::buscarNome(string nome){
    if(filaVazia()) return nullptr;
    // define um ponteiro auxiliar apontando para o item da frente da fila
    posicao *aux = frente;
    // checa se a frente da fila já é o item buscado
    if(aux->it->p->nome == nome) return aux->it;
    // checa todos os elementos da fila até encontrar o paciente desejado
    while(aux != nullptr && aux->it->p->nome != nome) aux = aux->prox;
    // caso aux == nullptr, o paciente não foi encontrado
    if(aux == nullptr) return nullptr;

    return aux->it;
}


// função que imprime todos os itens atualmente na sala de espera
void fila::consultar(){
    if(filaVazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return;
    }

    printf("\nListagem dos pacientes na fila de espera:\n");
    for(posicao *i = frente; i != nullptr; i = i->prox){
        printf("Nome: %s\n", i->it->p->nome.c_str());
        printf("ID: %d\n\n", i->it->p->id);
    }
}

// função que checa se a sala de espera está vazia
bool fila::filaVazia(){
    if(qtd == 0) return true;
    else return false;
}