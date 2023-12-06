/////////////////////////////   Biblioteca  \\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include "biblioteca.h"

//Subrotinas


void listagemHospedes(cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente){
    FILE *arquivoBin, *arquivoTxt;
    cad_clie cliente;
    int i = 0, encontrado = 0, aux = 0;
    char linha[(sizeof (cad_clie))], *token;
    float codInicial, codFinal;

    printf("Digite o código inicial da faixa que deseja filtrar: ");
    scanf("%f", &codInicial);

    printf("Digite o código final da faixa que deseja filtrar: ");
    scanf("%f", &codFinal);

    arquivoBin = fopen("cliente.bin", "rb");
    arquivoTxt = fopen("cliente.txt", "r");
    
    //bin
    printf("\nDados salvos em .bin: \n");
    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.delet == 0) {
            if(cliente.codigo >= codInicial && cliente.codigo <= codFinal){
                encontrado = 1;
                printf("\nCódigo: %.0f\n\tNome: %s\n\tCPF: %.0f\n\tTelefone: %.0f\n\tEmail: %s\n\tSexo: %s\n\tEstado civil: %s\n\tNascimento: %s\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNumero: %.0f\n\tCEP: %.0f",
                    cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil,
                    cliente.nascimento, cliente.local.estado, cliente.local.cidade, cliente.local.bairro, cliente.local.rua,
                    cliente.local.numero, cliente.local.cep);
            }
        }
    }

    if(encontrado == 0)
        printf("\tNenhum cliente cadastrado!");
    else
        encontrado ==0;

    //txt
    printf("\nDados salvos em .txt: \n");
    while (fgets(linha, sizeof (cad_clie), arquivoTxt)) {
        // pega o primeiro dado (se o arquivo foi ou não excluido logicamente)
        token = strtok(linha, ";");
        cliente.delet = atoi(token);
        token = strtok(NULL, ";");
        cliente.codigo = atoff(token);
        // compara e caso o arquivo não tenha sido excluido ele mostra
        if (cliente.delet == 0) {
            if(cliente.codigo >= codInicial && cliente.codigo <= codFinal){
                encontrado = 1;
                printf("\nCódigo: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Nome: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("CPF: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Telefone: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Email: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Sexo: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Estado Civil: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Nascimento: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Estado: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("CEP: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Cidade: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Bairro: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Rua: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Número da casa: %s\n", token);
                token = strtok(NULL, ";");
            }
        }
    }
    fclose(arquivoBin);
    fclose(arquivoTxt);
    
    if(encontrado == 0)
        printf("\tNenhum cliente cadastrado!");
    else
        encontrado ==0;

    //memoria
    if (GLOBAL_dados_cliente != NULL) {
        printf("\nDados salvos em memória: \n");
        
        for (i = 1; i < GLOBAL_tam_pont_dados_cliente; i++) {
            if (GLOBAL_dados_cliente->delet == 0) {
                if(GLOBAL_dados_cliente->codigo >= codInicial && GLOBAL_dados_cliente->codigo <= codFinal){
                    encontrado = 1;
                    printf("\nCódigo: %.0f\n\tNome: %s\n\tCPF: %.0f\n\tTelefone: %.0f\n\tEmail: %s\n\tSexo: %s\n\tEstad civil: %s\n\tNascimento: %s\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNumero: %.0f\n\tCEP: %.0f\n",
                        GLOBAL_dados_cliente->codigo, GLOBAL_dados_cliente->nome, GLOBAL_dados_cliente->cpf, GLOBAL_dados_cliente->telefone, GLOBAL_dados_cliente->email, GLOBAL_dados_cliente->sexo, GLOBAL_dados_cliente->estado_civil, GLOBAL_dados_cliente->nascimento, 
                        GLOBAL_dados_cliente->local.estado, GLOBAL_dados_cliente->local.cidade, GLOBAL_dados_cliente->local.bairro, GLOBAL_dados_cliente->local.rua,GLOBAL_dados_cliente->local.numero, GLOBAL_dados_cliente->local.cep);
                }
            }

            //pula o ponteiro para a próxima posição;
            GLOBAL_dados_cliente += 1;
        }
    
        //retorna o ponteiro para a posição inicial do bloco que foi alocado
        GLOBAL_dados_cliente -= (i - 1);
        if(encontrado == 0)
            printf("\tNenhum cliente cadastrado nessa faixa!");
        else
            encontrado ==0;
    }

}

