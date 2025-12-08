#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
#include "historico.hpp"
#include "paciente.hpp"
#include "lista.hpp"
#include "heap.hpp"


int main(void){

    heap fila;

    paciente *pac = new paciente("joaozinho", 2);
    paciente *pac2 = new paciente("henry", 3);
    paciente *pac3 = new paciente("agatha", 1);
    paciente *pac4 = new paciente("berry", 1);

    fila.inserir(pac2);
    fila.heap_listar();
    printf("\n");
    fila.inserir(pac);
    fila.heap_listar();
    printf("\n");
    fila.inserir(pac3);
    fila.heap_listar();
    printf("\n");
    fila.inserir(pac4);
    fila.heap_listar();
    printf("\n");
}