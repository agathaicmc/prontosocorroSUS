#ifndef IO_H
	#define IO_H
    #include "historico.hpp"
	#include "paciente.hpp"
    #include "heap.hpp"
    #include "lista.hpp"

    bool SAVE(lista *lista, fila *fila); // Salva os itens da lista e da fila em arquivos
    bool LOAD(lista *lista, fila *fila); // Carrega os itens dos arquivos na lista e na fila
	  
#endif
