#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/////////////////////////////   subrotinas  \\\\\\\\\\\\\\\\\\\


checkInOut le_dados_checkIn(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao){
    checkInOut check;

    reserva reser = le_uma_reserva(GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas);
    //Caso nenhuma reserva ou acomodação com o código seja encontrada o .delet = 1
    if(reser.delet == 0){
        acomodacao acomod = le_uma_acomodacao(reser.codQuarto, GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_acomodacao);
        if(acomod.delet == 0){
            check.codigoReserva = reser.codigo;

            int dias = retornaDias(reser.inicio, reser.fim);

            check.valorDiarias = dias * acomod.tipo.diaria;

            printf("Data inicio: %d/%d/%d\tFim: %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);

            printf("Dias: %d", dias);

            printf("\nCusto: R$%.2f", check.valorDiarias);

            int pagar;
            printf("\nDeseja realizar o pagamento das diárias? (1 - sim, 2 - não): ");
            scanf("%d", &pagar);

            while (pagar != 1 || pagar != 2){
                printf("\nNúmero inválido! Digite 1 para sim e 2 para não): ");
                scanf("%d", &pagar);
            }
            
            if(pagar == 1){
                //realizar pagamento
                check.DiariasPagas = 1;
                check.consumoHospede = 0;
            } else{
                check.DiariasPagas = 0;
                check.consumoHospede = check.valorDiarias;
                //contas a receber
            }
            return check;
        }
    }
    
}

void menu_checkInOut(int tipoArquivo, reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int *GLOBAL_tam_pont_dados_reservas, int *GLOBAL_tam_pont_dados_acomodacao, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks){
    int opcao = 0;

    while (opcao != 3) {
        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tRealizar Check-In - 1\n");
        printf("\tRealizar Check-Out - 2\n");
        printf("\tVoltar ao menu principal - 3\n");

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
                    
                }
                break;
            case 2:
                le_dados_checkIn(GLOBAL_dados_reservas, *GLOBAL_tam_pont_dados_reservas, GLOBAL_dados_acomodacao, *GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 3:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}
