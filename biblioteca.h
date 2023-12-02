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

/////////////////////////////   Structs  \\\\\\\\\\\\\\\\\\\\\\\\
\

//struct moradia
typedef struct {
    char estado[4], cidade[100], bairro[100], rua[150];
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

//Structs reservas

typedef struct {
    int dia, mes, ano;
} data;

typedef struct {
    int delet;
    data inicio, fim;
    float codigo, codQuarto;
} reserva;

typedef struct {
    float codigo, valor;
    int quantidade;
}itens;

typedef struct {
    float frete, imposto, cod_forn;
    int qnt;
}entrega_produto;

typedef struct {
    //Recebe 1 caso já tenha sido feito chech-out e os pagamentos
    int delet;
    float codigoReserva;
    float valorDiarias, consumoHospede;
    //1 para pagas, 0 para não pagas
    int DiariasPagas;

}checkInOut;;

/////////////////////////////   Indicar subrotinas  \\\\\\\\\\\\\\\\\\\\\\\\\\\\

//Coleta dados
/* Coleta os dados do cliente e os retorna em uma struct do tipo cad_clie*/
cad_clie le_dados_cad(int GLOBAL_tam_pont_dados_cliente);
/* Coleta os dados do hotel e os retorna em uma struct do tipo hotel */
hotel le_dados_hotel();
/* Coleta os dados do tipo de acomodação e os retorna em uma struct do tipo cate_aco */
cate_aco le_dados_categ_acomod(int GLOBAL_tam_pont_dados_categ_acomodacao);
/* Coleta os dados da acomodação e os retorna em uma struct do tipo acomodacao */
acomodacao le_dados_acomod(int GLOBAL_tam_pont_dados_acomodacao);
/* Coleta os dados do produto e os retorna em uma struct do tipo produto */
produto le_dados_produto(int GLOBAL_tam_pont_dados_produtos);
/* Coleta os dados do fornecedor e os retorna em uma struct do tipo fornecedor */
fornecedor le_dados_fornecedor(int GLOBAL_tam_pont_dados_fornecedores);
/* Coleta os dados do operador do sistema e os retorna em uma struct do tipo operador */
operador le_dados_operador(int GLOBAL_tam_pont_dados_reservas);
/*Coleta os dados de datas, retornando uma struct com dia, mes e ano*/
data le_dados_data();
/*Coleta os dados de reservas, retornando uma struct com cod do quarto, data de começo e fim*/
reserva le_dados_reserva(int GLOBAL_tam_pont_dados_reservas);
/*Coleta os dados do produto entregue, retornando uma struct com id do produto, quantia entregue e o valor da compra de cada produto*/
itens le_valor_produto();
/*Coleta os dados da entrega de produtos, retornando uma struct com nome do fornecedor, valor do frete e valor do imposto*/
entrega_produto le_entrega_produto();

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
float retorna_id(char *nome_txt, char *nome_bin, int tam, int tam_pont);

//Menus
void menuPrincipal(hotel *GLOBAL_dados_hotel, cad_clie *GLOBAL_dados_cliente, acomodacao *GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, produto *GLOBAL_dados_produtos,
                   fornecedor *GLOBAL_dados_fornecedores, operador *GLOBAL_dados_operadores, reserva *GLOBAL_dados_reservas, entrega_produto *GLOBAL_dados_entrega_produto, itens *GLOBAL_dados_itens, checkInOut *GLOBAL_dados_checkInOut);

hotel *menuHotel(int tipoArquivo, hotel *GLOBAL_dados_hotel);

void menuCliente(int tipoArquivo, cad_clie **GLOBAL_dados_cliente, int *GLOBAL_tam_pont_dados_cliente);

void menuReserva(int tipoArquivo, reserva **GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int *GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao);

void menuTipoAcomodacoes(int tipoArquivo, cate_aco **GLOBAL_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_categ_acomodacao);

void menuAcomodacoes(int tipoArquivo, cate_aco *GLOBAL_dados_categ_acomodacao, acomodacao **GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_acomodacao);

void menuProdutos(int tipoAquivo, produto **GLOBAL_dados_produtos, int *GLOBAL_tam_pont_dados_produtos);

void menuFornecedores(int tipoAquivo, fornecedor **GLOBAL_dados_fornecedores, int *GLOBAL_tam_pont_dados_fornecedores);

void menuOperadores(int tipoAquivo, operador **GLOBAL_dados_operadores, int *GLOBAL_tam_pont_dados_reservas);

void menuTransacoes(int tipoArquivo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos, entrega_produto **GLOBAL_dados_entrega_produto, int *GLOBAL_tam_pont_dados_entrega_produto,
                    itens **GLOBAL_dados_itens, int *GLOBAL_tam_pont_dados_itens, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks);

void menu_checkInOut(int tipoArquivo, reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao, checkInOut **GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks);

//  Hotel
int verifica_Hotel(hotel *GLOBAL_dados_hotel);

void salva_cadastro_hotel(hotel dados, hotel *GLOBAL_dados_hotel);

void le_cadastro_hotel();

void exclui_hotel(hotel *GLOBAL_dados_hotel);

//  Clientes

void salva_cadastro_pessoa_bin(cad_clie saves);

void salva_cadastro_pessoa_txt(cad_clie saves);

void salva_cadastro_pessoa_mem(cad_clie saves, cad_clie ***GLOBAL_dados_cliente, int *GLOBAL_tam_pont_dados_cliente);

void le_cadastro_pessoa(cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente);

void le_todos_cadastro_pessoa(cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente);

void alteraCliente(cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente);

void removeCliente(cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente);

//  Acomodação

void salva_cadastro_tipo_acomodacao_txt(cate_aco dados);

void salva_cadastro_tipo_acomodacao_bin(cate_aco dados);

void salva_cadastro_tipo_acomodacao_mem(cate_aco dados, cate_aco ***GLOBAL_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_categ_acomodacao);

void le_todos_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao);

