#include "IO.hpp"
#include <cstdio>

// Função para salvar os dados em um arquivo binário
bool SAVE(lista *lista, fila *fila) {
    if(!lista || !fila) return false;

    // Salvando itens da lista
    /*
    As informações da lista são salvos em uma ordem determinada para facilitar a leitura posteriormente
    Antes de cada string é escrito o tamanho dela, para saber quantos caracteres devem ser lidos
    */

    // Abrindo o arquivo da lista no modo de escrita binário, retorna false se houver algum erro
    FILE *fp_lista = fopen("lista_itens.bin", "wb");
    if(!fp_lista) return false;

    // Escreve o valor idAtual para não pegar o id de um paciente falecido posteriormente
    fwrite(&(lista->idAtual), sizeof(int), 1, fp_lista);

    // Escreve o número de itens da lista, para saber quantas vezes deve ser feita a leitura
    fwrite(&(lista->qtd), sizeof(int), 1, fp_lista);

    // Laço para percorrer a lista inteira
    for(item *it = lista->head; it != nullptr; it = it->prox) {
        // Para cada paciente:


        // Escreve o id
        fwrite(&(it->p->id), sizeof(int), 1, fp_lista);

        // Escreve o tamanho do nome
        int len = it->p->nome.size();
        fwrite(&len, sizeof(int), 1, fp_lista);

        // Escreve o nome
        fwrite(it->p->nome.data(), sizeof(char), len, fp_lista);

        // Escreve quantidade de procedimentos do histórico
        fwrite(&(it->p->hist.qtd), sizeof(int), 1, fp_lista);

        // Para cada um dos procedimentos, escreve seu tamanho e depois o procedimento em si
        for(procedimento *p = it->p->hist.topo; p != nullptr; p = p->prox){
            int len = p->tratamento.size();
            fwrite(&len, sizeof(int), 1, fp_lista);
            fwrite(p->tratamento.data(), sizeof(char), len, fp_lista);
        }

    }

    // Fechando o arquivo da lista
    fclose(fp_lista); fp_lista = nullptr;


    // Salvando os itens da fila
    /*
    Na fila, apenas os números de id são salvos, pois como todos os pacientes que estão na fila estão também na lista,
    não há necessidade de salvar todos os campos de informação novamente (inclusive, criar novos pacientes resulta
    na criação de dois pacientes que são a mesma pessoa, o que posteriormente causa vazamento de memória). Na leitura, 
    o id é utilizado para obter o paciente por meio de uma busca na lista.
    */

    // Abrindo o arquivo da fila no modo de escrita binário, retorna false se houver algum erro
    FILE *fp_fila = fopen("fila_itens.bin", "wb");
    if(!fp_fila) return false;

    // Escreve a quantidade de elementos da fila
    fwrite(&(fila->qtd), sizeof(int), 1, fp_fila);

    // Laço que percorre pela lista
    for(posicao *it = fila->frente; it != nullptr; it = it->prox){
        // Escreve o id
        fwrite(&(it->p->id), sizeof(int), 1, fp_fila);

    }

    // Fechando o arquivo da fila
    fclose(fp_fila); fp_fila = nullptr;

    // Retorna true se a leitura foi feita com êxito
    return true;
}

// Função para ler os itens salvos no arquivo binário
bool LOAD(lista *lista, fila *fila){
    if(!lista || !fila) return false;

    // Carregando os itens do arquivo na lista, na mesma ordem em que foram salvos

    // Abrindo o arquivo da lista no modo de leitura binário, retorna false se houver algum erro
    FILE *fp_lista = fopen("lista_itens.bin", "rb");
    if(fp_lista == NULL) return false;

    // Leitura do idAtual armazenado, já o colocando na lista
    int idAtual;
    fread(&idAtual, sizeof(int), 1, fp_lista);
    lista->idAtual = idAtual;

    // Leitura da quantidade de itens da lista
    int tam;
    fread(&tam, sizeof(int), 1, fp_lista);

    // Lista de ponteiro para ponteiro para paciente, para guardar os pacientes lidos
    paciente **pacs = new paciente*[tam];

    // Laço para leitura de todos os itens da lista
    for(int i = 0; i<tam; i++){
        // Para cada item da lista:


        // Declaração de variáveis auxiliares
        int id; int namelen; string name; int histlen;

        // Leitura do id
        fread(&id, sizeof(int), 1, fp_lista);

        // Leitura do tamanho do nome do paciente
        fread(&namelen, sizeof(int), 1, fp_lista);

        // Mudança de tamanho da string para acomodar corretamente o nome
        name.resize(namelen);

        // Leitura do nome do paciente
        fread(&name[0], sizeof(char), namelen, fp_lista);

        // Criação de um novo paciente com o nome lido
        pacs[i] = new paciente(name);

        // Definição do id do novo paciente como o id lido
        pacs[i]->id = id;

        // Leitura da quantidade de procedimentos no historico
        fread(&histlen, sizeof(int), 1, fp_lista);

        // Para cada um dos procedimentos, lê-se o tamanho do procedimento e depois o procedimento em si
        for(int j = 0; j<histlen; j++){
            string p;
            int plen;
            fread(&plen, sizeof(int), 1, fp_lista);
            p.resize(plen);
            fread(&p[0], sizeof(char), plen, fp_lista);

            // Inserção do procedimento lido no histórico do paciente criado
            pacs[i]->hist.inserir(p);
        }

    }

    /*
    Laço para inserir cada um dos pacientes salvos no array "pacs" na lista em ordem inversa,
    garantindo que a lista lida tenha a mesma ordem da lista que foi salva anteriormente
    */
    for(int i = 0; i<tam; i++){
        lista->inserir(pacs[i]);
    }

    // Libera memória e fecha o arquivo da lista
    delete[] pacs;
    fclose(fp_lista);


    // Carregando os itens do arquvio da fila

    // Abrindo o arquivo da fila no modo de leitura binário, retorna false se houver algum erro
    FILE *fp_fila = fopen("fila_itens.bin", "rb");
    if(fp_fila == NULL) return false;

    // Leitura da quantidade de itens da fila
    fread(&tam, sizeof(int), 1, fp_fila);

    // Laço para leitura de todos os itens, que nesse caso, são apenas os ids
    for(int i = 0; i<tam; i++){

        // Declaração de variável auxiliar
        int id;

        // Leitura do id
        fread(&id, sizeof(int), 1, fp_fila);

        // Inserção na fila por meio de uma busca na lista (novamente, todos os pacientes da fila estão necessariamente na lista)
        item * aux = lista->buscar(id);
        // Tratamento de exceção em que o elemento buscado é o head da lista
        if(id == lista->head->p->id) fila->inserir(aux->p);
        else fila->inserir(aux->prox->p);
    }

    // Libera memória
    fclose(fp_fila);

    // Retorna true se a leitura foi feita com êxito
    return true;
}