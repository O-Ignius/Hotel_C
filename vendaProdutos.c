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
            for(i = 1; i < *GLOBAL_tam_pont_dados_checks; i++){
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

contaHotel retornaVenda(float valor){
    contaHotel retorna;

    retorna.valor = valor;
    printf("\nQual será o método de pagamento? (0 - Dinheiro, 1 - cartão de débito, 2 - cartão de crédito): ");
    scanf("%d", &retorna.tipo);

    while (retorna.tipo < 0 || retorna.tipo > 2){
        printf("\nNúmero inválido! (Digite 0 - Dinheiro, 1 - cartão de débito, 2 - cartão de crédito: ");
        scanf("%d", &retorna.tipo);
    }

    if(retorna.tipo > 0){
        printf("Digite o dia de vencimento do seu cartão (1 - 30): ");
        scanf("%d", &retorna.DiaVencimento);

        while (retorna.DiaVencimento < 1 || retorna.DiaVencimento > 30){
            printf("\nNúmero inválido! (Digite de 1 a 30: ");
            scanf("%d", &retorna.DiaVencimento);
        } 
    } else
        retorna.DiaVencimento = 0;
    return retorna;
}

CaixaHotel verificaCaixa(){
    FILE *arquivo;
    CaixaHotel dados, retorna;
    retorna.contasAReceber = 0;
    retorna.valorEmCaixa = 0;
    retorna.valorEmCaixa = 0;
    
    arquivo = fopen("caixa.bin", "rb");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de contas!");
        exit(1);
    }

    fread(&dados, sizeof(CaixaHotel), 1, arquivo);
        retorna.valorEmCaixa += dados.valorEmCaixa;
        retorna.contasAReceber += dados.contasAReceber;
        retorna.contasAPagar = dados.contasAPagar;
    fclose(arquivo);

    return retorna;
}

void adicionaCaixa(CaixaHotel dadosCaixa){
    FILE *arquivo;
    int teste;
    
    //Adiciona ao caixa do hotel tanto em bin quanto txt      
    arquivo = fopen("caixa.bin", "wb");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de caixa!");
        exit(1);
    }

    fwrite(&dadosCaixa,sizeof(CaixaHotel), 1, arquivo);
    fclose(arquivo);
    
    arquivo = fopen("caixa.txt","w");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos do caixa!");
        exit(1);
    }

    teste = fprintf(arquivo,"%.2f;%.2f;%.2f;", dadosCaixa.valorEmCaixa, dadosCaixa.contasAReceber, dadosCaixa.contasAPagar);

    if(teste < 0)
        printf("Erro ao adicionar valor de caixa!\n");
    
    fclose(arquivo);
}

void adicionaContas_Bin(contaHotel dados){
    FILE *arquivo;

    //Adiciona ao hisotrico de vendas
    arquivo = fopen("contas.bin","ab");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de contas!");
        exit(1);
    }

    fwrite(&dados,sizeof(contaHotel), 1, arquivo);
    fclose(arquivo);
}

void adicionaContas_Txt(contaHotel dados){
    FILE *arquivo;
    int teste;

    arquivo = fopen("contas.txt","a");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de contas!");
        exit(1);
    }

    teste = fprintf(arquivo,"%d;%d;%d;%.2f\n",dados.delet, dados.tipo, dados.DiaVencimento, dados.valor);

    if(teste < 0)
        printf("\nErro ao adicionar transação!");
    fclose(arquivo);
}

contaHotel* adicionaContas_Mem(contaHotel dados, contaHotel *GLOBAL_dados_Contas, int *GLOBAL_tam_pont_dados_contas){
    //Realloca o o ponteiro para o tamanho necessário
    GLOBAL_dados_Contas = realloc(GLOBAL_dados_Contas, (*GLOBAL_tam_pont_dados_contas)*sizeof(contaHotel));

    //Aritimética para salvar os dados na última posição, como o tam começa em 1 e as posições em 0 é necessário o -1
    *(GLOBAL_dados_Contas + ((*GLOBAL_tam_pont_dados_contas) - 1)) = dados;
        
    //Verifica se foi possível alocar a memória necessária
    if (GLOBAL_dados_Contas == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    } else
        printf("\nVenda salva com sucesso!");

    //Aumenta o valor do tamanho
    (*GLOBAL_tam_pont_dados_contas)++;

    return GLOBAL_dados_Contas;
}

