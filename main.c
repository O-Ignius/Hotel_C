/////////////////////////////   Biblioteca  \\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include "biblioteca.h"

//MAIN


//hotel
    hotel *GLOBAL_dados_hotel = NULL; //já usado!
    
    //cliente
    cad_clie *GLOBAL_dados_cliente = NULL; //já usado!

    //acomodações
    acomodacao *GLOBAL_dados_acomodacao = NULL; //já usado!

    //categoria acomodações
    cate_aco *GLOBAL_dados_categ_acomodacao = NULL; //já usado!

    //produtos
    produto *GLOBAL_dados_produtos = NULL; //já usado!
    
    //fornecedores
    fornecedor *GLOBAL_dados_fornecedores = NULL; //já usado!

    //operadores
    operador *GLOBAL_dados_operadores = NULL; //já usado!

    //reservas
    reserva *GLOBAL_dados_reservas = NULL; //já usado!

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
    fopen("reservas.txt","a");
    
    if(verifica_Hotel() == 0){
        hotel dados;
        dados = le_dados_hotel();
        salva_cadastro_hotel(dados, GLOBAL_dados_hotel);
    }

    menuPrincipal(GLOBAL_dados_hotel, GLOBAL_dados_cliente, GLOBAL_dados_acomodacao, GLOBAL_dados_categ_acomodacao, GLOBAL_dados_produtos, GLOBAL_dados_fornecedores, GLOBAL_dados_operadores, GLOBAL_dados_reservas);
    return 0;
}