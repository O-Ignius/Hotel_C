#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>


int tam_categ_acomod() {
    int tamanho = 0;

    tamanho = sizeof (cate_aco) - sizeof (float);

    return tamanho;
}

cate_aco le_dados_categ_acomod(int GLOBAL_tam_pont_dados_categ_acomodacao) {
    //variaveis
    cate_aco dados;
    char bin[30] = "categoria_acomo.bin", txt[30] = "categoria_acomo.txt";
    int tam = sizeof(cate_aco);

    //coleta de dados
    dados.delet = 0;
    dados.codigo = retorna_id(txt, bin, tam, GLOBAL_tam_pont_dados_categ_acomodacao);
    setbuf(stdin, NULL);
    printf("Digite a descrição da acomodação: \n");
    scanf("%[^\n]", dados.descri);
    setbuf(stdin, NULL);
    printf("Digite o valor da diária: \n");
    scanf("%f", &dados.diaria);
    setbuf(stdin, NULL);
    printf("Digite a quantia de pessoas que a acomodação comporta: \n");
    scanf("%d", &dados.qnt_pessoas);
    setbuf(stdin, NULL);

    return dados;
}

void menuTipoAcomodacoes(int tipoArquivo, cate_aco **GLOBAL_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_categ_acomodacao) {
    int opcao = 0;
    cate_aco categ;
    while (opcao != 5) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de um tipo de acomodação - 1\n");
        printf("\tListar tipos de acomodação - 2\n");
        printf("\tAlterar um tipo de acomodação - 3\n");
        printf("\tExcluir um tipo de acomodação - 4\n");
        printf("\tVoltar ao menu principal - 5\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                categ = le_dados_categ_acomod(*GLOBAL_tam_pont_dados_categ_acomodacao);
                if (tipoArquivo == 0) {
                    salva_cadastro_tipo_acomodacao_bin(categ);
                } else if (tipoArquivo == 1) {
                    salva_cadastro_tipo_acomodacao_txt(categ);
                }
                else {
                    salva_cadastro_tipo_acomodacao_mem(categ, &GLOBAL_dados_categ_acomodacao, &(*GLOBAL_tam_pont_dados_categ_acomodacao));
                }
                break;
            case 2:
                le_todos_tipo_acomodacao(*GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao);
                break;
            case 3:
                altera_tipo_acomodacao(*GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao);
                break;
            case 4:
                remover_tipo_acomodacao(*GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao);
                break;
            case 5:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}

void salva_cadastro_tipo_acomodacao_txt(cate_aco dados) {
    FILE *salva;
    int salvar;

    salva = fopen("categoria_acomo.txt", "a");
    if (salva == NULL) {
        printf("Erro na abertura do arquivo categoria de acomodacoes!\n");
        exit(1);
    }

    salvar = fprintf(salva, "%d;%0.0f;%s;%0.2f;%d;\n", dados.delet, dados.codigo, dados.descri, dados.diaria, dados.qnt_pessoas);

    if (salvar < 0) {
        printf("Erro no salvamento do tipo de acomodação !\n");
    } else {
        printf("Categoria de acomodação salva com sucesso!\n");
    }

    fclose(salva);
}

void salva_cadastro_tipo_acomodacao_bin(cate_aco dados) {
    FILE *arquivo;

    arquivo = fopen("categoria_acomo.bin", "ab");

    if (arquivo == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    fwrite(&dados, sizeof (cate_aco), 1, arquivo);

    printf("Tipo de acomodação salvo com sucesso");

    fclose(arquivo);
}

void salva_cadastro_tipo_acomodacao_mem(cate_aco dados, cate_aco ***GLOBAL_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_categ_acomodacao) {
    //caso a variavel global GLOBAL_tam_pont_dados_acomodacao não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
    if (*GLOBAL_tam_pont_dados_categ_acomodacao == 1) {
        **GLOBAL_dados_categ_acomodacao = malloc(sizeof(acomodacao));
        ***GLOBAL_dados_categ_acomodacao = dados;
    }
    //caso a variavel GLOBAL_tam_pont_dados_categ_acomodacao tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
    //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
    else {
        **GLOBAL_dados_categ_acomodacao = realloc(GLOBAL_dados_categ_acomodacao, (*GLOBAL_tam_pont_dados_categ_acomodacao)*sizeof(acomodacao));
        ***(GLOBAL_dados_categ_acomodacao + (*GLOBAL_tam_pont_dados_categ_acomodacao - 1)) = dados;
    }
    
    if (**GLOBAL_dados_categ_acomodacao == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    }
    
    //aumenta o valor da variavel global
    (*GLOBAL_tam_pont_dados_categ_acomodacao)++;
}

void le_todos_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *ler;
    cate_aco acomodacao;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (cate_aco))], *token;

    ler = fopen("categoria_acomo.bin", "rb");

    if (ler == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }

    //bin
    while (fread(&acomodacao, sizeof (cate_aco), 1, ler)) {
        if (acomodacao.delet == 0) {
            printf("\nCódigo: %.0f\n\tDescrição: %s\n\tValor diária: %.2f\n\tNúmero de pessoas: %d",
                    acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
            encontrado =1;
        }
    }

    fclose(ler);

    ler = fopen("categoria_acomo.txt", "r");
    if (ler == NULL) {
        printf("Erro de abertura de arquivo !\n");
        exit(1);
    }

    //txt
    while (fgets(linha, sizeof (cate_aco), ler)) {
        token = strtok(linha, ";");

        if (strcmp(token, "0") == 0) {
            encontrado =1;
            token = strtok(NULL, ";");
            printf("\nCódigo: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Descrição: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Diária: R$%s\n\t", token);
            token = strtok(NULL, ";");
            printf("Quantia de pessoas que suporta: %s\n", token);
        }
    }

    fclose(ler);
    
    //memoria
    for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_categ_acomodacao; tam_point++) {
        if (GLOBAL_dados_categ_acomodacao->delet == 0) {
            encontrado =1;
            printf("\nCódigo: %.0f\n\tDescrição: %s\n\tValor diária: %.2f\n\tNúmero de pessoas: %d \n",
                    GLOBAL_dados_categ_acomodacao->codigo, GLOBAL_dados_categ_acomodacao->descri, GLOBAL_dados_categ_acomodacao->diaria, GLOBAL_dados_categ_acomodacao->qnt_pessoas);
        }
        
        GLOBAL_dados_categ_acomodacao++;
    }
    
    GLOBAL_dados_categ_acomodacao -= (tam_point - 1);
    if(encontrado == 0){
        printf("\nNenhuma categoria de acomodação cadastrada!");
    }
}

