#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include <ctype.h>

itens le_valor_produto() {
    itens dados;
    
    setbuf(stdin, NULL);
    printf("\nDigite o ID do produto: \n");
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

contaHotel* menuTransacoes(int tipoArquivo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks, contaHotel *GLOBAL_dados_Contas, int *GLOBAL_tam_pont_dados_contas) {
    int opcao = 0;
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
                menuCaixa();    
                break;
            case 2:
                menuReceber(tipoArquivo);
                break;
            case 3:
                menuPagar(tipoArquivo);
                break;
            case 4:
                GLOBAL_dados_produtos = vendeProduto(tipoArquivo, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas, GLOBAL_dados_checkInOut, GLOBAL_tam_pont_dados_checks, GLOBAL_dados_Contas, GLOBAL_tam_pont_dados_contas);
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
    return GLOBAL_dados_Contas;
}

void entrada_produtos(int BinOuTxt, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    int quantia, i, j, aux = 0, nota, pagar;
    int stop1 = 0;
    float val_imposto = 0, val_frete = 0, valorTotal = 0;
    entrega_produto fornecimento;
    fornecedor dadosFornecedor;
    produto dadosProduto;
    itens *vetorProdutos;
    CaixaHotel dadosCaixaHotel;

    while (stop1 != 1) {
        fornecimento = le_entrega_produto();
        dadosFornecedor = check_fornecedor(fornecimento.cod_forn, GLOBAL_dados_fornecedores, GLOBAL_tam_pont_dados_fornecedores);

        if (dadosFornecedor.delet != 2) {
            printf("\nDigite a quantia de produtos entregues: ");
            scanf("%d", &quantia);
            fornecimento.qnt = quantia;
            valorTotal = valorTotal + fornecimento.frete + fornecimento.imposto;
            itens produtos[quantia];

            for (i = 0; i < quantia; i++) {
                produtos[i] = le_valor_produto();
                dadosProduto = check_produto(produtos[i].codigo, GLOBAL_dados_produtos, GLOBAL_tam_pont_dados_produtos);
                if (dadosProduto.delet != 2) {
                    aux += produtos[i].quantidade;
                    strcpy(produtos[i].descricao, dadosProduto.descricao);
                    vetorProdutos[i] = produtos[i];
                    valorTotal += (produtos[i].quantidade * produtos[i].valor);
                }
                else {
                    i--;
                }
            }

            val_frete = (fornecimento.frete / aux);
            val_imposto = (fornecimento.imposto / aux);

            for (i = 0; i < quantia; i++) {
                atualiza_estoque_produto(produtos[i].codigo, produtos[i].quantidade, val_frete, val_imposto, produtos[i].valor);
            }
            
            if(BinOuTxt == 0)
                salva_entrada_produto_bin(fornecimento, dadosFornecedor, produtos);
                else if(BinOuTxt == 1)
                    salva_entrada_produto_txt(fornecimento, dadosFornecedor, produtos);
                    //else
                        //salva_entrada_produto_mem();
        }
        else {
            printf("\nFornecedor não consta na base de dados!\n Favor cadastrá-lo! \n");
        }
        printf("Encerrar entrada de produtos? (1- Sim    2- Não): ");
        scanf("%d", &stop1);
    }

    printf("Deseja impimir nota fiscal?(1- Sim    2- Não): ");
    scanf("%d", &nota);

    while (nota != 1 && nota != 2){
        printf("Número inválido, digite 1 - Sim ou 2 - Não: ");
        scanf("%d", &nota);
    }
    
    if(nota == 1){
        printf("\n______________________________________________________________________________");
        printf("\n\n\t\t\t\tFORNECEDOR");
        printf("\n______________________________________________________________________________");
        printf("\nFornecedor\t %s", dadosFornecedor.nome);
        printf("\nCNPJ\t\t %s", dadosFornecedor.cnpj);
        printf("\nFrete\t\t R$%.2f\t\t\tImposto\t\t R$%.2f", fornecimento.frete, fornecimento.imposto);
        printf("\n______________________________________________________________________________");
        printf("\n\n\t\t\t\tPRODUTOS");
        printf("\n______________________________________________________________________________");
        printf("\n\n\tDescrição");
        printf("\tPreço Custo(R$)");
        printf("\tQuantidade(Unid)");
        printf("\tTotal(R$)");

        for (j = 0; j < quantia; j++){
            printf("\n %s\t\t\tR$%.2f\t\t%d\tR$%.2f", vetorProdutos[j].descricao, vetorProdutos[j].valor, vetorProdutos[j].quantidade, (vetorProdutos[j].valor * vetorProdutos[j].quantidade));
        }
        printf("\n______________________________________________________________________________");
        printf("\n\n\t\tTotal da nota (produtos + frete + impostos):\t R$%.2f", valorTotal);
        printf("\n\n______________________________________________________________________________");
    }

    //Pagamento
    printf("\nDeseja pagar a vista ou a prazo? (1 - a vista, 2 - a prazo): ");
    scanf("%d", &pagar);

    while (pagar != 1 && pagar != 2){
        printf("\nNúmero inválido! (1 - a vista, 2 - a prazo): ");
        scanf("%d", &pagar);
    }
    dadosCaixaHotel = verificaCaixa();
    if(pagar == 1){
        dadosCaixaHotel.valorEmCaixa -= valorTotal;
    } else {
        dadosCaixaHotel.contasAPagar += valorTotal;
    }
    adicionaCaixa(dadosCaixaHotel);
}

fornecedor check_fornecedor(float codigo, fornecedor *GLOBAL_dados_fornecedores, int GLOBAL_tam_pont_dados_fornecedores) {
    FILE *arquivo;
    fornecedor dados, retorna;
    int encontrado = 0, tam_point = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f\n",
                    dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone, dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
            encontrado = 1;
            retorna = dados;
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

        while (fgets(linha, sizeof (fornecedor), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                printf("\nCódigo: %s \n", token);
                token = strtok(NULL, ";");
                strcpy(dados.nome, token);
                printf("Nome: %s \n", token);
                token = strtok(NULL, ";");
                printf("Razão social: %s \n", token);
                token = strtok(NULL, ";");
                printf("Inscrição estadual: %s \n", token);
                token = strtok(NULL, ";");
                strcpy(dados.cnpj, token);
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
                retorna = dados;
                break;
            }
        }

        fclose(arquivo);
    }
    
    //memoria
    if (encontrado == 0) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_fornecedores; tam_point++) {
            if (GLOBAL_dados_fornecedores->delet == 0) {
                if (GLOBAL_dados_fornecedores->codigo == codigo) {
                    printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f\n",
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
        retorna.delet = 2;
    }
    else {
        return retorna;
    }
}

produto check_produto(float codigo, produto *GLOBAL_dados_produtos, int GLOBAL_tam_pont_dados_produtos) {
    FILE *arquivo;
    int encontrado = 0, tam_point = 0;
    produto dados, retorna;
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
                printf("Estoque mínimo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Estoque atual: %s \n", token);
                token = strtok(NULL, ";");
                printf("Custo do produto: R$%s \n", token);
                token = strtok(NULL, ";");
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
        printf("Produto não encontrado!\n Verifique o código e tente novamente!\n");
        retorna.delet = 2;
    }
    return retorna;
}

