/////////////////////////////   Biblioteca  \\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include "biblioteca.h"

//Subrotinas

void criaCSV_cliente(cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente) {
    FILE *arquivoBin, *arquivoTxt, *CSV;
    cad_clie cliente;
    int i = 0;
    char linha[(sizeof (cad_clie))], *token;

    arquivoBin = fopen("cliente.bin", "rb");
    if (arquivoBin == NULL) {
        printf("Erro ao abrir cliente.bin\n");
        exit(1);
    }
    arquivoTxt = fopen("cliente.txt", "r");
    if (arquivoTxt == NULL) {
        printf("Erro ao abrir cliente.txt\n");
        exit(1);
    }
    CSV = fopen("dadosExportados/export_cliente.csv", "w");
    if (CSV == NULL) {
        printf("Erro ao abrir/criar CSV de cliente\n");
        exit(1);
    }
    
    //bin
    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.delet == 0) {
            //  !!! para export n printa o delet e n printa os clientes excluidos !!!
            fprintf(CSV, "%0.0f,%s,%0.0f,%0.0f,%s,%s,%s,%s,", cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
            fprintf(CSV, "%s,%0.0f,%s,%s,%s,%0.0f\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
        }
    }

    //txt
    while (fgets(linha, sizeof (cad_clie), arquivoTxt)) {
        // pega o primeiro dado (se o arquivo foi ou não excluido logicamente)
        token = strtok(linha, ";");

        // compara e caso o arquivo não tenha sido excluido ele mostra
        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
            cliente.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(cliente.nome, token);
            token = strtok(NULL, ";");
            cliente.cpf = atoff(token);
            token = strtok(NULL, ";");
            cliente.telefone = atoff(token);
            token = strtok(NULL, ";");
            strcpy(cliente.email, token);
            token = strtok(NULL, ";");
            strcpy(cliente.sexo, token);
            token = strtok(NULL, ";");
            strcpy(cliente.estado_civil, token);
            token = strtok(NULL, ";");
            strcpy(cliente.nascimento, token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.estado, token);
            token = strtok(NULL, ";");
            cliente.local.cep = atoff(token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.cidade, token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.bairro, token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.rua, token);
            token = strtok(NULL, ";");
            cliente.local.numero = atoff(token);
            
            //  !!! para export n printa o delet e n printa os clientes excluidos !!!
            fprintf(CSV, "%0.0f,%s,%0.0f,%0.0f,%s,%s,%s,%s,", cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
            fprintf(CSV, "%s,%0.0f,%s,%s,%s,%0.0f\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
        }
    }
    fclose(arquivoBin);
    fclose(arquivoTxt);

    //memoria
    if (GLOBAL_dados_cliente != NULL) {
        
        for (i = 1; i < GLOBAL_tam_pont_dados_cliente; i++) {
            if (GLOBAL_dados_cliente->delet == 0) {
                fprintf(CSV, "%0.0f,%s,%0.0f,%0.0f,%s,%s,%s,%s,", GLOBAL_dados_cliente->codigo, GLOBAL_dados_cliente->nome, GLOBAL_dados_cliente->cpf, GLOBAL_dados_cliente->telefone, GLOBAL_dados_cliente->email, GLOBAL_dados_cliente->sexo, GLOBAL_dados_cliente->estado_civil, GLOBAL_dados_cliente->nascimento);
                fprintf(CSV, "%s,%0.0f,%s,%s,%s,%0.0f\n", GLOBAL_dados_cliente->local.estado, GLOBAL_dados_cliente->local.cep, GLOBAL_dados_cliente->local.cidade, GLOBAL_dados_cliente->local.bairro, GLOBAL_dados_cliente->local.rua, GLOBAL_dados_cliente->local.numero);
            }

            //pula o ponteiro para a próxima posição;
            GLOBAL_dados_cliente += 1;
        }
    
        //retorna o ponteiro para a posição inicial do bloco que foi alocado
        GLOBAL_dados_cliente -= (i - 1);
    }
    
    fclose(CSV);
}

void criaCSV_reserva(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *txt, *bin, *CSV;
    reserva dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof(reserva))], *token;
    
    bin = fopen("reservas.bin", "rb");
    if (bin == NULL) {
        printf("Erro de leitura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    CSV = fopen("dadosExportados/export_reservas.csv", "w");
    if (CSV == NULL) {
        printf("Erro ao abrir/criar CSV de reservas\n");
        exit(1);
    }
    
    while(fread(&dados, sizeof(reserva), 1, bin)) {
        if (dados.delet == 0) {
            fprintf(CSV, "%0.0f,%0.0f,%d/%d/%d,%d/%d/%d\n", dados.codigo, dados.codQuarto, dados.inicio.dia, dados.inicio.mes, dados.inicio.ano, dados.fim.dia, dados.fim.mes, dados.fim.ano);
        }
    }
    
    fclose(bin);
    
    txt = fopen("reservas.txt", "r");
    if (txt == NULL) {
        printf("Erro de leitura de arquivo reservas.txt!\n");
        exit(1);
    }
    
    while(fgets(linha, sizeof(reserva), txt)) {
        token = strtok(linha, ";");
        
        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            dados.codQuarto = atoff(token);
            token = strtok(NULL, ";");
            dados.inicio.dia = atoi(token);
            token = strtok(NULL, ";");
            dados.inicio.mes = atoi(token);
            token = strtok(NULL, ";");
            dados.inicio.ano = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.dia = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.mes = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.ano = atoi(token);
            
            fprintf(CSV, "%0.0f,%0.0f,%d/%d/%d,%d/%d/%d\n", dados.codigo, dados.codQuarto, dados.inicio.dia, dados.inicio.mes, dados.inicio.ano, dados.fim.dia, dados.fim.mes, dados.fim.ano);
        }
    }
    
    fclose(txt);
    
    //memoria
    if (GLOBAL_dados_reservas != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_reservas; tam_point++) {
            if (GLOBAL_dados_reservas->delet == 0) {
                fprintf(CSV, "%0.0f,%0.0f,%d/%d/%d,%d/%d/%d\n", GLOBAL_dados_reservas->codigo, GLOBAL_dados_reservas->codQuarto, GLOBAL_dados_reservas->inicio.dia, GLOBAL_dados_reservas->inicio.mes, GLOBAL_dados_reservas->inicio.ano, GLOBAL_dados_reservas->fim.dia, GLOBAL_dados_reservas->fim.mes, GLOBAL_dados_reservas->fim.ano);
            }
            
            GLOBAL_dados_reservas++;
        }
        
        GLOBAL_dados_reservas -= (tam_point - 1);
    }
    
    fclose(CSV);
}

