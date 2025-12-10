#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
//#include "IO.hpp"
#include "historico.hpp"
#include "paciente.hpp"
#include "heap.hpp"
#include "AVL.hpp"

void registrarPaciente(avl *tree, heap *pqueue);
void registrarObito(avl *tree, heap *pqueue);
void adicionarProcedimento(heap *pqueue);
void removerProcedimento(heap *pqueue);
void chamarPaciente(heap *pqueue);
void consultarFila(heap *pqueue);
void consultarHistorico(avl *tree);
void consultarLista(avl *tree);

int main(void){

    avl a;
    heap h;

    //LOAD(&a, &h);

    int comandoAtual = -1;

    // rodando comandos de forma indefinida

    while(comandoAtual != 9){
        // interface simples para o usuário
        printf("\nLista de comandos do sistema hospitalar:\n");
        printf("1: Registrar paciente\n");
        printf("2: Registrar óbito de paciente\n");
        printf("3: Adicionar procedimento ao histórico médico de um paciente\n");
        printf("4: Desfazer procedimento do histórico médico de um paciente\n");
        printf("5: Chamar paciente para atendimento médico\n");
        printf("6: Mostrar fila de espera\n");
        printf("7: Mostrar histórico médico de um paciente\n");
        printf("8: Listar registros de pacientes\n");
        printf("9: Sair\n\n");
        printf("Digite o comando que deseja executar: ");

        scanf("%d", &comandoAtual);
        // cin.ignore() serve para ignorar o newline após o scanf
        cin.ignore();

        // mais comandos podem ser adicionados
        switch(comandoAtual){
            case 1:
                registrarPaciente(&a, &h);
                break;
            case 2:
                registrarObito(&a, &h);
                break;
            case 3:
                adicionarProcedimento(&h);
                break;
            case 4:
                removerProcedimento(&h);
                break;
            case 5:
                chamarPaciente(&h);
                break;
            case 6:
                consultarFila(&h);
                break;
            case 7:
                consultarHistorico(&a);
                break;
            case 8:
                consultarLista(&a);
                break;
            case 9:
                printf("\nEncerrando sistema...\n");
                break;
        }

    }

    //SAVE(&a, &h);

    return(0);
}


// função que registra um novo paciente, armazenando-o na lista e na fila
void registrarPaciente(avl *tree, heap *pqueue){
    if(pqueue->heap_cheia()){
        printf("\nA sala de espera está lotada.\n");
        return;
    }

    string nomePaciente;
    int pri;

    printf("\nInsira o nome do paciente a ser registrado: ");
    getline(cin, nomePaciente);

    printf("\nInsira o nível de prioridade do paciente: ");
    scanf("%d", &pri);
    paciente *pac = new paciente(nomePaciente, pri);

    tree->inserir(pac);
    pqueue->inserir(pac);
    printf("\nPaciente registrado com sucesso!\n");
}

// função que adiciona um procedimento médico ao histórico de um paciente, mediante busca por ID
void adicionarProcedimento(heap *pqueue){
    if(pqueue->heap_vazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return;
    }

    int id;
    string procedimento;
    printf("\nDigite o ID do paciente que terá um procedimento adicionado em seu histórico.\n");
    
    scanf("%d", &id);
    // cin.ignore() serve para ignorar o newline após o scanf
    cin.ignore();
    
    paciente *pac = pqueue->buscar(id);
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
void removerProcedimento(heap *pqueue){
    if(pqueue->heap_vazia()){
        printf("\nNão há pacientes na sala de espera no momento.\n");
        return;
    }
    
    int id;
    printf("\nDigite o ID do paciente que terá o último procedimento de seu histórico removido.\n");

    scanf("%d", &id);

    paciente *pac = pqueue->buscar(id);
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
void chamarPaciente(heap *pqueue){
    paciente *pac = pqueue->retirar();
    if(pac == nullptr) return;
    printf("\n%s foi chamado para atendimento!\n", pac->nome.c_str());
}

// função que imprime todos os pacientes da fila
void consultarFila(heap *pqueue){
    pqueue->heap_consultar();
}

// função que consulta o histórico médico de um paciente, mediante busca por ID
void consultarHistorico(avl *tree){
    if(tree->avl_vazia()){
        printf("\nNão há pacientes registrados no sistema.\n");
        return;
    }

    int id;
    printf("\nDigite o ID de um paciente para consultar seu histórico médico.\n");

    scanf("%d", &id);

    item *it = tree->busca(tree->raiz, id);

    if(it == nullptr){
        printf("\nNão há paciente com esse ID.\n");
        return;
    }

    it->p->hist.consultar();
}

// obito! obito uchiha!
void registrarObito(avl *tree, heap *pqueue){
    if(tree->avl_vazia()){
        printf("\nNão há pacientes registrados no sistema.\n");
        return;
    }

    int id;
    string nomePaciente;
    printf("\nDigite o ID de um paciente para registrar seu óbito.\n");
    
    scanf("%d", &id);
    
    // fazendo a checagem se o paciente está ou não na fila.
    // afinal, pacientes na fila são imortais

    paciente *pac = pqueue->buscar(id);
    if(pac != nullptr){ // tecnicamente não é necessário colocar esse != nullptr porém acho mais legível
        printf("\nPaciente ainda está na fila de espera. É proibido morrer!\n");
        return;
    }

    // guardando o paciente em uma variável temporária para armazenar seu nome
    item *it = tree->busca(tree->raiz, id);

    if(it == nullptr){
        printf("\nPaciente não existe.\n");
        return;
    }

    nomePaciente = it->p->nome;

    tree->apagar(id);
    printf("\n%s morreu :(\nDescanse em paz!\n", nomePaciente.c_str());
}

void consultarLista(avl *tree){
    tree->listar(tree->raiz);
}