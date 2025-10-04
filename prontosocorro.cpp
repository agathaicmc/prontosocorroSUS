#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
#include "IO.hpp"
#include "historico.hpp"
#include "paciente.hpp"
#include "fila.hpp"
#include "lista.hpp"

void registrarPaciente(lista *list, fila *queue);
void registrarObito(lista *list, fila *queue);
void adicionarProcedimento(fila *queue);
void removerProcedimento(fila *queue);
void chamarPaciente(fila *queue);
void consultarFila(fila *queue);
void consultarHistorico(lista *list);

int main(void){

    lista l;
    fila f;

    LOAD(&l, &f);

    int comandoAtual;

    // rodando comandos de forma indefinida

    while(comandoAtual != 8){
        // interface simples para o usuário
        printf("\nLista de comandos do sistema hospitalar:\n");
        printf("1: Registrar paciente\n");
        printf("2: Registrar óbito de paciente\n");
        printf("3: Adicionar procedimento ao histórico médico de um paciente\n");
        printf("4: Desfazer procedimento do histórico médico de um paciente\n");
        printf("5: Chamar paciente para atendimento médico\n");
        printf("6: Mostrar fila de espera\n");
        printf("7: Mostrar histórico médico de um paciente\n");
        printf("8: Sair\n\n");
        printf("Digite o comando que deseja executar: ");

        scanf("%d", &comandoAtual);
        // cin.ignore() serve para ignorar o newline após o scanf
        cin.ignore();

        // mais comandos podem ser adicionados
        switch(comandoAtual){
            case 1:
                registrarPaciente(&l, &f);
                break;
            case 2:
                registrarObito(&l, &f);
                break;
            case 3:
                adicionarProcedimento(&f);
                break;
            case 4:
                removerProcedimento(&f);
                break;
            case 5:
                chamarPaciente(&f);
                break;
            case 6:
                consultarFila(&f);
                break;
            case 7:
                consultarHistorico(&l);
                break;
            case 8:
                printf("\nEncerrando sistema...\n");
                break;
        }

    }

    SAVE(&l, &f);

    return(0);
}


// função que registra um novo paciente, armazenando-o na lista e na fila
void registrarPaciente(lista *list, fila *queue){
    if(queue->filaCheia()){
        printf("\nA sala de espera está lotada.\n");
        return;
    }

    string nomePaciente;

    printf("\nInsira o nome do paciente a ser registrado: ");
    getline(cin, nomePaciente);

    // verificar se paciente já existe na lista, mas coloca na fila de qualquer forma

    paciente *pac = new paciente(nomePaciente);

    list->inserir(pac);
    queue->inserir(pac);
    printf("\nPaciente registrado com sucesso!\n");
}

// função que adiciona um procedimento médico ao histórico de um paciente, mediante busca por ID
void adicionarProcedimento(fila *queue){
    if(queue->filaVazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return;
    }

    int id;
    string procedimento;
    printf("\nDigite o ID do paciente que terá um procedimento adicionado em seu histórico.\n");
    
    scanf("%d", &id);
    // cin.ignore() serve para ignorar o newline após o scanf
    cin.ignore();
    
    paciente *pac = queue->buscar(id);
    if(pac == nullptr){
        printf("\nPaciente não está na fila\n");
        return;
    }

    if(pac->hist.historicoCheio()){
        printf("\nNão é possível adicionar mais procedimentos no histórico deste paciente.\n");
        return;
    }

    printf("\nDigite os detalhes sobre o procedimento a ser adicionado.\n");
    
    getline(cin, procedimento);

    pac->hist.inserir(procedimento);
}

// função que remove um procedimento médico ao histórico de um paciente, mediante busca por ID
void removerProcedimento(fila *queue){
    if(queue->filaVazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return;
    }
    
    int id;
    printf("\nDigite o ID do paciente que terá o último procedimento de seu histórico removido.\n");

    scanf("%d", &id);

    paciente *pac = queue->buscar(id);
    if(pac == nullptr){
        printf("\nPaciente não está na fila\n");
        return;
    }

    string procedimentoRemovido = pac->hist.retirar();
    if(procedimentoRemovido == "") return;

    printf("\nO seguinte procedimento foi removido do histórico de %s:\n", pac->nome.c_str());
    printf("%s\n", procedimentoRemovido.c_str());
}

// função que remove o paciente da frente da fila
void chamarPaciente(fila *queue){
    paciente *pac = queue->retirar();
    if(pac == nullptr) return;
    printf("\n%s foi chamado para atendimento!\n", pac->nome.c_str());
}

// função que imprime todos os pacientes da fila
void consultarFila(fila *queue){
    queue->consultar();
}

// função que consulta o histórico médico de um paciente, mediante busca por ID
void consultarHistorico(lista *list){
    if(list->listaVazia()){
        printf("\nNão há pacientes registrados no sistema.\n");
        return;
    }

    int id;
    printf("\nDigite o ID de um paciente para consultar seu histórico médico.\n");

    scanf("%d", &id);

    item *it = list->buscar(id);

    if(it == nullptr){
        printf("\nNão há paciente com esse ID.\n");
        return;
    }

    // malabarismos necessários devido ao método de busca da lista
    if(it == list->head && list->head->p->id == id) it->p->hist.consultar(); 
    else it->prox->p->hist.consultar();
}

// obito! obito uchiha!
void registrarObito(lista *list, fila *queue){
    if(list->listaVazia()){
        printf("\nNão há pacientes registrados no sistema.\n");
        return;
    }

    int id;
    string nomePaciente;
    printf("\nDigite o ID de um paciente para registrar seu óbito.\n");
    
    scanf("%d", &id);
    
    // fazendo a checagem se o paciente está ou não na fila.
    // afinal, pacientes na fila são imortais

    paciente *pac = queue->buscar(id);
    if(pac != nullptr){ // tecnicamente não é necessário colocar esse != nullptr porém acho mais legível
        printf("\nPaciente ainda está na fila de espera. É proibido morrer!\n");
        return;
    }

    // guardando o paciente em uma variável temporária para armazenar seu nome
    item *it = list->buscar(id);

    if(it == nullptr){
        printf("\nPaciente não existe.\n");
        return;
    }

    // malabarismos necessários devido ao método de busca da lista
    if(it == list->head && list->head->p->id == id) nomePaciente = it->p->nome; 
    else nomePaciente = it->prox->p->nome;

    list->apagar(id);
    printf("\n%s morreu :(\nDescanse em paz!\n", nomePaciente.c_str());
}