void atualiza_estoque_produto(float codigo, int quantia, float frete, float imposto, float custo) {
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
            break;
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
                dados.custo = custo;
                dados.estoque += quantia;
                dados.venda = valor_venda;
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
    /*
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
    */

    if (encontrado != 0) {
        printf("\nProdutos atualizados com sucesso!\n");
    }
}

void salva_entrada_produto_bin(entrega_produto fornecimento, fornecedor dadosFornecedor, itens *produtos) {
    FILE *bin;
    
    bin = fopen("entradaProdutos.bin", "ab");
    if (bin == NULL) {
        printf("Erro de abertura de arquivo entradaProdutos.bin!\n");
        exit(1);
    }
    
    fwrite(&fornecimento, sizeof(entrega_produto), 1, bin);
    fwrite(produtos, sizeof(itens), fornecimento.qnt, bin);
    
    fclose(bin);
}

void salva_entrada_produto_txt(entrega_produto fornecimento, fornecedor dadosFornecedor, itens *produtos) {
    FILE *txt;
    int i = 0;
    
    txt = fopen("entradaProdutos.txt", "a");
    if (txt == NULL) {
        printf("Erro de abertura de arquivo entradaProdutos.bin!\n");
        exit(1);
    }
    
    //escreve os dados do fornecedor
    fprintf(txt, "%0.0f;%s;%s;%0.2f;%0.2f;%d;\n", fornecimento.cod_forn, dadosFornecedor.nome, dadosFornecedor.cnpj, fornecimento.frete, fornecimento.imposto, fornecimento.qnt);
    //escreve os dados dos produtos
    for (i = 0; i < fornecimento.qnt; i++) {
        fprintf(txt, "%0.0f;%s;%0.2f;%d;\n", produtos[i].codigo,produtos[i].descricao, produtos[i].valor, produtos[i].quantidade);
    }

    fclose(txt);
}

