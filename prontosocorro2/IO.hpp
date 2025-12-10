#ifndef IO_H
	#define IO_H
    #include "historico.hpp"
	#include "paciente.hpp"
    #include "heap.hpp"
    #include "fila.hpp"
    #include "AVL.hpp"

    bool SAVE(avl *avl, heap *heap); // Salva os itens da lista (AVL) e da fila (heap) em arquivos
    bool LOAD(avl *avl, heap *heap); // Carrega os itens dos arquivos na lista (AVL) e na fila (heap)
	  
#endif
