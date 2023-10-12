/////////////////////////////   Biblioteca  \\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include "biblioteca.h"

//MAIN 

int main() {
    // setar linguagem pt-br
    setlocale(LC_ALL, "Portuguese");

    //Cria caso não existam
    fopen("cliente.txt", "a");
    fopen("cliente.bin", "ab");
    fopen("hotel.txt","a");
    fopen("acomodacoes.txt","a");
    fopen("acomodacoes.bin","a");
    fopen("categoria_acomo.bin","a");
    fopen("categoria_acomo.txt","a");
    
    menuPrincipal();
    return 0;
}