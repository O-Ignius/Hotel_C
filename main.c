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
    fopen("acomodacoes.bin","ab");
    fopen("categoria_acomo.bin","ab");
    fopen("categoria_acomo.txt","a");
    fopen("hotel.bin","ab");
    fopen("produtos.bin","ab");
    fopen("produtos.txt","a");
    fopen("fornecedores.bin","ab");
    fopen("fornecedores.txt","a");
    fopen("operadores.bin","ab");
    fopen("operadores.txt","a");
    fopen("reservas.bin","ab");
    
    menuPrincipal();
    return 0;
}