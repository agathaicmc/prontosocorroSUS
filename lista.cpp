#include <cstdio>
#include <string>
#include "historico.hpp"
#include "paciente.hpp"
#include "lista.hpp"

/*
construtor da lista
*/
lista::lista(){
    head = nullptr;
    tail = nullptr;
    qtd = 0;
    idAtual = 1;
}

/*
destrutor da lista
*/
lista::~lista(){
    while(head != nullptr) apagar(head->p->id);
}


bool lista::inserir(paciente *pac){
    if(pac == nullptr) return false;
    
    // cria um novo item
    item *aux = new item;
    // seta automaticamente o id do novo paciente como o próximo inteiro disponível
    pac->id = idAtual++;
    // coloca o paciente dentro do item
    aux->p = pac;

    // se a lista for vazia, head e tail apontam para aux
    if(listaVazia()) head = aux;
    // do contrário, alterar o tail->prox para o novo elemento
    else tail->prox = aux;
    // atualiza tail para o aux
    tail = aux;
    // atualiza a quantidade de pacientes na lista
    qtd++;
    return true;
}

// função pra buscar o registro de um paciente dado um ID
item *lista::buscar(int id){
    // define um ponteiro auxiliar como o head (primeiro da lista)
    item *aux = head;
    // checando se o id é o primeiro elemento da lista
    if(aux->p->id == id) return aux;
    // loop que percorre até achar o item anterior ao certo ou até chegar no último item
    while(aux->prox != nullptr && aux->prox->p->id != id) aux = aux->prox; // nao vai tentar acessar NULL pq a verificacao do NULL vem antes (se achar gambiarrico demais fale)

    // se aux->prox for nullptr significa que não foi encontrado o id, então aux é definido como nullptr
    if(aux->prox == nullptr) aux = nullptr;

    // acho que é melhor verificar se a busca retornou null fora da funcao, me parece mais pratico
    return aux;
}

// função para apagar o registro de um paciente dado um ID
bool lista::apagar(int id){
    // achando o paciente com a função busca
    item *aux = buscar(id);

    // caso aux seja nullptr, a busca não encontrou o paciente.
    if(aux == nullptr){
        printf("\nPaciente não encontrado.\n");
        return false;
    }

    // caso contrario, há 3 casos diferentes: o item deletado ser o head, algum do meio ou o último.
    // caso seja o primeiro, o head será atualizado para o próximo item
    if(aux->p->id == id) head = head->prox;
    else{
        // ponteiro temporario para guardar a posicao do aux
        item *temp = aux;
        // aux vira o próximo item, ou seja, o que deve ser deletado
        aux = aux->prox;
        // ponteiro prox redefinido para pular o item que vai ser deletado
        temp->prox = temp->prox->prox;
    }

    // ponteiros do item são setados como nullptr
    delete aux->p;
    aux->prox = nullptr;
    
    // o item é deletado
    delete aux;
    // atualiza a quantidade de pacientes na lista
    qtd--;
    return true;
}

// função que percorre do head até o final (null) printando tudo
void lista::listar(){
    printf("\nRegistro dos pacientes:\n");
    item *aux = head;
    while(aux != nullptr){
        printf("Nome: %s\n", aux->p->nome.c_str());
        printf("ID: %d\n\n", aux->p->id);
        aux = aux->prox;
    }
    return;
}

bool lista::listaVazia(){
    if(qtd == 0) return true;
    else return false;
}

int lista::listaSize(){
    return qtd;
}