void criaCSV_operador(operador *GLOBAL_dados_operadores, int GLOBAL_tam_pont_dados_operadores) {
    FILE *arquivo, *CSV;
    operador dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (operador))], *token;

    arquivo = fopen("operadores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadoreses!");
        exit(1);
    }

    CSV = fopen("dadosExportados/export_operador.csv", "w");
    if (CSV == NULL) {
        printf("Erro ao abrir/criar CSV de operadores\n");
        exit(1);
    }
    
    while (fread(&dados, sizeof (operador), 1, arquivo)) {
        if (dados.delet == 0) {
            fprintf(CSV, "%0.0f,%d,%s,%s,%s\n", dados.codigo, dados.acesso, dados.nome, dados.user, dados.senha);
        }
    }

    fclose(arquivo);

    arquivo = fopen("operadores.txt", "r");
    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadores.txt!");
        exit(1);
    }

    while (fgets(linha, sizeof (operador), arquivo)) {
        token = strtok(linha, ";");
        dados.delet = atoi(token);
        if (dados.delet == 0) {
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            dados.acesso = atoi(token);
            token = strtok(NULL, ";");
            strcpy(dados.nome, token);
            token = strtok(NULL, ";");
            strcpy(dados.user, token);
            token = strtok(NULL, ";");
            strcpy(dados.senha, token);
            
            fprintf(CSV, "%0.0f,%d,%s,%s,%s\n", dados.codigo, dados.acesso, dados.nome, dados.user, dados.senha);
        }
    }

    fclose(arquivo);
    
    //memoria
    if (GLOBAL_dados_operadores != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_operadores; tam_point++) {
            if (GLOBAL_dados_operadores->delet == 0) {
                fprintf(CSV, "%0.0f,%d,%s,%s,%s\n", GLOBAL_dados_operadores->codigo, GLOBAL_dados_operadores->acesso, GLOBAL_dados_operadores->nome, GLOBAL_dados_operadores->user, GLOBAL_dados_operadores->senha);
            }
            
            //avança 1 posição
            GLOBAL_dados_operadores++;
        }
        
        //retorna o ponteiro para a primeira posição
        GLOBAL_dados_operadores -= (tam_point -1);
    }
    if(encontrado == 0){
        printf("\nNenhum operador cadastrado!");
    }
    
    fclose(CSV);
}

