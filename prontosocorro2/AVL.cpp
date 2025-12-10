#include <cstdio>
#include <string>
#include "historico.hpp"
#include "paciente.hpp"
#include "AVL.hpp"


// construtor da avl
avl::avl(){
    raiz = nullptr;
    qtd = 0;
    idAtual = 1;
}

// função auxiliar para o destrutor
void avl::destroyItem(item *no){
    if (no == nullptr) return;
    destroyItem(no->esq);
    destroyItem(no->dir);
    delete (no);
}

// destrutor da avl
avl::~avl(){
    if(raiz != nullptr) destroyItem(raiz);
}

// função para obter a altura de um item
int avl::getAltura(item *raiz){
    if(raiz == nullptr) return -1;
    return raiz->altura;
}

// função para obter fator de balanceamento de um item
int avl::getFB(item *raiz){
    return getAltura(raiz->esq) - getAltura(raiz->dir);
}

// função para definir a altura de um item
void avl::setAltura(item *raiz){
    raiz->altura = 1 + max(getAltura(raiz->esq), getAltura(raiz->dir));
}

// faz a rotação para a esquerda
item *avl::rotEsq(item *raiz){

    item *RST = raiz->dir;

    raiz->dir = RST->esq;
    RST->esq = raiz;

    // atualiza altura da raiz
    setAltura(raiz);
    setAltura(RST);

    return RST;
}

// faz a rotação para a direita
item *avl::rotDir(item *raiz){

    item *LST = raiz->esq;

    raiz->esq = LST->dir;
    LST->dir = raiz;

    // atualiza altura da raiz
    setAltura(raiz);
    setAltura(LST);

    return LST;
}

// balanceia a avl
item *avl::balancear(item *raiz){
    // atualizando altura da raiz pós inserção
    setAltura(raiz);
    int fator = getFB(raiz);

    // 4 casos simétricos

    // caso 1: direita da subárvore direita mais alta
    // solução: rotação esquerda
    if(fator < -1 && getFB(raiz->dir) <= 0) return rotEsq(raiz);

    // caso 2: esquerda da subárvore esquerda mais alta
    // solução: rotação direita
    if(fator > 1 && getFB(raiz->esq) >= 0) return rotDir(raiz);

    // caso 3: esquerda da subárvore direita mais alta
    // solução: rotação direita/esquerda
    if(fator < -1 && getFB(raiz->dir) > 0){
        raiz->dir = rotDir(raiz->dir);
        return rotEsq(raiz);
    }

    // caso 4: direita da subárvore esquerda mais alta
    // solução: rotação esquerda/direita

    if(fator > 1 && getFB(raiz->esq) < 0){
        raiz->esq = rotEsq(raiz->esq);
        return rotDir(raiz);
    }

    // caso a avl não tenha sofrido um desbalanceamento na inserção
    return raiz;
}

// função auxiliar para inserção
item *avl::insereAux(item *raiz, paciente *pac){
    // checando se a memória do sistema não estourou
    if(pac == nullptr) return nullptr;

    // se a subárvore é vazia
    if(raiz == nullptr){
        // seta automaticamente o id do novo paciente como o próximo inteiro disponível, a não ser que um id já exista
        if(pac->id == 0) pac->id = idAtual++;
        // cria um novo item
        return raiz = new item(pac);
    }

    // procura a posição certa para inserção
    if(raiz->p->id > pac->id) 
        raiz->esq = insereAux(raiz->esq, pac);
    else if(raiz->p->id < pac->id) 
        raiz->dir = insereAux(raiz->dir, pac);
    else return raiz;

    // depois de inserir, balanceia a avl!
    return balancear(raiz);
}

// função de inserção
bool avl::inserir(paciente *pac){
    if(pac == nullptr) return false;
    // realiza a inserção de fato
    raiz = insereAux(raiz, pac);
    // atualiza a quantidade de elementos na avl
    qtd++;
    return true;
}

// função auxiliar para apagar
item *avl::apagaItem(item *raiz, int id){
    // árvore vazia: nada para remover
    if (raiz == nullptr){
        printf("\nPaciente não encontrado.\n");
        return nullptr;
    }

    // busca pelo item desejado
    if(raiz->p->id > id)
        raiz->esq = apagaItem(raiz->esq, id);
    else if(raiz->p->id < id)
        raiz->dir = apagaItem(raiz->dir, id);
    // item encontrado
    else{
        item *temp;
        // caso 1: nó com 0 ou 1 filhos
        if(raiz->esq == nullptr){
            temp = raiz->dir;
            delete raiz->p;
            delete raiz;
            return temp;
        }
        else if(raiz->dir == nullptr){
            temp = raiz->esq;
            delete raiz->p;
            delete raiz;
            return temp;
        }
        // caso 2: nó com 2 filhos: pega o SUCESSOR da chave
        // pega o nó mais a esquerda da subárvore direita
        for(temp = raiz->dir; temp->esq != nullptr; temp = temp->esq);
        // troca o raiz com o temp
        paciente *aux = raiz->p;    
        raiz->p = temp->p;
        temp->p = aux;
        // remove o sucessor à direita da raiz
        raiz->dir = apagaItem(raiz->dir, temp->p->id);
    }
    return balancear(raiz);
}

// função de apagar 
void avl::apagar(int id){
    // atualiza a quantidade de elementos na avl
    qtd--;
    // faz a remoção
    raiz = apagaItem(raiz, id);
}

// função de busca que retorna o item procurado
item *avl::busca(item *raiz, int id){
    // chave não encontrada
    if(raiz == nullptr) return nullptr;

    if(raiz->p->id == id) return raiz;
    else if(raiz->p->id > id) return busca(raiz->esq, id);
    else return busca(raiz->dir, id);
}

// função para atravessar a avl em ordem e listar seus elementos
void avl::listar(item *raiz){
    if (raiz == nullptr) return;

    listar(raiz->esq);

    int p = raiz->p->priority;
    printf("Nome: %s\n", raiz->p->nome.c_str());
    printf("ID: %d\n", raiz->p->id);
    printf("Prioridade: %d - ", p);
    switch (p){
        case 1:
            printf("Emergência\n\n");
            break;
        case 2:
            printf("Muito Urgente\n\n");
            break;
        case 3:
            printf("Urgente\n\n");
            break;
        case 4:
            printf("Pouco Urgente\n\n");
            break;
        case 5:
            printf("Não Urgente\n\n");
            break;
    }

    listar(raiz->dir);
}

// função para checar se a avl está vazia
bool avl::avl_vazia(){
    if(qtd == 0) return true;
    return false;
}

// função para checar o tamanho da avl
int avl::avl_size(){
    return qtd;
}