void salva_entrada_produto_mem(entrega_produto fornecimento, entrega_produto ****GLOBAL_dados_entrega_produto, int *GLOBAL_tam_pont_dados_entrega_produto) {
    //caso a variavel global GLOBAL_dados_entrega_produto não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
    if (*GLOBAL_tam_pont_dados_entrega_produto == 1) {
        ***GLOBAL_dados_entrega_produto = malloc(sizeof(cad_clie));
        ****GLOBAL_dados_entrega_produto = fornecimento;
    }
    //caso a variavel GLOBAL_tam_pont_dados_entrega_produto tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
    //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
    else {
        ***GLOBAL_dados_entrega_produto = realloc(GLOBAL_dados_entrega_produto, (*GLOBAL_tam_pont_dados_entrega_produto)*sizeof(cad_clie));
        ****(GLOBAL_dados_entrega_produto + (*GLOBAL_tam_pont_dados_entrega_produto - 1)) = fornecimento;
    }
    
    //encerra o processo caso não haja memória o suficiente
    if (***GLOBAL_dados_entrega_produto == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    }
    
    //aumenta o valor da variavel global
    (*GLOBAL_tam_pont_dados_entrega_produto)++;
    
}

void salva_entrada_itens_mem(int quantia, itens *produtos, itens ****GLOBAL_dados_itens, int *GLOBAL_tam_pont_dados_itens) {
    int aux = 0;
    
    while(aux != quantia) {
        //caso a variavel global GLOBAL_dados_entrega_produto não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
        if (*GLOBAL_tam_pont_dados_itens == 1) {
            ***GLOBAL_dados_itens = malloc(sizeof(cad_clie));
            ****GLOBAL_dados_itens = produtos[aux];
        }
        //caso a variavel GLOBAL_tam_pont_dados_itens tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
        //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
        else {
            ***GLOBAL_dados_itens = realloc(GLOBAL_dados_itens, (*GLOBAL_tam_pont_dados_itens)*sizeof(cad_clie));
            ****(GLOBAL_dados_itens + (*GLOBAL_tam_pont_dados_itens - 1)) = produtos[aux];
        }

        //encerra o processo caso não haja memória o suficiente
        if (***GLOBAL_dados_itens == NULL) {
            printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
            exit(1);
        }

        //aumenta o valor da variavel global
        (*GLOBAL_tam_pont_dados_itens)++;
        
        aux++;
    }
}

