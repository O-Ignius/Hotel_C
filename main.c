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
    fopen("protudos.bin","ab");
    fopen("fornecedores.bin","ab");
    fopen("operadores.bin","ab");
    salva_cadastro_hotel();
    menuPrincipal();
    return 0;
}
