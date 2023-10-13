/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   biblioteca.h
 * Author: Andre
 *
 * Created on 12 de outubro de 2023, 01:00
 */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* BIBLIOTECA_H */

/////////////////////////////   Structs  \\\\\\\\\\\\\\\\\\\\\\\\\

//struct moradia
typedef struct {
    char estado[2], cidade[100], bairro[100], rua[150];
    float numero, cep;

} endereco;

//struct check

typedef struct {
    int hora, min;
} check;

//struct cadastro hotel

typedef struct {
    int delet;
    char nome_hot[100], nome_respo[100], raz_soci[150], inscri_estad[100], cnpj[50], email[150];
    endereco local;
    float telefone_hot, telefone_respo, lucro;
    check in, out;

} hotel;

// struct cadastro cliente

typedef struct {
    int delet;
    float codigo, cpf, telefone;
    char nome[100], email[150], sexo[50], estado_civil[50], nascimento[15];
    endereco local;

} cad_clie;

//struct categoria acomodações

typedef struct {
    char descri[300];
    float codigo, diaria;
    int qnt_pessoas, delet;

} cate_aco;

//struct acomodações

typedef struct {
    int delet;
    float codigo;
    char descri[300], facilidades[300];
    cate_aco tipo;

} acomodacao;

//struct produtos

typedef struct {
    int codigo, estoque, estoque_min;
    float custo, venda;
    char descricao[300];

} produto;

//struct fornecedores

typedef struct {
    int codigo;
    char nome[100], raz_soci[150], inscri_estad[100], cnpj[50], email[150];
    float telefone;
    endereco local;

} fornecedor;

//struct operadores sistema

typedef struct {
    int codigo, acesso;
    char nome[100], user[100], senha[100];

} operador;

/////////////////////////////   Indicar subrotinas  \\\\\\\\\\\\\\\\\\\\\\\\\\\\

//Coleta dados

cad_clie le_dados_cad();

hotel le_dados_hotel();

cate_aco le_dados_categ_acomod();

acomodacao le_dados_acomod();

produto le_dados_produto();

fornecedor le_dados_fornecedor();

operador le_dados_operador();

//Variadas

int tam_clientes();

int tam_categ_acomod();

int tam_acomodacao();

int selecionarTipoArquivo();

float retorna_id(char *nome_txt, char *nome_bin, int tam);

//Menus

void menuPrincipal();

void menuHotel(int tipoArquivo);

void menuCliente(int tipoArquivo);

void menuReserva(int tipoArquivo);

void menuAcomodacoes(int tipoArquivo);


//  Hotel

void salva_cadastro_hotel();

void le_cadastro_hotel_txt();

void altera_hotel_txt();

//  Clientes
void salva_cadastro_pessoa_bin(cad_clie saves);

void salva_cadastro_pessoa_txt(cad_clie saves);

void le_cadastro_pessoa();

void le_todos_cadastro_pessoa();

void alteraCliente();

void removeCliente();

//  Acomodação

void salva_cadastro_tipo_acomodacao_txt(cate_aco dados);

void le_todos_tipo_acomodacao();

void le_tipo_acomodacao(float codigo);

void altera_tipo_acomodacao();

void remover_tipo_acomodacao();

// geral

void salva_cadastro_acomodacao_txt(acomodacao dados);