void le_todas_entradas_produto(entrega_produto *GLOBAL_dados_entrega_produto, int GLOBAL_tam_pont_dados_entrega_produto, itens *GLOBAL_dados_itens, int GLOBAL_tam_pont_dados_itens) {
    FILE *arquivo;
    int i = 0, aux = 0;
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
        
        token1 = strtok(forn, ";");
        printf("Código do fornecedor: %s\n", token1);
        token1 = strtok(NULL, ";");
        printf("Frete: R$%s\n", token1);
        token1 = strtok(NULL, ";");
        printf("Imposto: R$%s\n", token1);
        token1 = strtok(NULL, ";");
        entrega.qnt = atoi(token1);
        printf("Quantia de produtos diferentes entregues: %s\n", token1);
        for (i = 0; i < entrega.qnt; i++) {
            //le o \n
            fgets(prod, sizeof(itens), arquivo);
            //le o resto
            fgets(prod, sizeof(itens), arquivo);
            token1 = strtok(prod, ";");
            printf("Código do produto: %s\n", token1);
            token1 = strtok(NULL, ";");
            printf("Valor do produto: R$ %s\n", token1);
            token1 = strtok(NULL, ";");
            printf("Quantia de produtos: %s\n", token1);
        }
        
        //le \n
        fgets(forn, sizeof(entrega_produto), arquivo);
    }
    
    fclose(arquivo); //fim txt
    
    //le memoria
    /*
        if (GLOBAL_dados_entrega_produto != NULL && GLOBAL_dados_itens != NULL) {
        for (i = 1; i < GLOBAL_tam_pont_dados_entrega_produto; i++) {
            printf("Código do fornecedor: %0.0f \nValor do frete: %0.2f \nValor do imposto: %0.2f \nQuantia de produtos diferentes entregues: %d\n", GLOBAL_dados_entrega_produto->cod_forn, GLOBAL_dados_entrega_produto->frete, GLOBAL_dados_entrega_produto->imposto, GLOBAL_dados_entrega_produto->qnt);
        
            aux = 0;
            
            //le os dados dos produtos entregues:
            while (aux != GLOBAL_dados_entrega_produto->qnt) {
                printf("Código do item: %0.0f \nValor do item: %0.2f \nQuantia de itens: %d\n", GLOBAL_dados_itens->codigo, GLOBAL_dados_itens->valor, GLOBAL_dados_itens->quantidade);

                aux++;
                //avança ponteiro uma posição
                GLOBAL_dados_itens++;
            }
            
            
            //avança ponteiro uma posição
            GLOBAL_dados_entrega_produto++;
        }
        
        //retorna ponteiro para a primeira posição
        GLOBAL_dados_entrega_produto -= (i - 1);
        GLOBAL_dados_itens -= (aux);
    }
    */
}

void menuCaixa(){
    int opcao = 0;
    while (opcao != 3) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tValor no caixa - 1\n");
        printf("\tListar vendas - 2\n");

        printf("\tVoltar ao menu principal - 3\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                le_ValorEmCaixa();
                break;
            case 2:
                le_transações();
                break;
            case 3:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}

void le_ValorEmCaixa(){
    FILE *arquivo;
    CaixaHotel dados;

    arquivo = fopen("caixa.bin", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de caixa!");
        exit(1);
    }

    fread(&dados, sizeof(CaixaHotel), 1, arquivo);
    printf("\nSaldo atual: %.2f", dados.valorEmCaixa);

    fclose(arquivo);
}

void le_transações(){
    FILE *arquivo;
    contaHotel dados;   
    char tipo[50], pago[10];
    arquivo = fopen("contas.bin", "rb");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de caixa!");
        exit(1);
    }
    printf("\n|Tipo de pagamento || Vencimento || Pago ||  Valor  |\n");
    while (fread(&dados, sizeof(contaHotel), 1, arquivo)){
        //Verifica o tipo de pagamento
        if(dados.tipo == 0)
            strcpy(tipo, "Dinheiro");
            else if(dados.tipo == 1)
                strcpy(tipo, "Débito");
                else if(dados.tipo == 2)
                    strcpy(tipo, "Crédito");
                    else
                        strcpy(tipo, "Montante cartao");
        //Verifica se já foi pago ou não
        if(dados.delet == 0)
            strcpy(pago, "Não");
            else
                strcpy(pago, "Sim");
        
        printf("\n|     %s            %d         %s     %.2f  |", tipo, dados.DiaVencimento, pago, dados.valor);
    }
    
    fclose(arquivo);

    arquivo = fopen("contas.txt", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de caixa!");
        exit(1);
    }
    
    char linha[sizeof(contaHotel)], *token;
    while (fgets(linha, sizeof(contaHotel), arquivo)){
        token = strtok(linha, ";");
        dados.delet = atoi(token);
        token = strtok(NULL, ";");
        dados.tipo = atoi(token);
        token = strtok(NULL, ";");
        dados.DiaVencimento = atoi(token);
        token = strtok(NULL, ";");
        dados.valor = atoff(token);

        //Verifica o tipo de pagamento
        if(dados.tipo == 0)
            strcpy(tipo, "Dinheiro");
            else if(dados.tipo == 1)
                strcpy(tipo, "Débito");
                else if(dados.tipo == 2)
                    strcpy(tipo, "Crédito");
                    else
                        strcpy(tipo, "Montante cartao");

        //Verifica se já foi pago ou não
        if(dados.delet == 0)
            strcpy(pago, "Não");
            else
                strcpy(pago, "Sim");
        
        printf("\n|     %s            %d         %s     %.2f  |", tipo, dados.DiaVencimento, pago, dados.valor);
    }
    fclose(arquivo);
}

