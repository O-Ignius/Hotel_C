#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

/////////////////////////////   subrotinas e Menu gerais  \\\\\\\\\\\\\\\\\\\

int selecionarTipoArquivo() {
    int tipoArquivo = 0;

    printf("\nDigite 0 para salvar as informações em arquivos binários, 1 para arquivos txt e 2 para salvar dados em memória: ");
    scanf("%d", &tipoArquivo);

    while (tipoArquivo != 0 && tipoArquivo != 1 && tipoArquivo != 2) {
        printf("Número inválido, digite novamente: ");
        scanf("%d", &tipoArquivo);
    }
    if (tipoArquivo == 0) {
        printf("Tipo de arquivo alterado para BINARIO!");
    } else if (tipoArquivo == 1) {
        printf("Tipo de arquivo alterado para TXT!");
    }
    else {
        printf("Salvando dados na memória, Cuidado!");
    }
    
    getchar();
    return tipoArquivo;
}

float retorna_id(char *nome_txt, char *nome_bin, int tam, int tam_pont) {
    FILE *txt, *bin;
    int tamanho = 0;
    char linha[300];
    void *aux = malloc(tam);

    txt = fopen(nome_txt, "r");
    if (txt == NULL) {
        printf("Erro de abertura de arquivo txt!");
        exit(1);
    }

    bin = fopen(nome_bin, "rb");
    if (bin == NULL) {
        printf("Erro de abertura de arquivo bin!");
        exit(1);
    }
    
    while(fgets(linha, sizeof(linha), txt)){
        tamanho++;
    }
    
    while(fread(aux, tam, 1, bin)){
        tamanho++;
    }
    
    //fecha binario
    fclose(bin);

    //fecha txt
    fclose(txt);
    
    //libera alocação dinamica
    free(aux);
    
    //aumenta com relação ao tamanho que está salvo em memória
    tamanho += (tam_pont - 1);
    
    return tamanho;
}

void menuPrincipal(hotel *GLOBAL_dados_hotel, cad_clie *GLOBAL_dados_cliente, acomodacao *GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, produto *GLOBAL_dados_produtos,
                   fornecedor *GLOBAL_dados_fornecedores, operador *GLOBAL_dados_operadores, reserva *GLOBAL_dados_reservas) {
    int opcao = 99, binOUtxt = 0;
    
    //parametros globais para ponteiros globais
    int GLOBAL_tam_pont_dados_cliente = 1; //ja usado!
    int GLOBAL_tam_pont_dados_acomodacao = 1; //ja usado!
    int GLOBAL_tam_pont_dados_categ_acomodacao = 1; //ja usado!
    int GLOBAL_tam_pont_dados_produtos = 1; //ja usado!
    int GLOBAL_tam_pont_dados_fornecedores = 1; //ja usado!
    int GLOBAL_tam_pont_dados_operadores = 1; //ja usado!
    int GLOBAL_tam_pont_dados_reservas = 1; //ja usado!

    
    setbuf(stdin, NULL);
    while (opcao != 0) {
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tHotel - 1\n");
        printf("\tClientes - 2\n");
        printf("\tReservas - 3\n");
        printf("\tTipo de Acomodações - 4\n");
        printf("\tAcomodações - 5\n");
        printf("\tProdutos - 6\n");
        printf("\tFornecedores - 7\n");
        printf("\tOperadores - 8\n");
        printf("\tConfigurações de salvamento - 9\n");
        printf("\tEncerrar - 0\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuHotel(binOUtxt, GLOBAL_dados_hotel);
                break;
            case 2:
                menuCliente(binOUtxt, GLOBAL_dados_cliente, &GLOBAL_tam_pont_dados_cliente);
                break;
            case 3:
                menuReserva(binOUtxt, GLOBAL_dados_reservas, GLOBAL_dados_acomodacao, &GLOBAL_tam_pont_dados_reservas, &GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 4:
                GLOBAL_dados_categ_acomodacao = menuTipoAcomodacoes(binOUtxt, GLOBAL_dados_categ_acomodacao, &GLOBAL_tam_pont_dados_categ_acomodacao);
                break;
            case 5:
                GLOBAL_dados_acomodacao = menuAcomodacoes(binOUtxt, GLOBAL_dados_categ_acomodacao, GLOBAL_dados_acomodacao, &GLOBAL_tam_pont_dados_categ_acomodacao, &GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 6:
                menuProdutos(binOUtxt, GLOBAL_dados_produtos, &GLOBAL_tam_pont_dados_produtos);
                break;
            case 7:
                menuFornecedores(binOUtxt, GLOBAL_dados_fornecedores, &GLOBAL_tam_pont_dados_fornecedores);
                break;
            case 8:
                menuOperadores(binOUtxt, GLOBAL_dados_operadores, &GLOBAL_tam_pont_dados_reservas);
                break;
            case 9:
                binOUtxt = selecionarTipoArquivo();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida, digite novamente: ");
                scanf("%d", &opcao);
                break;
        }
    }
    
    //liberando os ponteiros alocados:
    free(GLOBAL_dados_cliente);
    free(GLOBAL_dados_acomodacao);
    free(GLOBAL_dados_categ_acomodacao);
    free(GLOBAL_dados_produtos);
    free(GLOBAL_dados_fornecedores);
    free(GLOBAL_dados_operadores);
    free(GLOBAL_dados_reservas);
    free(GLOBAL_dados_hotel);
    
    printf("Fechando programa...");
}