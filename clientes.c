#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/////////////////////////////   subrotinas  \\\\\\\\\\\\\\\\\\\

int tam_clientes() {
    int tamanho = 0;

    tamanho = sizeof (cad_clie) - sizeof (float);

    return tamanho;
}

cad_clie le_dados_cad() {
    char bin[30] = "cliente.bin", txt[30] = "cliente.txt";
    int tam = sizeof(cad_clie);

    cad_clie dados;

    dados.delet = 0;

    dados.codigo = retorna_id(txt, bin, tam);

    setbuf(stdin, NULL);

    printf("\nDigite o seu nome completo: ");

    scanf("%[a-z A-Z][^\n]s", dados.nome);

    setbuf(stdin, NULL);

    /*

    printf("Digite o seu cpf: \n");

    scanf("%f", &dados.cpf);

    setbuf(stdin, NULL);

    
    printf("Digite seu estado: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.estado);

    setbuf(stdin, NULL); 
    
    printf("Digite sua cidade: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.cidade);

    setbuf(stdin, NULL);

    printf("Digite seu bairro: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.bairro);

    setbuf(stdin, NULL);

    printf("Digite sua rua: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.rua);

    setbuf(stdin, NULL);

    printf("Digite o número de sua casa: \n");

    scanf("%f", &dados.local.numero);

    setbuf(stdin, NULL);



    printf("Digite seu cpf: \n");

    scanf("%f", &dados.cpf);

    setbuf(stdin, NULL);

    printf("Digite seu telefone: \n");

    scanf("%f", &dados.telefone);

    setbuf(stdin, NULL);

    printf("Digite seu email: \n");

    scanf("%[^\n]s", dados.email);

    setbuf(stdin, NULL);

    printf("Digite seu sexo: \n");

    scanf("%[a-z A-Z][^\n]s", dados.sexo);

    setbuf(stdin, NULL);

    printf("Digite seu estado civil: \n");

    scanf("%[a-z A-Z][^\n]s", dados.estado_civil);

    setbuf(stdin, NULL);

    printf("Digite sua data de nascimento: \n");

    scanf("%[0-9/-][^\n]s", &dados.nascimento);

    setbuf(stdin, NULL);
     */
    return dados;
}

