#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

/////////////////////////////   subrotinas e Menu gerais  \\\\\\\\\\\\\\\\\\\

int selecionarTipoArquivo() {
    int tipoArquivo = 0;

    printf("\nDigite 0 para salvar as informações em arquivos binários e 1 para arquivos txt: ");
    scanf("%d", &tipoArquivo);

    while (tipoArquivo != 0 && tipoArquivo != 1) {
        printf("Número inválido, digite novamente: ");
        scanf("%d", &tipoArquivo);
    }
    if (tipoArquivo == 0) {
        printf("Tipo de arquivo alterado para BINARIO!");
    } else
        printf("Tipo de arquivo alterado para TXT!");
    getchar();
    return tipoArquivo;
}

float retorna_id(char *nome_txt, char *nome_bin, int tam) {
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
    
    return tamanho;
}

void menuPrincipal() {
    int opcao = 99, binOUtxt = 0;

    setbuf(stdin, NULL);
    while (opcao != 0) {
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tHotel - 1\n");
        printf("\tClientes - 2\n");
        printf("\tReservas - 3\n");
        printf("\tAcomodações - 4\n");
        printf("\tProdutos - 5\n");
        printf("\tFornecedores - 6\n");
        printf("\tOperadores - 7\n");
        printf("\tConfigurações de salvamento - 9\n");
        printf("\tEncerrar - 0\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuHotel(binOUtxt);
                break;
            case 2:
                menuCliente(binOUtxt);
                break;
            case 3:
                menuReserva(binOUtxt);
                break;
            case 4:
                menuAcomodacoes(binOUtxt);
                break;
            case 5:
                menuProdutos(binOUtxt);
                break;
            case 6:
                menuFornecedores(binOUtxt);
                break;
            case 7:
                menuOperadores(binOUtxt);
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
    printf("Fechando programa...");
    exit(1);
}