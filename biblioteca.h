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
    int delet, estoque, estoque_min;
    float codigo, custo, venda;
    char descricao[300];

} produto;

//struct fornecedores
typedef struct {
    int delet;
    char nome[100], raz_soci[150], inscri_estad[100], cnpj[50], email[150];
    float codigo, telefone;
    endereco local;

} fornecedor;

//struct operadores sistema
typedef struct {
    int acesso, delet;
    float codigo;
    char nome[100], user[100], senha[100];

} operador;

/////////////////////////////   Indicar subrotinas  \\\\\\\\\\\\\\\\\\\\\\\\\\\\

//Coleta dados
/* Coleta os dados do cliente e os retorna em uma struct do tipo cad_clie*/
cad_clie le_dados_cad();
/* Coleta os dados do hotel e os retorna em uma struct do tipo hotel */
hotel le_dados_hotel();
/* Coleta os dados do tipo de acomodação e os retorna em uma struct do tipo cate_aco */
cate_aco le_dados_categ_acomod();
/* Coleta os dados da acomodação e os retorna em uma struct do tipo acomodacao */
acomodacao le_dados_acomod();
/* Coleta os dados do produto e os retorna em uma struct do tipo produto */
produto le_dados_produto();
/* Coleta os dados do fornecedor e os retorna em uma struct do tipo fornecedor */
fornecedor le_dados_fornecedor();
/* Coleta os dados do operador do sistema e os retorna em uma struct do tipo operador */
operador le_dados_operador();

//Variadas
/* Retorna um inteiro com relação ao tamanho da struct cliente para usar com relação ao ID */
int tam_clientes();
/* Retorna um inteiro com relação ao tamanho da struct cate_aco para usar com relação ao ID */
int tam_categ_acomod();
/* Retorna um inteiro com relação ao tamanho da acomodacao para usar com relação ao ID */
int tam_acomodacao();
/* Retorna um inteiro com relação ao tipo de arquivo (0 = bin --- !0 = txt) */
int selecionarTipoArquivo();
/* Retorna um float que é um numero de ID válido. Recebe o nome do arquivo txt, o nome do arquivo binário e o tamanho da struct guardada nos arquivos */
float retorna_id(char *nome_txt, char *nome_bin, int tam);

//Menus
void menuPrincipal();

void menuHotel();

void menuCliente(int tipoArquivo);

void menuReserva(int tipoArquivo);

void menuAcomodacoes(int tipoArquivo);

void menuProdutos(int tipoAquivo);

void menuFornecedores(int tipoAquivo);

void menuOperadores(int tipoAquivo);

//  Hotel

void salva_cadastro_hotel();

void le_cadastro_hotel();

void altera_hotel();

void exclui_hotel();

//  Clientes
void salva_cadastro_pessoa_bin(cad_clie saves);

void salva_cadastro_pessoa_txt(cad_clie saves);

void le_cadastro_pessoa();

void le_todos_cadastro_pessoa();

void alteraCliente();

void removeCliente();

//  Acomodação

void salva_cadastro_tipo_acomodacao_txt(cate_aco dados);

void salva_cadastro_tipo_acomodacao_bin(cate_aco dados);

void le_todos_tipo_acomodacao();

void le_tipo_acomodacao(float codigo);

void altera_tipo_acomodacao();

void remover_tipo_acomodacao();

// geral

void salva_cadastro_acomodacao_txt(acomodacao dados);

void salva_cadastro_acomodacao_bin(acomodacao dados);

void le_todas_acomodacoes();

void altera_acomodacoes();

void exclui_acomodacoes();

//Produtos

void salva_cadastro_produtos_bin(produto dados);

void salva_cadastro_produtos_txt(produto dados);

void le_produtos();

void le_todos_produtos();

void altera_produto();

void exclui_produto();

//Fornecedor

void salva_cadastro_fornecedores_bin(fornecedor dados);

void salva_cadastro_fornecedores_txt(fornecedor dados);

void le_fonecedor();

void le_todos_fonecedores();

void altera_fonecedor();

void exclui_fonecedor();

//Operador

void salva_cadastro_operadores_bin(operador dados);

void salva_cadastro_operadores_txt(operador dados);

void le_operador();

void le_todos_operadores();

void alterar_operador();

void exclui_operador();