void le_tipo_acomodacao(float codigo, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao);

void altera_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao);

void remover_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao);

int valida_id_acomodacao(float id, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_categ_acomodacao);

// geral

cate_aco retorna_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao);

cate_aco retorna_tipo_acomodacao_memoria(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao);

void salva_cadastro_acomodacao_txt(acomodacao dados, cate_aco *GLOBAL_dados_categ_acomodacaoint, int GLOBAL_tam_pont_dados_categ_acomodacao);

void salva_cadastro_acomodacao_bin(acomodacao dados, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao);

void salva_cadastro_acomodacao_mem(acomodacao dados, acomodacao ***GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_acomodacao);

void le_todas_acomodacoes(acomodacao *GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_acomodacao);

acomodacao le_uma_acomodacao(float codigo, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao);

void altera_acomodacoes(acomodacao *GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_acomodacao);

void exclui_acomodacoes(acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao);

//Produtos

void salva_cadastro_produtos_bin(produto dados);

void salva_cadastro_produtos_txt(produto dados);

void salva_cadastro_produtos_mem(produto dados, produto ***GLOBAL_dados_produtos, int *GLOBAL_tam_pont_dados_produtos);

produto le_produtos(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos);

void le_todos_produtos(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos);

void altera_produto(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos);

void exclui_produto(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos);

//Fornecedor

void salva_cadastro_fornecedores_bin(fornecedor dados);

void salva_cadastro_fornecedores_txt(fornecedor dados);

void salva_cadastro_fornecedores_mem(fornecedor dados, fornecedor ***GLOBAL_dados_fornecedores, int *GLOBAL_tam_pont_dados_fornecedores);

void le_fonecedor(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores);

void le_todos_fonecedores(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores);

void altera_fonecedor(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores);

void exclui_fonecedor(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores);

//Operador

void salva_cadastro_operadores_bin(operador dados);

void salva_cadastro_operadores_txt(operador dados);

void salva_cadastro_operadores_mem(operador dados, operador ***GLOBAL_dados_operadores, int *GLOBAL_tam_pont_dados_reservas);

void le_operador(operador *GLOBAL_dados_operadores, int GLOBAL_tam_pont_dados_reservas);

void le_todos_operadores(operador *GLOBAL_dados_operadores, int GLOBAL_tam_pont_dados_reservas);

void alterar_operador(operador *GLOBAL_dados_operadores, int GLOBAL_tam_pont_dados_reservas);

void exclui_operador(operador *GLOBAL_dados_operadores, int GLOBAL_tam_pont_dados_reservas);

//Reserva

void salva_cadastro_reserva_bin(reserva dados, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas);

void salva_cadastro_reserva_txt(reserva dados, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas);

void salva_cadastro_reserva_mem(reserva dados, reserva ***GLOBAL_dados_reservas, int *GLOBAL_tam_pont_dados_reservas);

int valida_data(data inicio, data fim, float id, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas);

void le_todas_reservas(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas);

reserva le_uma_reserva(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas);

int retornaDias(data inicio, data fim);

void altera_reserva(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas);

void exclui_reservas(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas);

void pesquisa_reserva_Categoria(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao);

void pesquisa_reserva_quantPessoas(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao);

void pesquisa_reserva_facilidade(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao);

void pesquisa_reserva_data(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao);

void pesquisa_reserva(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao);

void pesquisa_reserva_porTudo(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao);

//Transações

void entrada_produtos(int tipoArquivo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos, entrega_produto ***GLOBAL_dados_entrega_produto, int *GLOBAL_tam_pont_dados_entrega_produto, itens ***GLOBAL_dados_itens, int *GLOBAL_tam_pont_dados_itens);

int check_fornecedor(float codigo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores);

int check_produto(float codigo, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos);

void atualiza_estoque_produto(float codigo, int quantia, float frete, float imposto, float custo, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos);

void salva_entrada_produto_bin(entrega_produto fornecimento, int quantia, itens *produtos);

void salva_entrada_produto_txt(entrega_produto fornecimento, int quantia, itens *produtos);

void salva_entrada_produto_mem(entrega_produto fornecimento, entrega_produto ****GLOBAL_dados_entrega_produto, int *GLOBAL_tam_pont_dados_entrega_produto);

void salva_entrada_itens_mem(int quantia, itens *produtos, itens ****GLOBAL_dados_itens, int *GLOBAL_tam_pont_dados_itens);

void le_todas_entradas_produto(entrega_produto *GLOBAL_dados_entrega_produto, int GLOBAL_tam_pont_dados_entrega_produto, itens *GLOBAL_dados_itens, int GLOBAL_tam_pont_dados_itens);

//Check
int verificaCheckIn(float codReserva, checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks);

void checkOut(checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks);

checkInOut le_dados_checkIn(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao, checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks);

void salva_check_bin(checkInOut dados);

void salva_check_txt(checkInOut dados);

void salva_check_memoria(checkInOut dados, checkInOut ***GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks);

checkInOut *adicionaConsumo(float codReserva, float valor, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks);
//Vendas

produto *vendeProduto(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks);

produto *removeDoEstoque(float codigoProduto, int quantidade, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos);
