#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>


int tam_produto() {
    int tamanho = 0;
    
    tamanho = sizeof(produto) - sizeof(float);
    
    return tamanho;
}

produto le_dados_produto(int GLOBAL_tam_pont_dados_produtos) {
    // variaveis
    produto dados;
    char txt[30] = "produtos.txt", bin[30] = "produtos.bin";
    int tam = sizeof(produto);

    //coleta dados
    dados.codigo = retorna_id(txt, bin, tam, GLOBAL_tam_pont_dados_produtos);
    setbuf(stdin, NULL);
    printf("Digite a descrição do produto: \n");
    scanf("%[a-z A-Z][^\n]s", dados.descricao);
    setbuf(stdin, NULL);
    printf("Digite o estoque do produto: \n");
    scanf("%d", &dados.estoque);
    setbuf(stdin, NULL);
    printf("Digite o estoque minimo do produto: \n");
    scanf("%d", &dados.estoque_min);
    setbuf(stdin, NULL);
    printf("Digite o preço de custo do produto: \n");
    scanf("%f", &dados.custo);
    setbuf(stdin, NULL);
    printf("Digite o preço de venda do produto: \n");
    scanf("%f", &dados.venda);
    dados.delet = 0;
    return dados;
}

produto *menuProdutos(int tipoAquivo, produto *GLOBAL_dados_produtos, int *GLOBAL_tam_pont_dados_produtos) {
    int opcao = 0;
    produto dados;
    while (opcao != 6) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de produtos - 1\n");
        printf("\tListar todos os produtos - 2\n");
        printf("\tListar um dos produtos - 3\n");
        printf("\tAlterar produtos - 4\n");
        printf("\tExcluir produtos - 5\n");
        printf("\tVoltar ao menu principal - 6\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_produto(*GLOBAL_tam_pont_dados_produtos);
                if (tipoAquivo == 0) {
                    salva_cadastro_produtos_bin(dados);
                } else if (tipoAquivo == 1) {
                    salva_cadastro_produtos_txt(dados);
                }
                else {
                    GLOBAL_dados_produtos = salva_cadastro_produtos_mem(dados, GLOBAL_dados_produtos, &(*GLOBAL_tam_pont_dados_produtos));
                }
                break;
            case 2:
                le_todos_produtos(GLOBAL_dados_produtos, *GLOBAL_tam_pont_dados_produtos);
                break;
            case 3:
                le_produtos(GLOBAL_dados_produtos, *GLOBAL_tam_pont_dados_produtos);
                break;
            case 4:
                altera_produto(GLOBAL_dados_produtos, *GLOBAL_tam_pont_dados_produtos);
                break;
            case 5:
                exclui_produto(GLOBAL_dados_produtos, *GLOBAL_tam_pont_dados_produtos);
                break;
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
    return GLOBAL_dados_produtos;
}

void salva_cadastro_produtos_bin(produto dados) {
    FILE *arquivo;

    arquivo = fopen("produtos.bin", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }
    printf("Codigo do prod: %0.0f", dados.codigo);
    fwrite(&dados, sizeof (produto), 1, arquivo);
    printf("\nProduto cadastrado com sucesso!");
    fclose(arquivo);
}

void salva_cadastro_produtos_txt(produto dados) {
    FILE *salva;
    int salvar;

    salva = fopen("produtos.txt", "a");
    if (salva == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    salvar = fprintf(salva, "%d;%0.0f;%s;%d;%d;%0.2f;%0.2f;\n", dados.delet, dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
    if (salvar < 0) {
        printf("Erro no salvamento do tipo de acomodação !\n");
    } else {
        printf("Salvo com sucesso!\n");
    }

    fclose(salva);
}

produto *salva_cadastro_produtos_mem(produto dados, produto *GLOBAL_dados_produtos, int *GLOBAL_tam_pont_dados_produtos) {
    //caso a variavel global GLOBAL_tam_pont_dados_acomodacao não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
    if (*GLOBAL_tam_pont_dados_produtos == 1) {
        GLOBAL_dados_produtos = malloc(sizeof(acomodacao));
        *GLOBAL_dados_produtos = dados;
    }
    //caso a variavel GLOBAL_tam_pont_dados_produtos tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
    //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
    else {
        GLOBAL_dados_produtos = realloc(GLOBAL_dados_produtos, (*GLOBAL_tam_pont_dados_produtos)*sizeof(acomodacao));
        *(GLOBAL_dados_produtos + (*GLOBAL_tam_pont_dados_produtos - 1)) = dados;
    }
    
    if (GLOBAL_dados_produtos == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    }
    
    //aumenta o valor da variavel global
    (*GLOBAL_tam_pont_dados_produtos)++;
    
    return GLOBAL_dados_produtos;
}

produto le_produtos(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    FILE *arquivo;
    float codigo;
    int encontrado = 0, tam_point = 0;
    produto dados, retorna;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    printf("Digite o codigo do produto que deseja ler: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                    dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            encontrado = 1;
            retorna = dados;
            break;
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
                printf("\nCódigo: %s \n", token);
                token = strtok(NULL, ";");
                strcpy(dados.descricao, token);
                printf("Descrição: %s \n", token);
                token = strtok(NULL, ";");
                dados.estoque_min = atoi(token);
                printf("Estoque mínimo: %s \n", token);
                token = strtok(NULL, ";");
                dados.estoque = atoi(token);
                printf("Estoque atual: %s \n", token);
                token = strtok(NULL, ";");
                dados.custo = atoff(token);
                printf("Custo do produto: R$%s \n", token);
                token = strtok(NULL, ";");
                dados.venda = atoff(token);
                printf("Preço de venda: R$%s \n", token);

                retorna = dados;
                break;
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
                        printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                        GLOBAL_dados_produtos->codigo, GLOBAL_dados_produtos->descricao, GLOBAL_dados_produtos->estoque_min, GLOBAL_dados_produtos->estoque, GLOBAL_dados_produtos->custo, GLOBAL_dados_produtos->venda);
                        retorna.codigo = GLOBAL_dados_produtos->codigo;
                        retorna.delet = GLOBAL_dados_produtos->delet;
                        strcpy(retorna.descricao, GLOBAL_dados_produtos->descricao);
                        retorna.estoque_min = GLOBAL_dados_produtos->estoque_min;
                        retorna.estoque = GLOBAL_dados_produtos->estoque;
                        retorna.custo = GLOBAL_dados_produtos->custo;
                        retorna.venda = GLOBAL_dados_produtos->venda;
                        break;
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
        printf("Produto não encontrado!");
        retorna.delet = 2;
    }
    return retorna;
}

void le_todos_produtos(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    FILE *arquivo;
    produto dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    //bin
    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0) {
            encontrado = 1;
            printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                    dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
        }
    }

    arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro de Leitura de arquivo texto!\n");
        exit(1);
    }

    //txt
    while (fgets(linha, sizeof (produto), arquivo)) {
        token = strtok(linha, ";");
        if (strcmp(token, "0") == 0) {
            encontrado = 1;
            token = strtok(NULL, ";");
            printf("\nCódigo: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Descrição: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Estoque mínimo: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Estoque atual: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Custo do produto: R$%s \n\t", token);
            token = strtok(NULL, ";");
            printf("Preço de venda: R$%s \n", token);
        }
    }

    fclose(arquivo);

    //memoria
    if (GLOBAL_dados_produtos != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_produtos; tam_point++) {
            if (GLOBAL_dados_produtos->delet == 0) {
                encontrado = 1;
                printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                    GLOBAL_dados_produtos->codigo, GLOBAL_dados_produtos->descricao, GLOBAL_dados_produtos->estoque_min, GLOBAL_dados_produtos->estoque, GLOBAL_dados_produtos->custo, GLOBAL_dados_produtos->venda);
            }
            
            // avança o ponteiro uma posição
            GLOBAL_dados_produtos++;
        }
        
        //retorna ponteiro para a primeira posição
        GLOBAL_dados_produtos -= (tam_point - 1);
    }
    if(encontrado == 0){
        printf("\nNenhum produto cadastrado!");
    }
}

