#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
#include "historico.hpp"
#include "paciente.hpp"
#include "lista.hpp"
#include "heap.hpp"


int main(void){

    paciente *pac = new paciente("joaozinho", 2);

    printf("%s\n", pac->nome.c_str());
    printf("%d\n", pac->priority);
}