#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
#include "historico.hpp"
#include "paciente.hpp"
#include "fila.hpp"
#include "lista.hpp"

void criarPaciente(lista *list, fila *queue);
void adicionarProcedimento(fila *queue);
void removerProcedimento(fila *queue);
void darAlta(fila *queue);
void consultarFila(fila *queue);
void consultarHistorico(lista *list);

int main(void){
    lista l;
    fila f;

    // falta fazer a main com um while fgets pra ler comandos indefinidamente no terminal

    // falta fazer a permanência dos dados nesse código

    return(0);
}

void criarPaciente(lista *list, fila *queue){

    string nomePaciente;

    printf("Insira o nome do paciente a ser registrado.\n");
    getline(cin, nomePaciente);

    // verificar se paciente já existe na lista, mas coloca na fila de qualquer forma

    paciente *pac = new paciente(nomePaciente);

    list->inserir(pac);
    queue->inserir(pac);
    printf("\nPaciente registrado com sucesso!\n");
}

void adicionarProcedimento(fila *queue){
    int id;
    string procedimento;
    printf("\nDigite o ID do paciente que terá um procedimento adicionado em seu histórico.\n");
    
    scanf("%d", &id);
    cin.ignore();
    
    paciente *pac = queue->buscar(id);
    if(pac == nullptr) return;

    printf("\nDigite os detalhes sobre o procedimento a ser adicionado.\n");
    
    getline(cin, procedimento);

    pac->hist.inserir(procedimento);
}

void removerProcedimento(fila *queue){
    int id;
    printf("\nDigite o ID do paciente que terá o último procedimento de seu histórico removido.\n");

    scanf("%d", &id);

    paciente *pac = queue->buscar(id);
    if(pac == nullptr) return;

    string procedimentoRemovido = pac->hist.retirar();
    if(procedimentoRemovido == "") return;

    printf("\nO seguinte procedimento foi removido do histórico de %s:\n", pac->nome.c_str());
    printf("%s\n", procedimentoRemovido.c_str());
}

void darAlta(fila *queue){
    paciente *pac = queue->retirar();

    printf("\n%s recebeu alta!\n", pac->nome.c_str());
}

void consultarFila(fila *queue){
    queue->consultar();
}

void consultarHistorico(lista *list){
    int id;
    printf("\nDigite o ID de um paciente para consultar seu histórico médico.\n");

    scanf("%d", &id);

    item *it = list->buscar(id);

    if(it == nullptr) return;

    if(it == list->head){
        if(list->head->p->id == id) it->p->hist.consultar();
    } else {
        it->prox->p->hist.consultar();
    }
}