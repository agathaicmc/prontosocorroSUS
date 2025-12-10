#include "IO.hpp"
#include <cstdio>

// Função para salvar os dados em um arquivo binário
bool SAVE(avl *avl, heap *heap){
    if(!avl || !heap) return false;

    // Salvando itens da avl
    /*
    As informações da avl são salvos em uma ordem determinada para facilitar a leitura posteriormente
    Antes de cada string é escrito o tamanho dela, para saber quantos caracteres devem ser lidos
    */

    // Abrindo o arquivo da avl no modo de escrita binário, retorna false se houver algum erro
    FILE *fp_avl = fopen("avl_itens.bin", "wb");
    if(!fp_avl) return false;

    // Escreve o valor idAtual para não pegar o id de um paciente falecido posteriormente
    fwrite(&(avl->idAtual), sizeof(int), 1, fp_avl);

    // Escreve o número de itens da avl, para saber quantas vezes deve ser feita a leitura
    fwrite(&(avl->qtd), sizeof(int), 1, fp_avl);

    // BFS para salvar a avl por níveis
    fila f;
    f.inserir(avl->raiz);

    while(!f.filaVazia()){
        item *aux = f.retirar();
        if(aux == nullptr) continue;
        
        // Escreve o id
        fwrite(&(aux->p->id), sizeof(int), 1, fp_avl);

        // Escreve o tamanho do nome
        int len = aux->p->nome.size();
        fwrite(&len, sizeof(int), 1, fp_avl);

        // Escreve o nome
        fwrite(aux->p->nome.data(), sizeof(char), len, fp_avl);

        // Escreve a prioridade
        fwrite(&(aux->p->priority), sizeof(int), 1, fp_avl);

        // Escreve quantidade de procedimentos do histórico
        fwrite(&(aux->p->hist.qtd), sizeof(int), 1, fp_avl);

        // Para cada um dos procedimentos, escreve seu tamanho e depois o procedimento em si
        for(procedimento *p = aux->p->hist.topo; p != nullptr; p = p->prox){
            int len = p->tratamento.size();
            fwrite(&len, sizeof(int), 1, fp_avl);
            fwrite(p->tratamento.data(), sizeof(char), len, fp_avl);
        }

        f.inserir(aux->esq);
        f.inserir(aux->dir);
    }

    // Fechando o arquivo da avl
    fclose(fp_avl); fp_avl = nullptr;


    // Salvando os itens da heap
    /*
    Na heap, apenas os números de id são salvos, pois como todos os pacientes que estão na heap estão também na avl,
    não há necessidade de salvar todos os campos de informação novamente (inclusive, criar novos pacientes resulta
    na criação de dois pacientes que são a mesma pessoa, o que posteriormente causa vazamento de memória). Na leitura, 
    o id é utilizado para obter o paciente por meio de uma busca na avl.
    */

    // Abrindo o arquivo da heap no modo de escrita binário, retorna false se houver algum erro
    FILE *fp_heap = fopen("heap_itens.bin", "wb");
    if(!fp_heap) return false;

    // Escreve a quantidade de elementos da heap
    int qtd = heap->heap_tamanho();
    fwrite(&(qtd), sizeof(int), 1, fp_heap);

    // Laço que percorre pela avl
    for(int i = 0; i < heap->heap_tamanho(); i++){
        // Escreve o id
        fwrite(&(heap->fila[i]->id), sizeof(int), 1, fp_heap);
    }

    // Fechando o arquivo da heap
    fclose(fp_heap); fp_heap = nullptr;

    // Retorna true se a leitura foi feita com êxito
    return true;
}

// Função para ler os itens salvos no arquivo binário
bool LOAD(avl *avl, heap *heap){
    if(!avl || !heap) return false;

    // Carregando os itens do arquivo na avl, na mesma ordem em que foram salvos

    // Abrindo o arquivo da avl no modo de leitura binário, retorna false se houver algum erro
    FILE *fp_avl = fopen("avl_itens.bin", "rb");
    if(fp_avl == NULL) return false;

    // Leitura do idAtual armazenado, já o colocando na avl
    int idAtual;
    fread(&idAtual, sizeof(int), 1, fp_avl);
    avl->idAtual = idAtual;

    // Leitura da quantidade de itens da avl
    int tam;
    fread(&tam, sizeof(int), 1, fp_avl);

    // Laço para leitura de todos os itens da avl
    for(int i = 0; i<tam; i++){
        // Para cada item da avl:

        // Declaração de variáveis auxiliares
        int id, namelen, histlen, pri; string name;

        // Leitura do id
        fread(&id, sizeof(int), 1, fp_avl);

        // Leitura do tamanho do nome do paciente
        fread(&namelen, sizeof(int), 1, fp_avl);

        // Mudança de tamanho da string para acomodar corretamente o nome
        name.resize(namelen);

        // Leitura do nome do paciente
        fread(&name[0], sizeof(char), namelen, fp_avl);

        // Leitura da prioridade do paciente
        fread(&pri, sizeof(int), 1, fp_avl);

        // Criação de um novo paciente com o nome lido
        paciente *pac = new paciente(name, pri);

        // Definição do id do novo paciente como o id lido
        pac->id = id;

        // Leitura da quantidade de procedimentos no historico
        fread(&histlen, sizeof(int), 1, fp_avl);

        // Para cada um dos procedimentos, lê-se o tamanho do procedimento e depois o procedimento em si
        for(int j = 0; j<histlen; j++){
            string p;
            int plen;
            fread(&plen, sizeof(int), 1, fp_avl);
            p.resize(plen);
            fread(&p[0], sizeof(char), plen, fp_avl);

            // Inserção do procedimento lido no histórico do paciente criado
            pac->hist.inserir(p);
        }

        avl->inserir(pac);

    }

    fclose(fp_avl);

    // Carregando os itens do arquvio da heap

    // Abrindo o arquivo da heap no modo de leitura binário, retorna false se houver algum erro
    FILE *fp_heap = fopen("heap_itens.bin", "rb");
    if(fp_heap == NULL) return false;

    // Leitura da quantidade de itens da heap
    fread(&tam, sizeof(int), 1, fp_heap);

    // Laço para leitura de todos os itens, que nesse caso, são apenas os ids
    for(int i = 0; i<tam; i++){
        // Declaração de variável auxiliar
        int id;

        // Leitura do id
        fread(&id, sizeof(int), 1, fp_heap);

        // Inserção na heap por meio de uma busca na avl (novamente, todos os pacientes da heap estão necessariamente na avl)
        item * aux = avl->busca(avl->raiz, id);
        
        heap->inserir(aux->p);
    }

    // Libera memória
    fclose(fp_heap);

    // Retorna true se a leitura foi feita com êxito
    return true;
}