void le_ValorContasAReceber(){
    FILE *arquivo;
    CaixaHotel dados;

    arquivo = fopen("caixa.bin", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de caixa!");
        exit(1);
    }

    fread(&dados, sizeof(CaixaHotel), 1, arquivo);
    printf("\nContas a receber: %.2f", dados.contasAReceber);

    fclose(arquivo);
}

void salvaMontante_Bin(montanteBanco dados){
    FILE *arquivo;

    arquivo = fopen("montantesBanco.bin","ab");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de montantes!");
        exit(1);
    }

    fwrite(&dados, sizeof(montanteBanco), 1, arquivo);
    fclose(arquivo);
}

void salvaMontante_Txt(montanteBanco dados){
    FILE *arquivo;
    int teste;
    arquivo = fopen("montantesBanco.txt","a");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de montantes!");
        exit(1);
    }

    teste = fprintf(arquivo, "%.2f;%d;%d;%d\n", dados.valor, dados.dataDados.dia, dados.dataDados.mes, dados.dataDados.ano);
    if(teste < 0){
        printf("\nErro ao adicionar montante!");
    }
    fclose(arquivo);
}

void darBaixaContasAReceber(int BinOuTxt){
    CaixaHotel dados;
    montanteBanco dadosMontante;

    float valor;
    data dataDados;
    

    printf("Digite o valor que deseja dar baixa: ");
    scanf("%f", &valor);
    dataDados = le_dados_data();
    
    dados = verificaCaixa();

    dados.valorEmCaixa += valor;
    dados.contasAReceber -= valor;

    //Salva nos três tipos de memória[
    adicionaCaixa(dados);

    dadosMontante.valor = valor;
    dadosMontante.dataDados = dataDados;

    if(BinOuTxt == 0)
                salvaMontante_Bin(dadosMontante);
                else if(BinOuTxt == 1)
                    salvaMontante_Txt(dadosMontante);
    
    printf("\nBaixa dada com sucesso!");
}

void lerBaixasAReceber(){
    FILE *arquivo;
    montanteBanco dados;

    arquivo = fopen("montantesBanco.bin","rb");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de montantes!");
        exit(1);
    }

    while (fread(&dados,sizeof(montanteBanco), 1, arquivo)){
        if(dados.valor > 0)
            printf("\nValor: %.2f\tData: %d/%d/%d", dados.valor, dados.dataDados.dia, dados.dataDados.mes, dados.dataDados.ano);
    }
    
    fclose(arquivo);

    arquivo = fopen("montantesBanco.txt","r");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de montantes!");
        exit(1);
    }
    
    char linha[sizeof(montanteBanco)], *token;

    while (fgets(linha, sizeof(montanteBanco), arquivo)){
        token = strtok(linha, ";");
        dados.valor = atoff(token);
        token = strtok(NULL, ";");
        dados.dataDados.dia = atoi(token);
        token = strtok(NULL, ";");
        dados.dataDados.mes = atoi(token);
        token = strtok(NULL, ";");
        dados.dataDados.ano = atoi(token);

        if(dados.valor > 0)
            printf("\nValor: %.2f\tData: %d/%d/%d", dados.valor, dados.dataDados.dia, dados.dataDados.mes, dados.dataDados.ano);
    }
    
    fclose(arquivo);
}

