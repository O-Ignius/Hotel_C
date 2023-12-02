#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

/////////////////////////////   subrotinas  \\\\\\\\\\\\\\\\\\\

produto *removeDoEstoque(float codigo, int quantidade, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos){
    FILE *arquivo, *altera;
    int encontrado = 0, tam_point = 0;
    produto dados;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.estoque -= quantidade;
            fseek(arquivo, -sizeof(produto), 1);
            fwrite(&dados, sizeof(produto), 1, arquivo);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        while (fgets(linha, sizeof(produto), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                encontrado = 1;
                
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

                dados.estoque -=quantidade;
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

            int salvar = fprintf(altera, "%d;%0.0f;%s;%d;%d;%0.2f;%0.2f;\n", dados.delet, dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            if (salvar < 0) {
                printf("\nErro ao alterar estoque!");
            }
        }

        fclose(arquivo);
        fclose(altera);

        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");
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
                        dados.codigo = GLOBAL_dados_produtos->codigo;
                        dados.delet = GLOBAL_dados_produtos->delet;
                        strcpy(dados.descricao, GLOBAL_dados_produtos->descricao);
                        dados.estoque_min = GLOBAL_dados_produtos->estoque_min;
                        dados.estoque = (GLOBAL_dados_produtos->estoque - quantidade);
                        dados.custo = GLOBAL_dados_produtos->custo;
                        dados.venda = GLOBAL_dados_produtos->venda;

                        *GLOBAL_dados_produtos = dados;
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
    }
    return GLOBAL_dados_produtos;
}

checkInOut *adicionaConsumo(float codReserva, float valor, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks){
    FILE *arquivo;
    int encontrado = 0;
    checkInOut dados;

    arquivo = fopen("checkInOut.bin", "rb + wb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo de Check-in bin");
        exit(1);
    }

    while (fread(&dados, sizeof(checkInOut), 1, arquivo)){
        if(dados.delet == 0){
            if(dados.codigoReserva == codReserva){
                encontrado = 1;
                dados.consumoHospede += valor;
                fseek(arquivo, -sizeof(checkInOut), 1);
                fwrite(&dados, sizeof(checkInOut), 1, arquivo);
                break;
            }
        }
    }
    
    fclose(arquivo);

    if(encontrado == 0){
        FILE *altera;
        arquivo = fopen("checkInOut.txt", "r");

        if(arquivo == NULL){
            printf("Erro ao abrir arquivo de Check-in txt");
            exit(1);
        }

        altera = fopen("checkInOut.txt", "a");

        if(altera == NULL){
            printf("Erro ao abrir arquivo de Check-in txt");
            exit(1);
        }

        char linha[(sizeof(checkInOut))], *token;
        while (fgets(linha, 1, arquivo)){
            token = strtok(linha, ";");
            //atoi passa string para int 
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            //atoff passa string para float
            dados.codigoReserva = atoff(token);
            token = strtok(NULL, ";");
            dados.consumoHospede = atoff(token);
            token = strtok(NULL, ";");
            dados.DiariasPagas = atoi(token);
            token = strtok(NULL, ";");
            dados.valorDiarias = atoff(token);

            //Caso o seja a reserva correta é adicionado o valor do consumo
            if(dados.delet == 0){
                if(dados.codigoReserva == codReserva){
                    encontrado = 1;
                    dados.consumoHospede += valor;
                }
            }
            //Todos os checkIns são passados para um novo arquivo
            int teste = fprintf(altera,"%d;%.0f;%.2f;%d;%.2f",dados.delet, dados.codigoReserva, dados.consumoHospede, dados.DiariasPagas, dados.valorDiarias);

            if(teste < 0)
                printf("\nFalha ao altera consumo!");
            else
                printf("\nConsumo alterado com sucesso!");
        }
        
        fclose(arquivo);
    }

    if(encontrado == 0){
        if(GLOBAL_dados_checkInOut != NULL){
            int i;
            for(i = 1; i < (*GLOBAL_tam_pont_dados_checks); i++){
                if(GLOBAL_dados_checkInOut->delet == 0){
                    if(GLOBAL_dados_checkInOut->codigoReserva == codReserva){
                        GLOBAL_dados_checkInOut->consumoHospede += valor;
                        encontrado = 1;
                        break;
                    }
                }
                //Aritimetica para passar para a próxima posição do ponteiro
                GLOBAL_dados_checkInOut++;
            }
            //Retorna o ponteiro para a posição inicial
            GLOBAL_dados_checkInOut -= (i -1);
        }
    }

    return GLOBAL_dados_checkInOut;
}

produto *vendeProduto(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks){
    produto dadosProduto;
    reserva reser;
    int quantidade;
    float codReserva, valor;

    reser = le_uma_reserva(GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas);
    
    if(reser.delet != 2){
        dadosProduto = le_produtos(GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);

        if(dadosProduto.delet != 2){
            printf("\nDigite a quantidade que deseja comprar: ");
            scanf("%d", &quantidade);

            valor = dadosProduto.venda * quantidade;

            int pagar;
            printf("\nDeseja anotar ou pagar a vista? (1 - anotar, 2 - a vista): ");
            scanf("%d", &pagar);

            while (pagar != 1 && pagar != 2){
                printf("\nNúmero inválido! Digite 1 - anotar ou 2 - a vista): ");
                scanf("%d", &pagar);
            }
            
            if(pagar == 1){
                //contas a receber
                GLOBAL_dados_checkInOut = adicionaConsumo(reser.codigo, valor, GLOBAL_dados_checkInOut, GLOBAL_tam_pont_dados_checks);
            } else{
                //adicionar ao caixa
            }
            GLOBAL_dados_produtos = removeDoEstoque(dadosProduto.codigo, quantidade, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);

            printf("\nProduto vendido:\n");

            //Chamar função de adicionar ao consumo e gerar nota
        } 
    }
}
