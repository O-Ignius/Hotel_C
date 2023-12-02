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
    scanf("%f", &dados.codigo);
    setbuf(stdin, NULL);
    printf("Digite a quantia de produtos: \n");
    scanf("%d", &dados.quantidade);
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
    printf("Digite o ID do fornecedor: \n");
    scanf("%f", &dados.cod_forn);
    setbuf(stdin, NULL);
    printf("Digite o valor do frete: \n");
    scanf("%f", &dados.frete);
    setbuf(stdin, NULL);
    printf("Digite o imposto cobrado: \n");
    scanf("%f", &dados.imposto);
    setbuf(stdin, NULL);
    
    return dados;
}

void menuTransacoes(int tipoArquivo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
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
                if (tipoArquivo == 0) {
                    //bin
                } else if (tipoArquivo == 1) {
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
                entrada_produtos(tipoArquivo, GLOBAL_dados_fornecedores, GLOBAL_tam_pont_dados_fornecedores, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
                break;
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}

void entrada_produtos(int tipoArquivo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    int quantia, i, aux = 0;
    int stop1 = 0;
    float val_imposto, val_frete;
    entrega_produto fornecimento;
    
    while (stop1 != 1) {
        fornecimento = le_entrega_produto();
    
        if (check_fornecedor(fornecimento.cod_forn, GLOBAL_dados_fornecedores, GLOBAL_tam_pont_dados_fornecedores) == 1) {
            stop1 = 1;
            printf("Digite a quantia de produtos entregues: ");
            scanf("%d", &quantia);

            itens produtos[quantia];
            fornecimento.qnt = quantia;

            for (i = 0; i < quantia; i++) {
                produtos[i] = le_valor_produto();
                
                if (check_produto(produtos[i].codigo, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos) == 1) {
                    aux += produtos[i].quantidade;
                }
                else {
                    i--;
                }
            }

            val_frete = (fornecimento.frete / aux);
            val_imposto = (fornecimento.imposto / aux);

            for (i = 0; i < quantia; i++) {
                atualiza_estoque_produto(produtos[i].codigo, produtos[i].quantidade, val_frete, val_imposto, produtos[i].valor, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
            }
            
            //criar arquivo pra salvar entrada de produtos!
            switch(tipoArquivo) {
                case 0:
                    salva_entrada_produto_bin(fornecimento, quantia, produtos);
                    break;
                case 1:
                    break;
                case 2:
                    break;
            }
            
        }
        else {
            printf("Fornecedor não consta na base de dados!\n Favor cadastrá-lo! \n");
            printf("Encerrar entrada de produtos?   1- Sim    2- Não");
            scanf("%d", &stop1);
        }
    }
}

int check_fornecedor(float codigo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores) {
    FILE *arquivo;
    fornecedor dados;
    int encontrado = 0, tam_point = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("fornecedores.txt", "r");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (fornecedor), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                encontrado = 1;
            }
        }

        fclose(arquivo);
    }
    
    //memoria
    if (encontrado == 0) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_fornecedores; tam_point++) {
            if (GLOBAL_dados_fornecedores->delet == 0) {
                if (GLOBAL_dados_fornecedores->codigo == codigo) {
                    encontrado = 1;
                    break;
                }
            }

            //avança o ponteiro uma posição
            GLOBAL_dados_fornecedores++;
        }

        //retorna o ponteiro para a primeira posição
        GLOBAL_dados_fornecedores -= (tam_point - 1);
    }

    if (encontrado == 0) {
        printf("Nenhum fornecedor encontrado com esse código");
    }
    else {
        return 1;
    }
}