void listagemAcomodacoes(acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao){
    FILE *arquivo;
    char linha[(sizeof (acomodacao))], *token;
    int tam_poin = 0, encontrado = 0;
    acomodacao acomod;
    float codInicial, codFinal, codCate;

    printf("Digite o código inicial da faixa que deseja filtrar: ");
    scanf("%f", &codInicial);

    printf("Digite o código final da faixa que deseja filtrar: ");
    scanf("%f", &codFinal);

    printf("\nDigite o código da categoria que deseja pesquisar: ");
    scanf("%d", &codCate);

    arquivo = fopen("acomodacoes.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de acomodações!");
        exit(1);
    }

    //bin
    while (fread(&acomod, sizeof (acomodacao), 1, arquivo)) {
        if (acomod.delet == 0) {
            if(acomod.codigo >= codInicial && acomod.codigo <= codFinal && acomod.tipo.codigo == codCate){
                encontrado = 1;
                printf("\nCódigo quarto: %.0f\n\tDescrição: %s\n\tFacilidades: %s\n\tCódigo categria: %.0f",
                    acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo);
            }
        }
    }
    fclose(arquivo);

    //txt
    arquivo = fopen("acomodacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo txt!\n");
        exit(1);
    } else {
        while (fgets(linha, sizeof (acomodacao), arquivo)) {
            //separa o primeiro elemento que diz se foi excluido ou não
            token = strtok(linha, ";");
            acomod.delet = atoi(token);
            token = strtok(NULL, ";");
            acomod.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(acomod.descri, token);
            token = strtok(NULL, ";");
            strcpy(acomod.facilidades, token);
            token = strtok(NULL, ";");
            acomod.tipo.codigo = atoff(token);
            printf("Cod cate: %.0f", acomod.tipo.codigo);
            //caso não tenha sido excluido
            if (acomod.delet == 0) {
                if(acomod.codigo >= codInicial && acomod.codigo <= codFinal && acomod.tipo.codigo == codCate){
                    encontrado = 1;
                    printf("Código da acomodação: %.0f", acomod.codigo);
                    printf("Descrição: %s\n\t", acomod.descri);
                    printf("Facilidades: %s\n\t", acomod.facilidades);
                    printf("Código categoria: %.0f", acomod.tipo.codigo);
                }
            }
        }
    }

    fclose(arquivo);
    
    //memoria
    for (tam_poin = 1; tam_poin < GLOBAL_tam_pont_dados_acomodacao; tam_poin++) {
        if (GLOBAL_dados_acomodacao->delet == 0) {
            if(GLOBAL_dados_acomodacao->codigo >= codInicial && GLOBAL_dados_acomodacao->codigo <= codFinal && GLOBAL_dados_acomodacao->tipo.codigo == codCate){
                encontrado = 1;
                printf("Código da acomodação: %.0f", GLOBAL_dados_acomodacao->codigo);
                printf("Descrição: %s\n\t", GLOBAL_dados_acomodacao->descri);
                printf("Facilidades: %s\n\t", GLOBAL_dados_acomodacao->facilidades);
                printf("Código categoria: %.0f", GLOBAL_dados_acomodacao->tipo.codigo);
            }
        }
        
        GLOBAL_dados_acomodacao += 1;
    }
    
    //retorna o ponteiro para a posição inicial do bloco que foi alocado
    GLOBAL_dados_acomodacao -= (tam_poin - 1);

    if(encontrado == 0){
        printf("\nNenhuma acomodação cadastrada!");
    }
}

void listagemProdutos(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos){
    FILE *arquivo;
    produto dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (produto))], *token;
    float codInicial, codFinal, codCate;

    printf("Digite o código inicial da faixa que deseja filtrar: ");
    scanf("%f", &codInicial);

    printf("Digite o código final da faixa que deseja filtrar: ");
    scanf("%f", &codFinal);

    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    //bin
    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0) {
            if(dados.codigo >= codInicial && dados.codigo <= codFinal){
                encontrado = 1;
                printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                    dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            }
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
        dados.delet = atoi(token);
        token = strtok(NULL, ";");
        dados.codigo = atoff(token);

        if(dados.codigo >= codInicial && dados.codigo <= codFinal){
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

            printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
        }
    }

    fclose(arquivo);

    //memoria
    if (GLOBAL_dados_produtos != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_produtos; tam_point++) {
            if (GLOBAL_dados_produtos->delet == 0) {
                if(GLOBAL_dados_produtos->codigo >= codInicial && GLOBAL_dados_produtos->codigo <= codFinal){
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
    if(encontrado == 0){
        printf("\nNenhum produto cadastrado!");
    }
}

void listagemProdutosMin(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos){
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
            if(dados.estoque <= dados.estoque_min){
                encontrado = 1;
                printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                    dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            }
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
        dados.delet = atoi(token);
        token = strtok(NULL, ";");
        dados.codigo = atoff(token);
        token = strtok(NULL, ";");
        strcpy(dados.descricao, token);
        token = strtok(NULL, ";");
        dados.estoque_min = atoi(token);
        token = strtok(NULL, ";");
        dados.estoque = atoi(token);

        if(dados.estoque <= dados.estoque_min){
            encontrado = 1;
            token = strtok(NULL, ";");
            dados.custo = atoff(token);
            token = strtok(NULL, ";");
            dados.venda = atoff(token);

            printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: R$%.2f\n\tVenda: R$%.2f",
                dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
        }
    }

    fclose(arquivo);

    //memoria
    if (GLOBAL_dados_produtos != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_produtos; tam_point++) {
            if (GLOBAL_dados_produtos->delet == 0) {
                if(GLOBAL_dados_produtos->estoque <= GLOBAL_dados_produtos->estoque_min){
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
    if(encontrado == 0){
        printf("\nNenhum produto cadastrado!");
    }
}

void menuRelatorios(cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos){
    int opcao = 0;
    while (opcao != 5) {
        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tListagem de hóspedes - 1\n");
        printf("\tListagem de acomodações - 2\n");
        printf("\tListagem de produtos de consumo - 3\n");
        printf("\tProdutos em estoque mínimo - 4\n");
        printf("\tVoltar ao menu principal - 5\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listagemHospedes(GLOBAL_dados_cliente, GLOBAL_tam_pont_dados_cliente);
                break;
            case 2:
                listagemAcomodacoes(GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 3:
                listagemProdutos(GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
                break;
            case 4:
                listagemProdutosMin(GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
                break;
            case 5:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}