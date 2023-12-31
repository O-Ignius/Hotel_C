#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>


int tam_fornecedor() {
    int tamanho = 0;
    
    tamanho = sizeof(fornecedor) - sizeof(float);
    
    return tamanho;
}

fornecedor le_dados_fornecedor(int GLOBAL_tam_pont_dados_fornecedores) {
    //variaveis
    fornecedor dados;
    char txt[30] = "fornecedores.txt", bin[30] = "fornecedores.bin";
    int tam = sizeof(fornecedor);
    
    //coleta dados
    dados.codigo = retorna_id(txt, bin, tam, GLOBAL_tam_pont_dados_fornecedores);
    setbuf(stdin, NULL);
    printf("Digite o nome do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.nome);
    setbuf(stdin, NULL);
    printf("Digite a razão social do fornecedor: \n");
    scanf("%[^\n]s", dados.raz_soci);
    setbuf(stdin, NULL);
    printf("Digite a inscrição estadual do fornecedor: \n");
    scanf("%[^\n]s", dados.inscri_estad);
    setbuf(stdin, NULL);
    printf("Digite o CNPJ do fornecedor: \n");
    scanf("%[^\n]s", dados.cnpj);
    setbuf(stdin, NULL);
    printf("Digite o telefone do fornecedor: \n");
    scanf("%f", &dados.telefone);
    setbuf(stdin, NULL);
    printf("Digite o email do fornecedor: \n");
    scanf("%[^\n]s", dados.email);
    setbuf(stdin, NULL);
    printf("Digite a sigla do estado do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.estado);
    setbuf(stdin, NULL);
    printf("Digite a cidade do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.cidade);
    setbuf(stdin, NULL);
    printf("Digite o CEP da cidade do fornecedor: \n");
    scanf("%f", &dados.local.cep);
    setbuf(stdin, NULL);
    printf("Digite o bairro do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.bairro);
    setbuf(stdin, NULL);
    printf("Digite a rua do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.rua);
    setbuf(stdin, NULL);
    printf("Digite o número do fornecedor: \n");
    scanf("%f", &dados.local.numero);
    dados.delet = 0;
    return dados;
}

void menuFornecedores(int tipoAquivo, fornecedor **GLOBAL_dados_fornecedores, int *GLOBAL_tam_pont_dados_fornecedores) {
    int opcao = 0;
    fornecedor dados;
    while (opcao != 6) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de fornecedores - 1\n");
        printf("\tListar todos os fornecedores - 2\n");
        printf("\tListar um dos fornecedores - 3\n");
        printf("\tAlterar fornecedores - 4\n");
        printf("\tExcluir fornecedores - 5\n");
        printf("\tVoltar ao menu principal - 6\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_fornecedor(*GLOBAL_tam_pont_dados_fornecedores);
                if (tipoAquivo == 0) {
                    salva_cadastro_fornecedores_bin(dados);
                } else if (tipoAquivo == 1) {
                    salva_cadastro_fornecedores_txt(dados);
                }
                else {
                    salva_cadastro_fornecedores_mem(dados, &GLOBAL_dados_fornecedores, &(*GLOBAL_tam_pont_dados_fornecedores));
                }
                break;
            case 2:
                le_todos_fonecedores(*GLOBAL_dados_fornecedores, *GLOBAL_tam_pont_dados_fornecedores);
                break;
            case 3:
                le_fonecedor(*GLOBAL_dados_fornecedores, *GLOBAL_tam_pont_dados_fornecedores);
                break;
            case 4:
                altera_fonecedor(*GLOBAL_dados_fornecedores, *GLOBAL_tam_pont_dados_fornecedores);
                break;
            case 5:
                exclui_fonecedor(*GLOBAL_dados_fornecedores, *GLOBAL_tam_pont_dados_fornecedores);
                break;
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPRESSIONE ENTER PARA CONTINUAR...");
        getchar();
    }
}

void salva_cadastro_fornecedores_bin(fornecedor dados) {
    FILE *arquivo;

    arquivo = fopen("fornecedores.bin", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fonecedores!");
        exit(1);
    }
    fwrite(&dados, sizeof (fornecedor), 1, arquivo);

    fclose(arquivo);
}

void salva_cadastro_fornecedores_txt(fornecedor dados) {
    FILE *salva;
    int salvar, local, salvou = 0;

    salva = fopen("fornecedores.txt", "a");
    if (salva == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    salvar = fprintf(salva, "%d;%0.0f;%s;%s;%s;%s;%s;%0.0f;", dados.delet, dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
    if (salvar < 0) {   
        printf("Erro no salvamento do fornecedor!\n");
    } else {
        salvou++;
    }

    local = fprintf(salva, "%s;%0.0f;%s;%s;%s;%0.0f;\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
    if (local < 0) {
        printf("Erro no salvamento do fornecedor!\n");
    } else {
        salvou++;
    }

    if (salvou == 2) {
        printf("Salvo com Sucesso!");
    }

    fclose(salva);
}

void salva_cadastro_fornecedores_mem(fornecedor dados, fornecedor ***GLOBAL_dados_fornecedores, int *GLOBAL_tam_pont_dados_fornecedores) {
    //caso a variavel global GLOBAL_tam_pont_dados_acomodacao não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
    if (*GLOBAL_tam_pont_dados_fornecedores == 1) {
        **GLOBAL_dados_fornecedores = malloc(sizeof(acomodacao));
        ***GLOBAL_dados_fornecedores = dados;
    }
    //caso a variavel GLOBAL_tam_pont_dados_fornecedores tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
    //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
    else {
        **GLOBAL_dados_fornecedores = realloc(GLOBAL_dados_fornecedores, (*GLOBAL_tam_pont_dados_fornecedores)*sizeof(acomodacao));
        ***(GLOBAL_dados_fornecedores + (*GLOBAL_tam_pont_dados_fornecedores - 1)) = dados;
    }
    
    if (**GLOBAL_dados_fornecedores == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    }
    
    //aumenta o valor da variavel global
    (*GLOBAL_tam_pont_dados_fornecedores)++;
}

void le_fonecedor(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores) {
    FILE *arquivo;
    float codigo;
    fornecedor dados;
    int encontrado = 0, tam_point = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    printf("Digite o codigo do fornecedor que deseja ler: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f",
                    dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone, dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
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
                printf("\nCódigo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Nome: %s \n", token);
                token = strtok(NULL, ";");
                printf("Razão social: %s \n", token);
                token = strtok(NULL, ";");
                printf("Inscrição estadual: %s \n", token);
                token = strtok(NULL, ";");
                printf("CNPJ: %s \n", token);
                token = strtok(NULL, ";");
                printf("Email: %s \n", token);
                token = strtok(NULL, ";");
                printf("Telefone: %s \n", token);
                token = strtok(NULL, ";");
                printf("Estado: %s \n", token);
                token = strtok(NULL, ";");
                printf("CEP: %s \n", token);
                token = strtok(NULL, ";");
                printf("Cidade: %s \n", token);
                token = strtok(NULL, ";");
                printf("Bairro: %s \n", token);
                token = strtok(NULL, ";");
                printf("Rua: %s \n", token);
                token = strtok(NULL, ";");
                printf("Número: %s \n", token);
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
                    printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f",
                        GLOBAL_dados_fornecedores->codigo, GLOBAL_dados_fornecedores->nome, GLOBAL_dados_fornecedores->raz_soci, GLOBAL_dados_fornecedores->inscri_estad, GLOBAL_dados_fornecedores->cnpj, GLOBAL_dados_fornecedores->email, 
                        GLOBAL_dados_fornecedores->telefone, GLOBAL_dados_fornecedores->local.estado, GLOBAL_dados_fornecedores->local.cep, GLOBAL_dados_fornecedores->local.cidade, GLOBAL_dados_fornecedores->local.bairro, GLOBAL_dados_fornecedores->local.rua, GLOBAL_dados_fornecedores->local.numero);
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
}

void le_todos_fonecedores(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores) {
    FILE *arquivo;
    fornecedor dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0) {
            encontrado = 1;
            printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f",
                    dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone, 
                    dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
        }
    }

    fclose(arquivo);

    arquivo = fopen("fornecedores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro de abertura de arquivo TXT!\n");
        exit(1);
    }

    while (fgets(linha, sizeof (fornecedor), arquivo)) {
        token = strtok(linha, ";");
        dados.delet = atoi(token);

        if (dados.delet == 0) {
            encontrado = 1;
            token = strtok(NULL, ";");
            printf("\nCódigo: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Nome: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Razão social: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Inscrição estadual: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("CNPJ: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Email: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Telefone: %s \n", token);
            token = strtok(NULL, ";");
            printf("Dados do local:\n\tEstado: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("CEP: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Cidade: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Bairro: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Rua: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Número: %s \n", token);
        }
    }

    fclose(arquivo);
    
    //memoria
    for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_fornecedores; tam_point++) {
        if (GLOBAL_dados_fornecedores->delet == 0) {
            encontrado = 1;
            printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f",
                    GLOBAL_dados_fornecedores->codigo, GLOBAL_dados_fornecedores->nome, GLOBAL_dados_fornecedores->raz_soci, GLOBAL_dados_fornecedores->inscri_estad, GLOBAL_dados_fornecedores->cnpj, GLOBAL_dados_fornecedores->email, 
                    GLOBAL_dados_fornecedores->telefone, GLOBAL_dados_fornecedores->local.estado, GLOBAL_dados_fornecedores->local.cep, GLOBAL_dados_fornecedores->local.cidade, GLOBAL_dados_fornecedores->local.bairro, GLOBAL_dados_fornecedores->local.rua, GLOBAL_dados_fornecedores->local.numero);
        }
        
        //avança o ponteiro uma posição
        GLOBAL_dados_fornecedores++;
    }
    
    //retorna o ponteiro para a primeira posição
    GLOBAL_dados_fornecedores -= (tam_point - 1);
    if(encontrado == 0)
        printf("\nNenhum fornecedor cadastrado!");
}

void altera_fonecedor(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores) {
    FILE *arquivo, *altera;
    float codigo;
    fornecedor dados;
    int encontrado = 0, i = 0, tam = 0, salvar;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    printf("Digite o codigo do fornecedor que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados = le_dados_fornecedor(GLOBAL_tam_pont_dados_fornecedores);
            fseek(arquivo, -sizeof (fornecedor), 1);
            fwrite(&dados, sizeof (fornecedor), 1, arquivo);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("fornecedores.txt", "r");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
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
                dados = le_dados_fornecedor(GLOBAL_tam_pont_dados_fornecedores);
                dados.codigo = codigo;

                encontrado = 1;
            } else {
                token = strtok(NULL, ";");
                strcpy(dados.nome, token);
                token = strtok(NULL, ";");
                strcpy(dados.raz_soci, token);
                token = strtok(NULL, ";");
                strcpy(dados.inscri_estad, token);
                token = strtok(NULL, ";");
                strcpy(dados.cnpj, token);
                token = strtok(NULL, ";");
                strcpy(dados.email, token);
                token = strtok(NULL, ";");
                dados.telefone = atoff(token);
                token = strtok(NULL, ";");
                strcpy(dados.local.estado, token);
                token = strtok(NULL, ";");
                dados.local.cep = atoff(token);
                token = strtok(NULL, ";");
                strcpy(dados.local.cidade, token);
                token = strtok(NULL, ";");
                strcpy(dados.local.bairro, token);
                token = strtok(NULL, ";");
                strcpy(dados.local.rua, token);
                token = strtok(NULL, ";");
                dados.local.numero = atoff(token);
            }

            fprintf(altera, "%d;%0.0f;%s;%s;%s;%s;%s;%0.0f;", dados.delet, dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
            fprintf(altera, "%s;%0.0f;%s;%s;%s;%0.0f;\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
        }

        fclose(arquivo);
        fclose(altera);

        remove("fornecedores.txt");
        rename("temp.txt", "fornecedores.txt");
    }
    
    //memoria
    if (encontrado == 0) {
        for (i = 1; i < GLOBAL_tam_pont_dados_fornecedores; i++) {
            if (GLOBAL_dados_fornecedores->delet == 0) {
                if (GLOBAL_dados_fornecedores->codigo == codigo) {
                    dados = le_dados_fornecedor(GLOBAL_tam_pont_dados_fornecedores);
                    dados.codigo = codigo;
                    *(GLOBAL_dados_fornecedores) = dados;

                    encontrado = 1;
                    break;
                }
            }

            //avança o ponteiro uma posição
            GLOBAL_dados_fornecedores++;
        }

        //retorna o ponteiro para a primeira posição
        GLOBAL_dados_fornecedores -= (i - 1);
    }

    if (encontrado == 0) {
        printf("Fornecedor não encontrado!\n");
    } else {
        printf("Dados alterados com sucesso!\n");
    }

}

void exclui_fonecedor(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores) {
    FILE *arquivo, *exclui;
    float codigo;
    fornecedor dados;
    int encontrado = 0, i = 0, tam = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    printf("Digite o codigo do fornecedor que deseja excluir: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.delet = 1;
            fseek(arquivo, -sizeof (fornecedor), 1);
            fwrite(&dados, sizeof (fornecedor), 1, arquivo);
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

        exclui = fopen("temp.txt", "a");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (fornecedor), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(dados.nome, token);
            token = strtok(NULL, ";");
            strcpy(dados.raz_soci, token);
            token = strtok(NULL, ";");
            strcpy(dados.inscri_estad, token);
            token = strtok(NULL, ";");
            strcpy(dados.cnpj, token);
            token = strtok(NULL, ";");
            strcpy(dados.email, token);
            token = strtok(NULL, ";");
            dados.telefone = atoff(token);
            token = strtok(NULL, ";");
            strcpy(dados.local.estado, token);
            token = strtok(NULL, ";");
            dados.local.cep = atoff(token);
            token = strtok(NULL, ";");
            strcpy(dados.local.cidade, token);
            token = strtok(NULL, ";");
            strcpy(dados.local.bairro, token);
            token = strtok(NULL, ";");
            strcpy(dados.local.rua, token);
            token = strtok(NULL, ";");
            dados.local.numero = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados.delet = 1;

                encontrado = 1;
            }

            fprintf(exclui, "%d;%0.0f;%s;%s;%s;%s;%s;%0.0f;", dados.delet, dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
            fprintf(exclui, "%s;%0.0f;%s;%s;%s;%0.0f;\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
        }

        fclose(arquivo);
        fclose(exclui);

        remove("fornecedores.txt");
        rename("temp.txt", "fornecedores.txt");
    }
    
    //memoria
    if (encontrado == 0) {
        for (i = 1; i < GLOBAL_tam_pont_dados_fornecedores; i++) {
            if (GLOBAL_dados_fornecedores->delet == 0) {
                if (GLOBAL_dados_fornecedores->codigo == codigo) {
                    GLOBAL_dados_fornecedores->delet = 1;
                    encontrado = 1;
                    break;
                }
            }

            //avança o ponteiro uma posição
            GLOBAL_dados_fornecedores++;
        }

        //retorna o ponteiro para a primeira posição
        GLOBAL_dados_fornecedores -= (i - 1);
    }

    if (encontrado == 0) {
        printf("Fornecedor não encontrado!\n");
    } else {
        printf("Dados excluídos com sucesso!\n");
    }

}