int check_produto(float codigo, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    FILE *arquivo;
    int encontrado = 0, tam_point = 0;
    produto dados;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro de Leitura de arquivo texto!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (produto), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                encontrado = 1;
            }
        }

        fclose(arquivo);
    }
    
    if (encontrado == 0) {
        //memoria
        if (GLOBAL_dados_produtos != NULL) {
            for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_produtos; tam_point++) {
                if (GLOBAL_dados_produtos->delet == 0) {
                    if (GLOBAL_dados_produtos->codigo == codigo) {
                        encontrado = 1;
                    }
                }

                // avança o ponteiro uma posição
                GLOBAL_dados_produtos++;
            }

            //retorna ponteiro para a primeira posição
            GLOBAL_dados_produtos -= (tam_point - 1);
        }
    }
    
    if(encontrado == 0){
        printf("Produto não encontrado!\n Verifique o código e tente novamente!\n");
    }
    else {
        return 1;
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

void salva_entrada_produto_bin(entrega_produto fornecimento, int quantia, itens *produtos) {
    FILE *bin;
    
    bin = fopen("entrada_produto.bin", "ab");
    if (bin == NULL) {
        printf("Erro de abertura de arquivo entrada_produto.bin!\n");
        exit(1);
    }
    
    fwrite(&fornecimento, sizeof(entrega_produto), 1, bin);
    fwrite(produtos, sizeof(itens), quantia, bin);
    
    fclose(bin);
}

void salva_entrada_produto_txt(entrega_produto fornecimento, int quantia, itens *produtos) {
    FILE *txt;
    int i = 0;
    
    txt = fopen("entrada_produto.txt", "a");
    if (txt == NULL) {
        printf("Erro de abertura de arquivo entrada_produto.bin!\n");
        exit(1);
    }
    
    //escreve os dados do fornecedor
    fprintf(txt, "%0.0f;%0.2f;%0.2f;%d;", fornecimento.cod_forn, fornecimento.frete, fornecimento.imposto, fornecimento.qnt);
    //escreve os dados dos produtos
    for (i = 0; i < quantia; i++) {
        if (i < quantia - 1) {
            fprintf(txt, "%0.0f;0.2%f;%d", produtos[i].codigo, produtos[i].valor, produtos[i].quantidade);
        }
        else {
            fprintf(txt, "%0.0f;%0.2f;%d;", produtos[i].codigo, produtos[i].valor, produtos[i].quantidade);
        }
    }
    //salta pra proxima linha ao acabar de escrever os dados
    fprintf(txt, "\n");
    
    fclose(txt);
}

void salva_entrada_produto_mem(entrega_produto fornecimento, int quantia, itens *produtos) {
    
}

void le_todas_entradas_produto() {
    FILE *arquivo;
    int i = 0;
    char forn[sizeof(entrega_produto)], prod[sizeof(itens)], *token1;
    itens *produtos = NULL;
    entrega_produto entrega;
    
    arquivo = fopen("entrada_produto.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro de abertura de arquivo entrada_produto.bin!\n");
        exit(1);
    }
    
    // le binario
    while(fread(&entrega, sizeof(entrega_produto), 1, arquivo)){
        printf("Fornecedor: %0.0f, frete %0.2f, imposto %0.2f, quantia produtos %d \n", entrega.cod_forn, entrega.frete, entrega.imposto, entrega.qnt);
        
        //alocar memoria para salvamento base em ponteiro
        produtos = malloc(sizeof(itens) * entrega.qnt);
        
        fread(produtos, sizeof(itens), entrega.qnt, arquivo);
        for (i = 0; i < entrega.qnt; i++) {
            printf("Codigo produto %0.0f, quantia %d, valor %0.2f\n", produtos[i].codigo, produtos[i].quantidade, produtos[i].valor);
        }
        
        //liberando memória
        free(produtos);
    }
    fclose(arquivo); //fim bin
    
    //le txt
    arquivo = fopen("entrada_produto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro de abertura de arquivo entrada_produto.bin!\n");
        exit(1);
    }
    
    while(fgets(forn, sizeof(entrega_produto), arquivo)) {
        /*
        token1 = strtok(";", forn);
        entrega.cod_forn = atoff(token1);
        token1 = strtok(";", NULL);
        entrega.frete = atoff(token1);
        token1 = strtok(";", NULL);
        entrega.imposto = atoff(token1);
        token1 = strtok(";", NULL);
        entrega.qnt = atoi(token1);
        */
        
        token1 = strtok(";", forn);
        printf("Código do fornecedor: %s\n", token1);
        token1 = strtok(";", NULL);
        printf("Frete: R$%s\n", token1);
        token1 = strtok(";", NULL);
        printf("Imposto: R$%s\n", token1);
        token1 = strtok(";", NULL);
        entrega.qnt = atoi(token1);
        printf("Quantia de produtos diferentes entregues: %s\n", token1);
        for (i = 0; i < entrega.qnt; i++) {
            while(fgets(prod, sizeof(itens), arquivo)) {
                token1 = strtok(";", NULL);
                printf("Código do produto: %s\n", token1);
                token1 = strtok(";", NULL);
                printf("Valor do produto: R$ %s\n", token1);
                token1 = strtok(";", NULL);
                printf("Quantia de produtos: %s\n", token1);
            }
        }
    }
    
    fclose(arquivo); //fim txt
    
    //le memoria
    
}