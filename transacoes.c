#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include <ctype.h>

itens le_valor_produto() {
    itens dados;
    
    setbuf(stdin, NULL);
    printf("Digite o ID do produto: \n");
    scanf("%d", &dados.codigo);
    setbuf(stdin, NULL);
    printf("Digite a quantia de produtos: \n");
    scanf("%d", &dados.quantia);
    setbuf(stdin, NULL);
    printf("Digite o valor do produto: \n");
    scanf("%f", &dados.valor);
    setbuf(stdin, NULL);
    
    return dados;
}

entrega_produto le_entrega_produto() {
    int aux;
    entrega_produto dados;
    
    setbuf(stdin, NULL);
    printf("Digite o nome do fornecedor: \n");
    scanf("%s", dados.fornecedor);
    setbuf(stdin, NULL);
    printf("Digite o valor do frete: \n");
    scanf("%f", &dados.frete);
    setbuf(stdin, NULL);
    printf("Digite o imposto cobrado: \n");
    scanf("%f", &dados.imposto);
    setbuf(stdin, NULL);
    
    //Torna todos os caracteres da string minúsculos para facilitar busca posterior
    for (aux = 0; aux < strlen(dados.fornecedor); aux++) {
       dados.fornecedor[aux] = tolower((unsigned char) dados.fornecedor[aux]);
    }
    
    return dados;
}

void menuTransacoes(int tipoAquivo, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    int opcao = 0;
    produto dados;
    while (opcao != 6) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tControle de Caixa - 1\n");
        printf("\tContas a receber - 2\n");
        printf("\tContas a pagar - 3\n");
        printf("\tVenda de produtos - 4\n");
        printf("\tEntrada de produtos - 5\n");
        printf("\tVoltar ao menu principal - 6\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (tipoAquivo == 0) {
                    //bin
                } else if (tipoAquivo == 1) {
                    //txt
                }
                else {
                    //memoria
                }
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                entrada_produtos(GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
                break;
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}

void entrada_produtos(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    int quantia, i, aux = 0;
    float val_imposto, val_frete;
    entrega_produto fornecimento;
    
    fornecimento = le_entrega_produto();
    
    printf("Digite a quantia de produtos entregues: ");
    scanf("%d", &quantia);
    
    itens produtos[quantia];
    
    for (i = 0; i < quantia; i++) {
        produtos[i] = le_valor_produto();
        aux += produtos[i].quantia;
    }
    
    val_frete = (fornecimento.frete / aux);
    val_imposto = (fornecimento.imposto / aux);
    
    for (i = 0; i < quantia; i++) {
        atualiza_estoque_produto(produtos[i].codigo, produtos[i].quantia, val_frete, val_imposto, produtos[i].valor, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
    }
}

void atualiza_estoque_produto(float codigo, int quantia, float frete, float imposto, float custo, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    FILE *altera, *le;
    float lucro, valor_venda = 0;
    int encontrado = 0, tam = 0, i = 0, salvar;
    produto dados;
    char linha[(sizeof (produto))], *token;
    
    altera = fopen("hotel.bin", "rb");
    if (altera == NULL) {
        printf("Erro ao abrir hotel.bin!!\n");
        exit(1);
    }
    
    //posiciona o cursor para coletar o valor do lucro salvo
    fseek(altera, (-sizeof(float) - (2*sizeof(check))), SEEK_END);
    fread(&lucro, sizeof(float), 1, altera);
    
    fclose(altera);
    
    valor_venda = custo + frete + imposto;
    valor_venda += (valor_venda * (lucro / 100));
    
    //altera valor e quantia dos produtos
    
    altera = fopen("produtos.bin", "rb+wb");

    if (altera == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    while (fread(&dados, sizeof (produto), 1, altera)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.custo = custo;
            dados.estoque += quantia;
            dados.venda = valor_venda;
            fseek(altera, -sizeof (produto), 1);
            fwrite(&dados, sizeof (produto), 1, altera);
            encontrado = 1;
        }
    }

    fclose(altera);

    if (encontrado == 0) {
        le = fopen("produtos.txt", "r");
        if (le == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (produto), le)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados.custo = custo;
                dados.estoque += quantia;
                dados.venda = valor_venda;
            } else {
                token = strtok(NULL, ";");
                strcpy(dados.descricao, token);
                token = strtok(NULL, ";");
                dados.estoque_min = atoi(token);
                token = strtok(NULL, ";");
                dados.estoque = atoi(token);
                token = strtok(NULL, ";");
                dados.custo = atoff(token);
                token = strtok(NULL, ";");
                dados.venda = atoff(token);
            }

            salvar = fprintf(altera, "%d;%0.0f;%s;%d;%d;%0.2f;%0.2f;\n", dados.delet, dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            if (salvar < 0) {
                printf("Erro de salvamento de arquivo texto!\n");
            }
        }

        fclose(le);
        fclose(altera);

        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");
    }
    
    //memoria
    if (encontrado == 0) {
        if (GLOBAL_dados_produtos != NULL) {
            for (i = 1; i < GLOBAL_tam_pont_dados_produtos; i++) {
                if (GLOBAL_dados_produtos->delet == 0) {
                    if (GLOBAL_dados_produtos->codigo == codigo) {
                        encontrado = 1;
                        dados.custo = custo;
                        dados.estoque += quantia;
                        dados.venda = valor_venda;
                        *(GLOBAL_dados_produtos) = dados;
                        break;
                    }
                }

                // avança o ponteiro uma posição
                GLOBAL_dados_produtos++;
            }

            //retorna ponteiro para a primeira posição
            GLOBAL_dados_produtos -= (i - 1);
        }
    }

    if (encontrado != 0) {
        printf("Produtos atualizados com sucesso!\n");
    }
}