void altera_produto(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    FILE *altera, *le;
    float codigo;
    produto dados;
    int encontrado = 0, tam = 0, i = 0, salvar;
    char linha[(sizeof (produto))], *token;

    altera = fopen("produtos.bin", "rb+wb");

    if (altera == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    printf("Digite o codigo do produto que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (produto), 1, altera)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados = le_dados_produto(GLOBAL_tam_pont_dados_produtos);
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
                dados = le_dados_produto(GLOBAL_tam_pont_dados_produtos);
                dados.codigo = codigo;
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
                        dados = le_dados_produto(GLOBAL_tam_pont_dados_produtos);
                        dados.codigo = codigo;
                        *GLOBAL_dados_produtos = dados;
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

    if (encontrado == 0) {
        printf("Produto não encontrado!\n");
    } else {
        printf("Dados alterados com sucesso!\n");
    }
}

void exclui_produto(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {

    FILE *arquivo, *exclui;
    float codigo;
    produto dados;
    int encontrado = 0, tam = 0, i = 0, salvar;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    printf("Digite o codigo do produto que deseja excluir: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.delet = 1;
            fseek(arquivo, -sizeof (produto), 1);
            fwrite(&dados, sizeof (produto), 1, arquivo);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        exclui = fopen("temp.txt", "a");
        if (exclui == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (produto), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
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
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados.delet = 1;
                encontrado = 1;
            }

            salvar = fprintf(exclui, "%d;%0.0f;%s;%d;%d;%0.2f;%0.2f;\n", dados.delet, dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            if (salvar < 0) {
                printf("Erro na exclusão!\n");
            }
        }

        fclose(arquivo);
        fclose(exclui);

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
                        GLOBAL_dados_produtos->delet = 1;
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

    if (encontrado == 0) {
        printf("Produto não encontrado!\n");
    } else {
        printf("Dados excluidos com sucesso!\n");
    }
}