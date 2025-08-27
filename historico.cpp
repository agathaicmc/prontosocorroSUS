#include <cstdio>
#include "historico.hpp"

/*
construtor da pilha
*/

historico::historico(){
    topo = nullptr;
    qtd = 0;
}

/*
destrutor da pilha
*/

historico::~historico(){
    while(!historicoVazio()) retirar();
}



// função que insere um novo procedimento no histórico do paciente
bool historico::inserir(string str){
    // checa se o historico do paciente está cheio
    if(historicoCheio()){
        printf("Não é possível adicionar mais procedimentos no histórico deste paciente.\n");
        return false;
    }
    
    // cria um novo procedimento
    procedimento *aux = new procedimento;
    // coloca o dado dentro do procedimento
    aux->tratamento = str;
    // agora o prox aponta para o topo antigo
    aux->prox = topo;
    // atualiza o topo para apontar para aux, o novo topo
    topo = aux;
    // atualiza a quantidade de procedimentos no histórico
    qtd++;

    return true;
}


string historico::retirar(){
    if(historicoVazio()){
        printf("Não há procedimentos para serem retirados do histórico deste paciente.\n");
        return {};
    }
    // guarda o procedimento atual em um elemento
    string elemento = topo->tratamento;
    // cria um auxiliar que aponta para o topo
    procedimento *aux = topo;
    // atualiza o topo para apontar para o elemento abaixo dele
    topo = topo->prox;
    // deleta o topo antigo
    delete aux;
    // atualiza a quantidade de elementos no histórico
    qtd--;

    return elemento;
}

// função que imprime todos os elementos da pilha
void historico::consultar(){
    printf("Aqui está a lista dos procedimentos médicos deste paciente:\n");

    for(procedimento *p = topo; p != nullptr; p = p->prox){
        printf("%s\n", p->tratamento);
    }
}

// função que checa se o historico do paciente está cheio
bool historico::historicoCheio(){
    if (qtd == MAX_PILHA) return true;
    else return false;
}


// função que checa se o historico do paciente está vazio
bool historico::historicoVazio(){
    if (qtd == 0) return true;
    else return false;
}