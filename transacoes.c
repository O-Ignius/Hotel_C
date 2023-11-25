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
    printf("Digite o ID do fornecedor: \n");
    scanf("%f", dados.cod_forn);
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
                entrada_produtos(GLOBAL_dados_fornecedores, GLOBAL_tam_pont_dados_fornecedores, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
                break;
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}

void entrada_produtos(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    int quantia, i, aux = 0;
    int stop1 = 0;
    float val_imposto, val_frete;
    entrega_produto fornecimento;
    
    while (stop1 != 1) {
        fornecimento = le_entrega_produto();
    
        if (check_fornecedor(fornecimento.cod_forn, GLOBAL_dados_fornecedores, GLOBAL_tam_pont_dados_fornecedores) == 1) {
            printf("Digite a quantia de produtos entregues: ");
            scanf("%d", &quantia);

            itens produtos[quantia];

            for (i = 0; i < quantia; i++) {
                produtos[i] = le_valor_produto();
                
                if (check_produto(produtos[i].codigo, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos) == 1) {
                    aux += produtos[i].quantia;
                }
                else {
                    i--;
                }
            }

            val_frete = (fornecimento.frete / aux);
            val_imposto = (fornecimento.imposto / aux);

            for (i = 0; i < quantia; i++) {
                atualiza_estoque_produto(produtos[i].codigo, produtos[i].quantia, val_frete, val_imposto, produtos[i].valor, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
            }
            
            //criar arquivo pra salvar entrada de produtos!
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
            printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                    dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
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
                printf("\nCódigo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Descrição: %s \n", token);
                token = strtok(NULL, ";");
                printf("Estoque mínimo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Estoque atual: %s \n", token);
                token = strtok(NULL, ";");
                printf("Custo do produto: R$%s \n", token);
                token = strtok(NULL, ";");
                printf("Preço de venda: R$%s \n", token);
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