void criaCSV_acomodacao(acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao) {
    FILE *arquivo, *CSV;
    char linha[(sizeof (acomodacao))], *token;
    float codigo;
    int tam_poin = 0, encontrado = 0, i = 0;
    acomodacao acomod;
    char auxiliar[(sizeof(acomod.facilidades))];

    arquivo = fopen("acomodacoes.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de acomodações!");
        exit(1);
    }

    CSV = fopen("dadosExportados/export_acomodacoes.csv", "w");
    if (CSV == NULL) {
        printf("Erro ao abrir/criar CSV de acomodações\n");
        exit(1);
    }
    
    //bin
    while (fread(&acomod, sizeof (acomodacao), 1, arquivo)) {
        if (acomod.delet == 0) {
            //retira possiveis separadores , para n bugar csv!
            for (i = 0; i < strlen(acomod.facilidades); i++) {
                if (acomod.facilidades[i] == ',') {
                    //troca , por ;
                    acomod.facilidades[i] = ';';
                }
            }
            
            fprintf(CSV, "%0.0f,%s,%s,%d,%0.0f,%s,%0.2f,%d\n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.delet, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.diaria, acomod.tipo.qnt_pessoas);
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
            //caso não tenha sido excluido
            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                acomod.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomod.descri, token);
                token = strtok(NULL, ";");
                strcpy(acomod.facilidades, token);
                token = strtok(NULL, ";");
                //pula o delet
                token = strtok(NULL, ";");
                acomod.tipo.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomod.tipo.descri, token);
                token = strtok(NULL, ";");
                acomod.tipo.diaria = atoff(token);
                token = strtok(NULL, ";");
                acomod.tipo.diaria = atoff(token);
                
                //retira possiveis separadores , para n bugar csv!
                for (i = 0; i < strlen(acomod.facilidades); i++) {
                    if (acomod.facilidades[i] == ',') {
                        //troca , por ;
                        acomod.facilidades[i] = ';';
                    }
                }

                fprintf(CSV, "%0.0f,%s,%s,%d,%0.0f,%s,%0.2f,%d\n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.delet, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.diaria, acomod.tipo.qnt_pessoas);
            }
        }
    }

    fclose(arquivo);
    
    //memoria
    for (tam_poin = 1; tam_poin < GLOBAL_tam_pont_dados_acomodacao; tam_poin++) {
        if (GLOBAL_dados_acomodacao->delet == 0) {
            //retira possiveis separadores , para n bugar csv!
                for (i = 0; i < strlen(GLOBAL_dados_acomodacao->facilidades); i++) {
                    if (GLOBAL_dados_acomodacao->facilidades[i] == ',') {
                        //troca , por ;
                        GLOBAL_dados_acomodacao->facilidades[i] = ';';
                    }
                }

                fprintf(CSV, "%0.0f,%s,%s,%d,%0.0f,%s,%0.2f,%d\n", GLOBAL_dados_acomodacao->codigo, GLOBAL_dados_acomodacao->descri, GLOBAL_dados_acomodacao->facilidades, GLOBAL_dados_acomodacao->tipo.delet, GLOBAL_dados_acomodacao->tipo.codigo, GLOBAL_dados_acomodacao->tipo.descri, GLOBAL_dados_acomodacao->tipo.diaria, GLOBAL_dados_acomodacao->tipo.qnt_pessoas);
        }
        
        GLOBAL_dados_acomodacao += 1;
    }
    
    //retorna o ponteiro para a posição inicial do bloco que foi alocado
    GLOBAL_dados_acomodacao -= (tam_poin - 1);
    
    fclose(CSV);
}