produto *vendeProduto(int BinOuTxt, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks, contaHotel *GLOBAL_dados_Contas, int *GLOBAL_tam_pont_dados_contas){  
    produto dadosProduto;
    reserva reser;
    contaHotel dadosConta;
    CaixaHotel dadosCaixa;

    int pagar, tipo;
    int quantidade, continuar = 0;
    float codReserva, valor, total = 0;

    reser = le_uma_reserva(GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas);
    
    if(reser.delet != 2){
        if(verificaCheckIn(reser.codigo, GLOBAL_dados_checkInOut, *GLOBAL_tam_pont_dados_checks) == 1){
            do{
                dadosProduto = le_produtos(GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);

                if(dadosProduto.delet != 2){
                    printf("\nDigite a quantidade que deseja comprar: ");
                    scanf("%d", &quantidade);

                    if(dadosProduto.estoque >= quantidade || quantidade < 0){
                        valor = dadosProduto.venda * quantidade;
                        total += valor;
                    } else 
                        printf("\nO estoque atual é de %d, não é possível realizar a venda!", dadosProduto.estoque);
                    
                    printf("Deseja adicionar mais algum produto? (Digite 1 para sim e 0 para não): ");
                    scanf("%d", &continuar);

                    while (continuar != 1 && continuar != 0){
                        printf("\nNúmero inválido! Digite 1 - Sim ou 0 - Não): ");
                        scanf("%d", &continuar);
                    }
                }
            } while (continuar == 1);

            printf("\nTotal a ser pago: %.2f", total);

            printf("\nDeseja anotar ou pagar a vista? (1 - anotar, 2 - pagar agora): ");
            scanf("%d", &pagar);

            while (pagar != 1 && pagar != 2){
                printf("\nNúmero inválido! (Digite 1 - anotar ou 2 - a vista): ");
                scanf("%d", &pagar);
            }
            
            if(pagar == 1){
                GLOBAL_dados_checkInOut = adicionaConsumo(reser.codigo, total, GLOBAL_dados_checkInOut, GLOBAL_tam_pont_dados_checks);
                //Chamar função de gerar nota
            } else{
                dadosConta = retornaVenda(total);
                //Verifica qual os valores de caixa e contas a receber do hotel
                dadosCaixa = verificaCaixa();

                //Caso o pagamento seja em dinheiro vai direto para o caixa
                if(dadosConta.tipo == 0){
                    //Adiciona o valor da compra ao caixa
                    dadosConta.delet = 1;
                    dadosCaixa.valorEmCaixa += total;
                } 
                //Caso o pagamento seja no cartão vai para as contas a receber
                else{
                    //Adiciona o valor da compra as contas a receber
                    dadosCaixa.contasAReceber += total;
                    dadosConta.delet = 0;
                }
                
                //Salva nos três tipos de memória
                adicionaCaixa(dadosCaixa);

                if(BinOuTxt == 0)
                    adicionaContas_Bin(dadosConta);
                    else if(BinOuTxt == 1)
                        adicionaContas_Txt(dadosConta);
                        else
                            GLOBAL_dados_Contas = adicionaContas_Mem(dadosConta, GLOBAL_dados_Contas, GLOBAL_tam_pont_dados_contas);
            }

            GLOBAL_dados_produtos = removeDoEstoque(dadosProduto.codigo, quantidade, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
            printf("\nProduto vendido!\n");
        } else
            printf("\nRealize o check-in nessa reserva para poder comprar!");
    }
}