void menuCliente(int tipoArquivo) {
    int opcao = 0;
    cad_clie dados;
    while (opcao != 6) {
        setbuf(stdin, NULL);
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de cliente - 1\n");
        printf("\tListar todos os cliente - 2\n");
        printf("\tLista dados de um cliente - 3\n");
        printf("\tAlterar dados cliente - 4\n");
        printf("\tExcluir dados de cliente - 5\n");
        printf("\tVoltar ao menu inicial - 6\n");

        printf("Opc�o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_cad();
                if (tipoArquivo == 0) {
                    salva_cadastro_pessoa_bin(dados);
                } else {
                    salva_cadastro_pessoa_txt(dados);
                }
                break;
            case 2:
                le_todos_cadastro_pessoa();
                break;
            case 3:
                le_cadastro_pessoa();
                break;
            case 4:
                alteraCliente();
                break;
            case 5:
                removeCliente();
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPRESSIONE QUALQUER TECLA PARA CONTINUAR...");
        getchar();
    }
}

//  Clientes

void salva_cadastro_pessoa_bin(cad_clie saves) {

    FILE *salva;
    //      abrir arquivo
    salva = fopen("cliente.bin", "ab");

    if (salva == NULL) {
        printf("\n\t!! Erro de salvamento de Cadastro !! \n");
        return;
    }

    //      Escrever no arquivo
    fwrite(&saves, sizeof (cad_clie), 1, salva);

    printf("\nCadastro realizado com sucesso!\n\n");
    fclose(salva);
}

void salva_cadastro_pessoa_txt(cad_clie saves) {

    FILE *salva;

    int end, pessoa;

    //      abrir arquivo

    salva = fopen("cliente.txt", "a");

    if (salva == NULL) {

        printf("\n\t!! Erro de salvamento de Cadasto !! \n");

        exit(1);
    }

    //      Escrever no arquivo

    pessoa = fprintf(salva, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", saves.delet, saves.codigo, saves.nome, saves.cpf, saves.telefone, saves.email, saves.sexo, saves.estado_civil, saves.nascimento);

    if (pessoa < 0) {

        printf("!! Erro em salvar os dados !!\n");

        exit(1);
    } else {
        printf("Dados do cliente salvos com sucesso! \n");
    }

    //      Endereço

    end = fprintf(salva, "%s;%0.0f;%s;%s;%s;%0.0f;\n", saves.local.estado, saves.local.cep, saves.local.cidade, saves.local.bairro, saves.local.rua, saves.local.numero);

    if (end < 0) {

        printf("!! Erro em salvar o endereço !!\n");

        exit(1);
    } else {
        printf("Dados do endereço salvos com sucesso! \n");
    }

    //      Fechar arquivo
    fclose(salva);
}

void le_cadastro_pessoa() {
    //      Variáveis
    FILE *arquivoBin, *arquivoTxt;
    cad_clie cliente;

    float codigo;
    int encontrado = 0;

    printf("Digite o codigo do cliente que deseja ler: ");
    scanf("%f", &codigo);

    //      abrir arquivo
    arquivoBin = fopen("cliente.bin", "rb");
    arquivoTxt = fopen("cliente.txt", "r");

    if (arquivoBin == NULL || arquivoTxt == NULL) {
        printf("\n\t!! Erro de leitura do Cadastro !! \n");
        exit(1);
    }

    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.codigo == codigo && cliente.delet == 0) {
            encontrado = 1;
            printf("\nCódigo: %.0f\n\tNome: %s\n\tCPF: %.0f\n\tTelefone: %.0f\n\tEmail: %s\n\tSexo: %s\n\tEstad civil: %s\n\tNascimento: %s\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNumero: %.0f\n\tCEP: %.0f",
                    cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil,
                    cliente.nascimento, cliente.local.estado, cliente.local.cidade, cliente.local.bairro, cliente.local.rua,
                    cliente.local.numero, cliente.local.cep);
            break;
        }
    }
    if (encontrado == 0) {

        char linha[(sizeof (cad_clie))], *token, cod[10];
        //Passa o cod de float para string
        sprintf(cod, "%.0f", codigo);

        while (fgets(linha, sizeof (cad_clie), arquivoTxt) != NULL) {
            // pega o primeiro dado (se o arquivo foi ou não excluido logicamente)
            token = strtok(linha, ";");

            // compara e caso o arquivo não tenha sido excluido ele verifica se o código escrito pela pessoa realmente existe
            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                if (strcmp(cod, token) == 0) {
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
    }

    if (encontrado == 0) {
        printf("Cliente não encontrado!");
    }
    fclose(arquivoBin);
    fclose(arquivoTxt);
}

void le_todos_cadastro_pessoa() {
    FILE *arquivoBin, *arquivoTxt;
    cad_clie cliente;

    arquivoBin = fopen("cliente.bin", "rb");
    arquivoTxt = fopen("cliente.txt", "r");

    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.delet == 0) {
            printf("\nCódigo: %.0f\n\tNome: %s\n\tCPF: %.0f\n\tTelefone: %.0f\n\tEmail: %s\n\tSexo: %s\n\tEstad civil: %s\n\tNascimento: %s\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNumero: %.0f\n\tCEP: %.0f",
                    cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil,
                    cliente.nascimento, cliente.local.estado, cliente.local.cidade, cliente.local.bairro, cliente.local.rua,
                    cliente.local.numero, cliente.local.cep);
        }
    }

    char linha[(sizeof (cad_clie))], *token;
    while (fgets(linha, sizeof (cad_clie), arquivoTxt) != NULL) {
        // pega o primeiro dado (se o arquivo foi ou não excluido logicamente)
        token = strtok(linha, ";");

        // compara e caso o arquivo não tenha sido excluido ele mostra
        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
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
    fclose(arquivoBin);
    fclose(arquivoTxt);
    getchar();
}

void alteraCliente() {
    FILE *arquivoBin, *le, *altera;
    cad_clie cliente, novo;
    int encontrado = 0;
    float codigo;
    char linha[(sizeof(cad_clie))], *token;

    //      abrir arquivo
    arquivoBin = fopen("cliente.bin", "rb+wb");

    if (arquivoBin == NULL) {
        printf("\n\t!! Erro de leitura do Cadastro !! \n");
        exit(1);
    }

    printf("Digite o codigo do cliente que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.codigo == codigo && cliente.delet == 0) {
            encontrado = 1;
            printf("\nAntigos dados:\nCod: %.0f\nNome: %s\n", cliente.codigo, cliente.nome);

            printf("\nNovos dados:");

            novo.codigo = cliente.codigo;
            novo = le_dados_cad();

            //Volta para o inicio da linha de cadastro desse cliente, permitindo que se altere o cliente correto
            fseek(arquivoBin, -sizeof (cad_clie), SEEK_CUR);
            //Com o ponteiro no local correto, salva-se os novos dados, substituindo os antigos
            fwrite(&novo, sizeof (cad_clie), 1, arquivoBin);
            break;
        }

    }

    fclose(arquivoBin);

    if (encontrado == 0) {
        le = fopen("cliente.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        //lê linha a linha do arquivo
        while (fgets(linha, sizeof (cad_clie), le) != NULL) {
            //pega o primeiro dado guardado (se o arquivo foi ou não excluido) e o separa dos demais
            token = strtok(linha, ";");
            //compara o primeiro dado, caso ele seja 0, o arquivo não foi excluido
            if (strcmp(token, "0") == 0) {
                cliente.delet = atoi(token);
                token = strtok(NULL, ";");
                cliente.codigo = atoff(token);

                //se o código foi igual ao digitado ele altera
                if (cliente.codigo == codigo) {
                    cliente = le_dados_cad();
                    cliente.codigo = codigo;
                    encontrado = 1;
                }//caso o código digitado seja diferente
                else {
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
                }
            }//caso os dados já tenham sido deletados
            else {
                cliente.delet = atoi(token);
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
            }

            //salva os dados no arquivo temporario altera 
            fprintf(altera, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", cliente.delet, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
            fprintf(altera, "%s;%0.0f;%s;%s;%s;%0.0f;\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
        }

        fclose(altera);
        fclose(le);
        remove("cliente.txt");
        rename("temp.txt", "cliente.txt");
    }

    if (encontrado == 1) {
        printf("Dados alterados com sucesso!");
    } else {
        printf("Cliente não encontrado!");
    }

}

void removeCliente() {
    //      Variáveis
    FILE *arquivoBin;
    cad_clie cliente;

    float codigo;
    int encontrado = 0;

    printf("Digite o codigo do cliente que deseja excluir: ");
    scanf("%f", &codigo);

    //      abrir arquivo
    arquivoBin = fopen("cliente.bin", "rb+wb");

    if (arquivoBin == NULL) {
        printf("\n\t!! Erro de abertura de arquivo !! \n");
        exit(1);
    }
    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.codigo == codigo && cliente.delet == 0) {
            encontrado = 1;
            //Salva-se os dados na va, substituindo o valor do campo delet de 0 para 1
            cliente.delet = 1;
            //Volta para o inicio da linha de cadastro desse cliente, permitindo que se altere o cliente correto
            fseek(arquivoBin, -sizeof (cad_clie), SEEK_CUR);
            //Com o ponteiro no local correto, 
            fwrite(&cliente, sizeof (cad_clie), 1, arquivoBin);
            printf("\n\ta");
            break;
        }
    }
    fclose(arquivoBin);

    if (encontrado == 0) {
        FILE *remover, *le;
        char linha[(sizeof (cad_clie))], *token;
        le = fopen("cliente.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        remover = fopen("temp.txt", "a");
        if (remover == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (cad_clie), le) != NULL) {
            token = strtok(linha, ";");
            cliente.delet = atoi(token);
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

            if (cliente.codigo == codigo) {
                cliente.delet = 1;
                fprintf(remover, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", cliente.delet, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
                fprintf(remover, "%s;%0.0f;%s;%s;%s;%0.0f;\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
                encontrado = 1;
            } else {
                fprintf(remover, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", cliente.delet, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
                fprintf(remover, "%s;%0.0f;%s;%s;%s;%0.0f;\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
            }
        }

        fclose(remover);
        fclose(le);

        remove("cliente.txt");
        rename("temp.txt", "cliente.txt");
    }
    
    if (encontrado == 0) {
        printf("Cliente não encontrado!\n");
    } else {
        printf("Cliente excluido com sucesso!\n");
    }
}