void criaCSV_fornecedor(fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores) {
    FILE *arquivo, *CSV;
    fornecedor dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }
    
    CSV = fopen("dadosExportados/export_fornecedor.csv", "w");
    if (CSV == NULL) {
        printf("Erro ao abrir/criar CSV de acomodações\n");
        exit(1);
    }

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0) {
            fprintf(CSV, "%0.0f,%s,%s,%s,%s,%s,%0.0f,", dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
            fprintf(CSV, "%s,%0.0f,%s,%s,%s,%0.0f\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
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
            
            fprintf(CSV, "%0.0f,%s,%s,%s,%s,%s,%0.0f,", dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
            fprintf(CSV, "%s,%0.0f,%s,%s,%s,%0.0f\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
        }
    }

    fclose(arquivo);
    
    //memoria
    for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_fornecedores; tam_point++) {
        if (GLOBAL_dados_fornecedores->delet == 0) {
            fprintf(CSV, "%0.0f,%s,%s,%s,%s,%s,%0.0f,", GLOBAL_dados_fornecedores->codigo, GLOBAL_dados_fornecedores->nome, GLOBAL_dados_fornecedores->raz_soci, GLOBAL_dados_fornecedores->inscri_estad, GLOBAL_dados_fornecedores->cnpj, GLOBAL_dados_fornecedores->email, GLOBAL_dados_fornecedores->telefone);
            fprintf(CSV, "%s,%0.0f,%s,%s,%s,%0.0f\n", GLOBAL_dados_fornecedores->local.estado, GLOBAL_dados_fornecedores->local.cep, GLOBAL_dados_fornecedores->local.cidade, GLOBAL_dados_fornecedores->local.bairro, GLOBAL_dados_fornecedores->local.rua, GLOBAL_dados_fornecedores->local.numero);
        }
        
        //avança o ponteiro uma posição
        GLOBAL_dados_fornecedores++;
    }
    
    //retorna o ponteiro para a primeira posição
    GLOBAL_dados_fornecedores -= (tam_point - 1);
    
    fclose(CSV);
}

void criaCSV_produto(produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    FILE *arquivo, *CSV;
    produto dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    CSV = fopen("dadosExportados/export_produtos.csv", "w");
    if (CSV == NULL) {
        printf("Erro ao abrir/criar CSV de produtos\n");
        exit(1);
    }
    
    //bin
    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0) {
            fprintf(CSV, "%0.0f,%s,%d,%d,%0.2f,%0.2f\n", dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
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
            
            fprintf(CSV, "%0.0f,%s,%d,%d,%0.2f,%0.2f\n", dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
        }
    }

    fclose(arquivo);

    //memoria
    if (GLOBAL_dados_produtos != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_produtos; tam_point++) {
            if (GLOBAL_dados_produtos->delet == 0) {
                fprintf(CSV, "%0.0f,%s,%d,%d,%0.2f,%0.2f\n", GLOBAL_dados_produtos->codigo, GLOBAL_dados_produtos->descricao, GLOBAL_dados_produtos->estoque_min, GLOBAL_dados_produtos->estoque, GLOBAL_dados_produtos->custo, GLOBAL_dados_produtos->venda);
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
    
    fclose(CSV);
}

void criaCSV_categoria_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *ler, *CSV;
    cate_aco acomodacao;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (cate_aco))], *token;

    ler = fopen("categoria_acomo.bin", "rb");

    if (ler == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }
    
    CSV = fopen("dadosExportados/export_categ_acomodacoes.csv", "w");
    if (CSV == NULL) {
        printf("Erro ao abrir/criar CSV de acomodações\n");
        exit(1);
    }

    //bin
    while (fread(&acomodacao, sizeof (cate_aco), 1, ler)) {
        if (acomodacao.delet == 0) {
            fprintf(CSV, "%0.0f,%s,%0.2f,%d\n", acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
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
            acomodacao.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(acomodacao.descri, token);
            token = strtok(NULL, ";");
            acomodacao.diaria = atoff(token);
            token = strtok(NULL, ";");
            acomodacao.qnt_pessoas = atoi(token);
        }
        
        fprintf(CSV, "%0.0f,%s,%0.2f,%d\n", acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
    }

    fclose(ler);
    
    //memoria
    for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_categ_acomodacao; tam_point++) {
        if (GLOBAL_dados_categ_acomodacao->delet == 0) {
            fprintf(CSV, "%0.0f,%s,%0.2f,%d\n", GLOBAL_dados_categ_acomodacao->codigo, GLOBAL_dados_categ_acomodacao->descri, GLOBAL_dados_categ_acomodacao->diaria, GLOBAL_dados_categ_acomodacao->qnt_pessoas);
        }
        
        GLOBAL_dados_categ_acomodacao++;
    }
    
    GLOBAL_dados_categ_acomodacao -= (tam_point - 1);
    
    fclose(CSV);
}

void menuExportacao(int BinOuTxt, cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos, operador *GLOBAL_dados_operadores, int GLOBAL_tam_pont_dados_operadores, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores){
    int opcao = 0;
    while (opcao != 8) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tHóspedes - 1\n");
        printf("\tAcomodações - 2\n");
        printf("\tCategoria acomodação - 3\n");
        printf("\tReservas - 4\n");
        printf("\tProdutos - 5\n");
        printf("\tOperadores - 6\n");
        printf("\tFornecedores - 7\n");
        printf("\tVoltar ao menu principal - 8\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criaCSV_cliente(GLOBAL_dados_cliente, GLOBAL_tam_pont_dados_cliente);
                break;
            case 2:
                criaCSV_acomodacao(GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 3:
                criaCSV_categoria_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
                break;
            case 4:
                criaCSV_reserva(GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas);
                break;
            case 5:
                criaCSV_produto(GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
                break;
            case 6:
                criaCSV_operador(GLOBAL_dados_operadores, GLOBAL_tam_pont_dados_operadores);
                break;
            case 7:
                criaCSV_fornecedor(GLOBAL_dados_fornecedores, GLOBAL_tam_pont_dados_fornecedores);
                break;
            case 8:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}