void menuReceber(int BinOuTxt){
    int opcao = 0;
    while (opcao != 4) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tValor de contas a Receber - 1\n");
        printf("\tDar baixa - 2\n");
        printf("\tLer últimas baixas - 3\n");
        printf("\tVoltar ao menu principal - 4\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                le_ValorContasAReceber();
                break;
            case 2:
                darBaixaContasAReceber(BinOuTxt);
                break;
            case 3:
                lerBaixasAReceber();
                break;
            case 4:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}

void le_ValorContasApagar(){
    FILE *arquivo;
    CaixaHotel dados;

    arquivo = fopen("caixa.bin", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivos de caixa!");
        exit(1);
    }

    fread(&dados, sizeof(CaixaHotel), 1, arquivo);
    printf("\nContas a pagar: %.2f", dados.contasAPagar);

    fclose(arquivo);
}

void darBaixaContasApagar(int BinOuTxt){
    CaixaHotel dados;
    montanteBanco dadosMontante;

    float valor;
    data dataDados;
    

    printf("Digite o valor que deseja dar baixa: ");
    scanf("%f", &valor);
    dataDados = le_dados_data();
    
    dados = verificaCaixa();

    dados.valorEmCaixa -= valor;
    dados.contasAPagar -= valor;

    //Salva nos três tipos de memória[
    adicionaCaixa(dados);

    dadosMontante.valor = valor * (-1);
    dadosMontante.dataDados = dataDados;

    if(BinOuTxt == 0)
                salvaMontante_Bin(dadosMontante);
                else if(BinOuTxt == 1)
                    salvaMontante_Txt(dadosMontante);
    
    printf("\nBaixa dada com sucesso!");
}

void lerBaixasAPagar(){
    FILE *arquivo;
    montanteBanco dados;

    arquivo = fopen("montantesBanco.bin","rb");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de montantes!");
        exit(1);
    }

    while (fread(&dados,sizeof(montanteBanco), 1, arquivo)){
        if(dados.valor < 0)
            printf("\nValor: %.2f\tData: %d/%d/%d", dados.valor * -1, dados.dataDados.dia, dados.dataDados.mes, dados.dataDados.ano);
    }
    
    fclose(arquivo);

    arquivo = fopen("montantesBanco.txt","r");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de montantes!");
        exit(1);
    }
    
    char linha[sizeof(montanteBanco)], *token;

    while (fgets(linha, sizeof(montanteBanco), arquivo)){
        token = strtok(linha, ";");
        dados.valor = atoff(token);
        token = strtok(NULL, ";");
        dados.dataDados.dia = atoi(token);
        token = strtok(NULL, ";");
        dados.dataDados.mes = atoi(token);
        token = strtok(NULL, ";");
        dados.dataDados.ano = atoi(token);

        if(dados.valor < 0)
            printf("\nValor: %.2f\tData: %d/%d/%d", dados.valor * -1, dados.dataDados.dia, dados.dataDados.mes, dados.dataDados.ano);
    }
    
    fclose(arquivo);
}

void menuPagar(int BinOuTxt){
    int opcao = 0;
    while (opcao != 4) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tValor de contas a Pagar - 1\n");
        printf("\tDar baixa - 2\n");
        printf("\tLer últimas baixas - 3\n");
        printf("\tVoltar ao menu principal - 4\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                le_ValorContasApagar();
                break;
            case 2:
                darBaixaContasApagar(BinOuTxt);
                break;
            case 3:
                lerBaixasAPagar();
                break;
            case 4:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}