void le_tipo_acomodacao(float codigo, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *ler;
    cate_aco acomodacao;

    char linha[(sizeof (cate_aco))], *token;
    int encontrado = 0, tam_point = 0;

    ler = fopen("categoria_acomo.bin", "rb");

    if (ler == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }

    while (fread(&acomodacao, sizeof (cate_aco), 1, ler)) {
        if (acomodacao.delet == 0 && acomodacao.codigo == codigo) {
            printf("\n\tCódigo categoria: %.0f\n\tDescrição: %s\n\tValor diária: %.2f\n\tNúmero de pessoas: %d",
                    acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
            encontrado = 1;
        }
    }

    fclose(ler);

    //Testar se essa comparação esta funcionando

    if (encontrado == 0) {
        float cod;
        ler = fopen("categoria_acomo.txt", "r");
        if (ler == NULL) {
            printf("Erro de abertura de arquivo !\n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), ler)) {
            token = strtok(linha, ";");

            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                cod = atoff(token);

                //se o código foi igual ao digitado ele altera
                if (cod == codigo) {
                    printf("\nCódigo: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Descrição: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Diária: R$%s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Quantia de pessoas que suporta: %s\n", token);
                    
                    encontrado = 1;
                    break;
                }
            }
        }

        fclose(ler);
    }
    
    //memoria
    if (encontrado == 0) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_categ_acomodacao; tam_point++) {
            if (GLOBAL_dados_categ_acomodacao->delet == 0) {
                if (GLOBAL_dados_categ_acomodacao->codigo == codigo) {
                    printf("\nCódigo: %.0f\n\tDescrição: %s\n\tValor diária: %.2f\n\tNúmero de pessoas: %d \n",
                        GLOBAL_dados_categ_acomodacao->codigo, GLOBAL_dados_categ_acomodacao->descri, GLOBAL_dados_categ_acomodacao->diaria, GLOBAL_dados_categ_acomodacao->qnt_pessoas);
                    
                    encontrado = 1;
                    break;
                }
            }

            //avança uma posição
            GLOBAL_dados_categ_acomodacao++;
        }
        
        //retorna o ponteiro para primeira posição
        GLOBAL_dados_categ_acomodacao -= (tam_point - 1);
    }
}

void altera_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *le, *altera;
    cate_aco acomodacao, novo;
    char linha[(sizeof (cate_aco))], *token;
    int tam = 0, encontrado = 0, i = 0;
    float codigo;

    printf("Digite o código do tipo da acomodação que deseja alterar: \n");
    scanf("%f", &codigo);

    le = fopen("categoria_acomo.bin", "rb+wb");

    if (le == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }

    //bin
    while (fread(&acomodacao, sizeof (cate_aco), 1, le)) {
        if (acomodacao.delet == 0 && acomodacao.codigo == codigo) {
            acomodacao = le_dados_categ_acomod(GLOBAL_tam_pont_dados_categ_acomodacao);
            acomodacao.codigo = codigo;
            fseek(le, -sizeof (cate_aco), SEEK_CUR);
            fwrite(&acomodacao, sizeof (cate_aco), 1, le);
            encontrado = 1;
            printf("Tipo de acomodação alterado com sucesso!");
            break;
        }
    }

    fclose(le);

    //txt
    if (encontrado == 0) {
        le = fopen("categoria_acomo.txt", "r");
        if (le == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le)) {
            token = strtok(linha, ";");

            if (strcmp(token, "0") == 0) {
                acomodacao.delet = atoi(token);
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);

                if (acomodacao.codigo == codigo) {
                    acomodacao = le_dados_categ_acomod(GLOBAL_tam_pont_dados_categ_acomodacao);
                    acomodacao.codigo = codigo;
                    encontrado = 1;
                } else {
                    token = strtok(NULL, ";");
                    strcpy(acomodacao.descri, token);
                    token = strtok(NULL, ";");
                    acomodacao.diaria = atoff(token);
                    token = strtok(NULL, ";");
                    acomodacao.qnt_pessoas = atoi(token);
                }
            } else {
                acomodacao.delet = atoi(token);
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomodacao.descri, token);
                token = strtok(NULL, ";");
                acomodacao.diaria = atoff(token);
                token = strtok(NULL, ";");
                acomodacao.qnt_pessoas = atoi(token);
            }

            fprintf(altera, "%d;%0.0f;%s;%0.2f;%d", acomodacao.delet, acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
        }
        fclose(altera);
        fclose(le);

        remove("categoria_acomo.txt");
        rename("temp.txt", "categoria_acomo.txt");
    }
    
    //memoria
    if (encontrado == 0) {
        for (i = 1; i < GLOBAL_tam_pont_dados_categ_acomodacao; i++) {
            if (GLOBAL_dados_categ_acomodacao->delet == 0) {
                if (GLOBAL_dados_categ_acomodacao->codigo == codigo) {
                    encontrado = 1;
                    acomodacao = le_dados_categ_acomod(GLOBAL_tam_pont_dados_categ_acomodacao);
                    acomodacao.codigo = codigo;

                    *(GLOBAL_dados_categ_acomodacao) = acomodacao;
                    break;
                }
            }

            GLOBAL_dados_categ_acomodacao++;
        }

        GLOBAL_dados_categ_acomodacao -= (i - 1);
    }
    
    if (encontrado == 1) {
        printf("Dados alterados com sucesso!\n");
    } else {
        printf("Código digitado não encontrado!\n");
    }
}

void remover_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *remover, *le;
    cate_aco acomodacao;
    char linha[(sizeof (cad_clie))], *token;
    int tam = 0, i = 0, encontrado = 0;
    float codigo;

    printf("Digite o código do cliente a ser excluido:\n");
    scanf("%f", &codigo);

    le = fopen("categoria_acomo.bin", "rb+wb");

    if (le == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }
    
    //bin
    while (fread(&acomodacao, sizeof (cate_aco), 1, le)) {
        if (acomodacao.delet == 0 && acomodacao.codigo == codigo) {
            acomodacao.delet = 1;
            fseek(le, -sizeof (cate_aco), 1);
            fwrite(&acomodacao, sizeof (cate_aco), 1, le);
            encontrado = 1;
            break;
        }
    }

    fclose(le);

    //txt
    if (encontrado == 0) {
        le = fopen("categoria_acomo.txt", "r");
        if (le == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        remover = fopen("temp.txt", "a");
        if (remover == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le)) {
            token = strtok(linha, ";");
            acomodacao.delet = atoi(token);

            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomodacao.descri, token);
                token = strtok(NULL, ";");
                acomodacao.diaria = atoff(token);
                token = strtok(NULL, ";");
                acomodacao.qnt_pessoas = atoi(token);

                if (acomodacao.codigo == codigo) {
                    acomodacao.delet = 1;
                    encontrado = 1;
                }
            } else {
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomodacao.descri, token);
                token = strtok(NULL, ";");
                acomodacao.diaria = atoff(token);
                token = strtok(NULL, ";");
                acomodacao.qnt_pessoas = atoi(token);
            }

            fprintf(remover, "%d;%0.0f;%s;%0.2f;%d", acomodacao.delet, acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
        }

        fclose(remover);
        fclose(le);
        
        remove("categoria_acomo.txt");
        rename("temp.txt", "categoria_acomo.txt");
    }
    
    //memoria
    if (encontrado == 0) {
        for (i = 1; i < GLOBAL_tam_pont_dados_categ_acomodacao; i++) {
            if (GLOBAL_dados_categ_acomodacao->delet == 0) {
                if (GLOBAL_dados_categ_acomodacao->codigo == codigo) {
                    GLOBAL_dados_categ_acomodacao->delet = 1;
                    
                    break;
                }
            }

            GLOBAL_dados_categ_acomodacao++;
        }

        GLOBAL_dados_categ_acomodacao -= (i - 1);
    }

    if (encontrado == 1) {
        printf("Dados deletados com sucesso!\n");
    } else {
        printf("Código digitado não encontrado!\n");
    }
}
